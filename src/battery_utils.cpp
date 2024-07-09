#include <Arduino.h>
#include "battery_utils.h"
#include "configuration.h"
#include "boards_pinout.h"
#include "power_utils.h"
#include "utils.h"

extern  Configuration                   Config;
extern  uint32_t                        lastBatteryCheck;

bool    shouldSleepLowVoltage           = false;

float   adcReadingTransformation        = (3.3/4095);
float   voltageDividerCorrection        = 0.288;
float   readingCorrection               = 0.125;
float   multiplyCorrection              = 0.035;
float   adcVoltageCorrection            = 0.041;

float   voltageDividerTransformation    = 0.0;


#ifdef HAS_ADC_CALIBRATION
    #include <esp_adc_cal.h>

    #if defined(TTGO_T_LORA32_V2_1) || defined(TTGO_T_LORA32_V2_1_915)
        #define InternalBattery_ADC_Channel ADC1_CHANNEL_7  // t_lora32 pin35
        #define ExternalVoltage_ADC_Channel ADC1_CHANNEL_6  // t_lora32 pin34
    #endif

    #if CONFIG_IDF_TARGET_ESP32
    #define ADC_EXAMPLE_CALI_SCHEME ESP_ADC_CAL_VAL_EFUSE_VREF
    #elif CONFIG_IDF_TARGET_ESP32S2
    #define ADC_EXAMPLE_CALI_SCHEME ESP_ADC_CAL_VAL_EFUSE_TP
    #elif CONFIG_IDF_TARGET_ESP32C3
    #define ADC_EXAMPLE_CALI_SCHEME ESP_ADC_CAL_VAL_EFUSE_TP
    #elif CONFIG_IDF_TARGET_ESP32S3
    #define ADC_EXAMPLE_CALI_SCHEME ESP_ADC_CAL_VAL_EFUSE_TP_FIT
    #endif

    esp_adc_cal_characteristics_t adc_chars;
    bool calibrationEnable = false;
#endif



namespace BATTERY_Utils {

    float mapVoltage(float voltage, float in_min, float in_max, float out_min, float out_max) {
        return (voltage - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

    void adcCalibration() {
        if (calibrationEnable) {
            adc1_config_width(ADC_WIDTH_BIT_12);
            adc1_config_channel_atten(InternalBattery_ADC_Channel, ADC_ATTEN_DB_12);
            adc1_config_channel_atten(ExternalVoltage_ADC_Channel, ADC_ATTEN_DB_12);
        }  
    }

    void adcCalibrationCheck() {
        esp_err_t ret;
        ret = esp_adc_cal_check_efuse(ADC_EXAMPLE_CALI_SCHEME);
        /*if (ret == ESP_ERR_NOT_SUPPORTED) {
            Serial.println("Calibration scheme not supported, skip software calibration");
        } else if (ret == ESP_ERR_INVALID_VERSION) {
            Serial.println("eFuse not burnt, skip software calibration");
        } else */
        if (ret == ESP_OK) {
            esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_12, ADC_WIDTH_BIT_12, 1100, &adc_chars);
            //Serial.printf("eFuse Vref:%u mV\n", adc_chars.vref);
            calibrationEnable = true;
        } /*else {
            Serial.println("Invalid Calibration Arg");
        }*/        
    }

    void setup() {
        if ((Config.battery.sendExternalVoltage || Config.battery.monitorExternalVoltage) && Config.battery.voltageDividerR2 != 0) voltageDividerTransformation = (Config.battery.voltageDividerR1 + Config.battery.voltageDividerR2) / Config.battery.voltageDividerR2;

        #if defined(HAS_ADC_CALIBRATION)
            if (Config.battery.sendInternalVoltage || Config.battery.monitorInternalVoltage || Config.battery.sendExternalVoltage || Config.battery.monitorExternalVoltage) {
                adcCalibrationCheck();
                adcCalibration();
            }
        #endif
    }

    float checkInternalVoltage() { 
        #if defined(HAS_AXP192) || defined(HAS_AXP2101)
            if(POWER_Utils::isBatteryConnected()) {
                return POWER_Utils::getBatteryVoltage();
            } else {
                return 0.0;
            }
        #else
            int sample;
            int sampleSum = 0;
            #ifdef ADC_CTRL
                #if defined(HELTEC_WIRELESS_TRACKER)
                    digitalWrite(ADC_CTRL, HIGH);
                #endif
                #if defined(HELTEC_V3) || defined(HELTEC_V2) || defined(HELTEC_WSL_V3)
                    digitalWrite(ADC_CTRL, LOW);
                #endif
            #endif

            for (int i = 0; i < 100; i++) {
                #if defined(ESP32_DIY_LoRa) || defined(ESP32_DIY_LoRa_915) || defined(ESP32_DIY_1W_LoRa) || defined(ESP32_DIY_1W_LoRa_915)
                    sample = 0;
                #else
                    if (calibrationEnable) {
                        sample = adc1_get_raw(InternalBattery_ADC_Channel);
                    } else {
                        sample = analogRead(BATTERY_PIN);
                    }
                #endif                
                sampleSum += sample;
                delayMicroseconds(50); 
            }

            #ifdef ADC_CTRL
                #if defined(HELTEC_WIRELESS_TRACKER)
                    digitalWrite(ADC_CTRL, LOW);
                #endif
                #if defined(HELTEC_V3) || defined(HELTEC_V2) || defined(HELTEC_WSL_V3)
                    digitalWrite(ADC_CTRL, HIGH);
                #endif
                double inputDivider = (1.0 / (390.0 + 100.0)) * 100.0;  // The voltage divider is a 390k + 100k resistor in series, 100k on the low side.
                return (((sampleSum/100) * adcReadingTransformation) / inputDivider) + 0.285; // Yes, this offset is excessive, but the ADC on the ESP32s3 is quite inaccurate and noisy. Adjust to own measurements.
            #else
                if (calibrationEnable){
                    float voltage = esp_adc_cal_raw_to_voltage(sampleSum / 100, &adc_chars);
                    voltage *= 2;       // for 100K/100K voltage divider
                    voltage /= 1000;
                    voltage -= adcVoltageCorrection;
                    return voltage;
                } else {
                    return (2 * (sampleSum/100) * adcReadingTransformation) + voltageDividerCorrection;  // raw voltage without mapping
                }
            #endif
            // return mapVoltage(voltage, 3.34, 4.71, 3.0, 4.2); // mapped voltage
        #endif
    }

    float checkExternalVoltage() {
        int sample;
        int sampleSum = 0;
        for (int i = 0; i < 100; i++) {
            if(calibrationEnable){    
                sample = adc1_get_raw(ExternalVoltage_ADC_Channel);
            } else {
                sample = analogRead(Config.battery.externalVoltagePin);
            }
            sampleSum += sample;
            delayMicroseconds(50);
        }

        float extVoltage;
        if (calibrationEnable){
            extVoltage = esp_adc_cal_raw_to_voltage(sampleSum / 100, &adc_chars) * voltageDividerTransformation; // in mV
            extVoltage /= 1000;
        } else {
            extVoltage = ((((sampleSum/100)* adcReadingTransformation) + readingCorrection) * voltageDividerTransformation) - multiplyCorrection;
        }
        return extVoltage; // raw voltage without mapping

        // return mapVoltage(voltage, 5.05, 6.32, 4.5, 5.5); // mapped voltage
    }

    void checkIfShouldSleep() {
        if (lastBatteryCheck == 0 || millis() - lastBatteryCheck >= 15 * 60 * 1000) {
            lastBatteryCheck = millis();            
            if (checkInternalVoltage() < Config.lowVoltageCutOff) {
                ESP.deepSleep(1800000000); // 30 min sleep (60s = 60e6)
            }
        }
    }

    void startupBatteryHealth() {
        #ifdef BATTERY_PIN
            if (Config.battery.monitorInternalVoltage && checkInternalVoltage() < Config.battery.internalSleepVoltage + 0.1) {
                shouldSleepLowVoltage = true;
            }
        #endif
        if (Config.battery.monitorExternalVoltage && checkExternalVoltage() < Config.battery.externalSleepVoltage + 0.1) {
            shouldSleepLowVoltage = true;
        }
        if (shouldSleepLowVoltage) {
            Utils::checkSleepByLowBatteryVoltage(0);
        }
    }

}