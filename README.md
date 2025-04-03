# LoRa APRS iGate Taller Integrador Grupo 3

# Resumen
En el presente documento se encuentra una investigación acerca de los sistemas de comunicación APRS y LoRa, donde se detalla información importante acerca de ellos, como funcionan, en que bandas de frecuencia pueden operar en distintos lugares del mundo, así como aplicaciones de estos en diferentes áreas. El objetivo de la investigación es ampliar el conocimiento del tema para posteriormente realizar una implementación con un módulo iGate, a este se le cargara el programa del repositorio para visualizar su correcto funcionamiento en páginas de APRS.

# Introducción

# APRS
El APRS (Automatic Packet Reporting System) [1] es un sistema de radioaficionados diseñado para resistir un intercambio rápido y confiable de información táctica en tiempo real y que permite compartir datos de eventos, redes, o cualquier otro tipo de información relevante a cualquier otra estación de la red a través de equipos de radioaficionado, para ello ese utiliza bandas de frecuencias asignadas específicamente para realizar transmisiones de datos. Este sistema fue desarrollado por Bob Bruninga en la década de 1990.

El APRS se utiliza en varias aplicaciones como las siguientes [2]:

Seguimiento y mapeo de posiciones en tiempo real: útil para la gestión de emergencias donde el seguimiento de la ubicación de los equipos de rescate, ambulancias u otros activos críticos requieren de rápidos tiempos de respuesta y la coordinación general. También en eventos públicos, como maratones o desfiles, donde los organizadores del evento necesitan monitorear la ubicación en tiempo real de los participantes y los vehículos de apoyo.

Informes de estaciones meteorológicas: información sobre temperatura, humedad, velocidad y dirección del viento, presión barométrica y precipitaciones. Muchas estaciones meteorológicas principiantes transmiten estos datos a través de APRS, lo que proporciona una valiosa información meteorológica localizada que puede ser fundamental para la respuesta ante desastres y el conocimiento de la situación.

Mensajes bidireccionales, boletines y anuncios: El APRS admite la transmisión y recepción de mensajes de texto, que pueden dirigirse a estaciones específicas o transmitirse a todas las estaciones dentro de la red. Esto es particularmente importante para comunicaciones de emergencia, donde una comunicación rápida y confiable es altamente requerido.

Integración en internet: El sistema APRS para Internet (APRS-IS) conecta redes APRS locales con una red global de servidores, proporcionando acceso mundial a los datos APRS. Al vincular las redes APRS basadas en radioenlaces locales a Internet, APRS-IS permite que estaciones de todo el mundo compartan su información, convirtiendo el APRS en una herramienta de comunicación de acceso global.

El APRS trabaja con el protocolo AX.25 [2], este es utilizado por radioaficionados para la comunicación basada en paquetes. El protocolo AX.25 se deriva del conjunto de protocolos X.25, diseñado para redes conmutadas por paquetes. APRS utiliza el modo de tramas UI (tramas de información no numerada) de AX.25, permitiendo la comunicación sin conexión. Esto significa que las tramas APRS se transmiten sin necesidad de establecer una conexión, lo que lo hace ideal para la comunicación de estilo difusión en tiempo real. Un paquete APRS se compone de varios campos:

Campo de dirección de destino: este campo indica el receptor del paquete. Sin embargo, en APRS, este campo también puede contener información como el tipo de datos (por ejemplo, datos GPS, mensajes) o especificar un grupo al que se dirige el paquete. Algunos ejemplos de direcciones de destino incluyen GPS, APRS, y BEACON.

Campo de dirección de origen: este campo contiene el distintivo de llamada y el SSID de la estación transmisora. El SSID (identificador de estación secundaria) es un identificador adicional que especifíca entre los distintos tipos de transmisiones APRS o muestra los íconos que representan la estación en el mapa (por ejemplo, automóvil, casa, estación meteorológica, entre otros).

Campo de dirección de repetidor digital: este campo contiene los distintivos de llamada de los repetidores digitales que retransmitirán el paquete. Pueden ser hasta ocho repetidores digitales en un paquete APRS, pero el uso de la gestión de rutas inteligente reduce la necesidad de especificar cada uno.

Campos de control e identificador de protocolo: estos campos son estándar en todos los paquetes AX.25. El espaci0o de control está configurado en 0x03 para tramas de interfaz de usuario y el espacio de identificador de protocolo (PID) está configurado en 0xf0, lo que indica que no hay ningún protocolo de capa 3.

Campo de información: el campo de información es el centro de un paquete APRS. Contiene los datos APRS reales y empieza con un identificador de tipo de datos (DTI) que especifica qué tipo de datos siguen. El campo de información puede incluir informes de posición, mensajes de texto, información meteorológica o incluso datos de telemetría.

La banda de frecuencia [1] en la que opera es 144.390 MHz para América del norte y se dice que para el resto del continente es la misma, en Europa se utiliza 144,80 MHz, en Australia se utiliza 145,175 MHz y en Asia se utiliza 144.64 MHz.

Los componentes de una red APRS se basan en un dispositivo con GPS, una red de digipeater, IGates, un servidor APRS y un software APRS disponible para computadoras o dispositivos móviles. En la siguiente imagen se ejemplifica como se conectan todos estos componentes [2]. 

![red-aprs](https://github.com/user-attachments/assets/89e7c9a5-8456-4295-a1b4-b172ab43dce0)

# LoRa

LoRa (Long Range) es [3] una tecnología inalámbrica (asi como WiFi, Bluetooth, LTE, SigFox o Zigbee) que utiliza un tipo de modulación en radiofrecuencia patentado por Semtech, LoRa es una tecnología de comunicación inalámbrica que combina un consumo de energía ultrabajo con un largo alcance efectivo. LoRa emplea una modulación de espectro ampliado con características similares a las de modulación por desplazamiento de frecuencia. Sin embargo, LoRa destaca gracias a su aumento notable del rango de comunicaciones. Algunas de sus ventajas son [4] la alta tolerancia a las interferencias, alta sensibilidad en la recepción de datos, bajo consumo de potencia, baja transferencia de datos (hasta 255 Bytes), conexión punto a punto.

Las bandas de frecuencias de trabajo para LoRa son las siguientes [4]: 868 MHz en Europa, 915 MHz en América, y 433 MHz en Asia.

LoRa es flexible [5] para usos rurales o en interiores en agricultura inteligente, ciudades inteligentes, IoT industrial (IIoT), entornos inteligentes, control industrial, atención sanitaria inteligente, hogares y edificios inteligentes, servicios públicos y medición inteligentes (electricidad, agua, gas), y cadenas de suministro y logística inteligentes.

Existen múltiples módulos en el mercado que combinan el microcontrolador ESP32 con tecnología LoRa, ideales para proyectos de Internet de las Cosas (IoT) que requieren comunicación inalámbrica de largo alcance y bajo consumo energético.

ESP32 LoRa V3 Placa de módulo con batería de 3000 mAh (Amazon, 31\$). Disponible en: https://www.amazon.com/-/es/ESP32-V3-Placa-m\%C3\%B3dulo-bater\%C3\%ADa/dp/B0D2WXLZXQ?th=1

Módulo de placa de desarrollo LoRa ESP32 SX1276 LoRaWAN protocolo WIFI BLE pantalla OLED con antena para Arduino 433/510MHz 868/915MHz (AliExpress, 16\$) Disponible en: https://es.aliexpress.com/i/32987170470.html.

ESP32-LORA915-OLED Modulo LoRa 915MHz con pantalla OLED (27\$). Disponible en: https://www.didacticaselectronicas.com.co/shop/esp32-lora915-oled-modulo-lora-915mhz-con-pantalla-oled-14207#attr=

Modulo Lora 32 V3 Iot Kit Esp32 Wifi Desarrollo Para Arduino (16\$). Disponible en: https://www.tienda.educabot.com/MLA-1422421393-modulo-lora-32-v3-iot-kit-esp32-wifi-desarrollo-para-arduino-\_JM

# Legislación costarricense

Para la obtención de un permiso de uso de frecuencias indicado, se debe seguir el siguiente procedimiento [6]:

El interesado debe presentar la solicitud de permiso de uso de frecuencia ante la Viceministro de Telecomunicaciones del MICITT (Poder Ejecutivo).

El Poder Ejecutivo remite dicha solicitud a la SUTEL para la emisión de un dictamen técnico.

La SUTEL revisa la información presentada, elabora el dictamen técnico requerido y lo remite al Poder Ejecutivo.

El Poder Ejecutivo resuelve la solicitud del interesado, considerando el dictamen técnico de la SUTEL, otorgando o no el permiso respectivo, según la legislación actual.

El interesado recibe la notificación por parte del Poder Ejecutivo, respecto a la resolución de la solicitud presentada.

# Uso práctico del módulo iGate
Para la siguiente sección del proyecto, se realizó una implementación con un modulo LoRa iGate, el cual se le cargó el repositorio de GitHub de Richon Guzmán utilizando Platformio y se verificó en las páginas de APRS si el dispositivo utilizado era visible. En las siguientes imágenes se aprecia como en dichas páginas se observaba el dispositivo, el cual esta ubicado en las cercanías del ITCR, en la imagén se logra ver otros dispositivos en la escuela de electrónica. Además de evidencias del correcto funcionamiento del módulo.
 
![image](https://github.com/user-attachments/assets/b90b827b-c4d7-4339-9ba5-01e1d6844ea4)


![APRS](https://github.com/user-attachments/assets/7c2f6764-f6ad-4020-842d-f059dcae9f3e)


Para configurar correctamente el dispositivo, se hizo uso de la extensión Platformio de Visual Studio. Luego de cargar el programa al dispositivo, se ingresó a la dirección IP dada por este, en donde fue posible configurar la red wifi a la que se conectara, junto con la contraseña y SSID propio del módulo. Al cargar correctamente la extensión de platformio en VS, se cargará un ícono, tal como se muestra a continuación.


# Bibliografía

[1] C. de Radio Experimentadores. “Que es y cómo funciona el sistema APRS.” [Online]. (2024), direccion: https://crecj.org/que-es-y-como-funciona-el-sistema-aprs/.
[2] R. C. Capitol. “Guía definitiva de APRS para radioaficionados.” [Online]. (s.f.), direccion: https : / / www.radioclubcapitol.es/formacion/aprs/guia-aprs.
[3] A. Secure. “LORA: Que es y para que sirve?” [Online].(s.f.), direccion: https://alaisecure.es/glosario/lora-que-es-y-para-que-sirve/.
[4] C. Sensors. “Tecnolog´ıa LORA y LORAWAN.” [Online].(s.f.), direccion: https://www.catsensors.com/es/lorawan/tecnologia-lora-y-lorawan.
[5] Semtech. “La tecnología LoRa esta conectando nuestro planeta inteligente.” [Online]. (s.f.), direccion: https://www.semtech.com/lora/lora-applications.
[6] M. de Ciencia Innovacion Tecnología y Telecomunicaciones. “Cuadro Nacional de Atribucion de Frecuencias del PNAF.” Decreto No 44010-MICITT, Alcance no 99 a la Gaceta no 95, 30 de mayo. (2023).

# Informe escrito: 
https://www.overleaf.com/read/qsrhzgrrwdwn#01a2f4



# Documentación repositorio de Richon Guzmán
__(This iGate Firmware works with all LoRa Tracker Firmwares (specially this <a href="https://github.com/richonguzman/LoRa_APRS_Tracker" target="_blank">LoRa APRS Tracker Firmware</a>))__
<br />

____________________________________________________

## You can support this project to continue to grow:

[<img src="https://github.com/richonguzman/LoRa_APRS_Tracker/blob/main/images/github-sponsors.png">](https://github.com/sponsors/richonguzman)     [<img src="https://github.com/richonguzman/LoRa_APRS_Tracker/blob/main/images/paypalme.png">](http://paypal.me/richonguzman)

<br />

# WEB FLASHER/INSTALLER is <a href="https://richonguzman.github.io/lora-igate-web-flasher/installer.html" target="_blank">here</a>

____________________________________________________

# WIKI

### FAQ, BME280, TNC and more --> <a href="https://github.com/richonguzman/LoRa_APRS_iGate/wiki/00.-FAQ-(frequently-asked-questions)" target="_blank">here</a>.

### Installation Guide --> <a href="https://github.com/richonguzman/LoRa_APRS_iGate/wiki/01.-Installation-Guide" target="_blank">here</a>.
<br />

# SUPPORTED BOARDS

### Buying links --> <a href="https://github.com/richonguzman/LoRa_APRS_iGate/wiki/108.-Supported-Boards-and-Buying-Links" target="_blank">here</a>.

(NOTE: all boards with 433-868-915 MHz versions)

- TTGO Lilygo LoRa32 T3S3 V1.2 and LoRa32 V2.1 (V1.6 is the same).

- TTGO T-Beam V1.0 , V1.1, V1.2 (also variations with SX1262 and SX1268 LoRa Modules).

- T-Deck Plus (and also regular T-Deck with/without GPS).

- HELTEC V2, V3 , Wireless Stick, Wireless Stick Lite, HT-CT62, Wireless Tracker, Wireless Paper.

- QRP Labs LightGateway 1.0.

- ESP32 Wroom + SX1278 LoRa Module or Ebyte 400M30S (or 900M30S) 1W LoRa Module for a DIY Versions.

- ESP32C3 + Ebyte 400M30S(or 900M30S) 1W LoRa Module for another DIY version.

- ESP32 + 4G/LTE A7670 Modem + SX1278 DIY Version.

- Wemos Lolin32 Oled + SX1278 DIY Version.

<br />

## Timeline (Versions):

- 2025.03.20 Manager List added to enable/disable DigiEcoMode and Tx Control. Thanks LB5JJ.
- 2025.03.03 T-Beam Supreme board added and more BlackList rules added.
- 2025.02.28 Heltec Wireless Paper with Epaper working. Thanks SzymonPriv for pointing to the right library.
- 2025.02.25 Objects Rules update, GPS Boards: Satellites on Screen, Wx Height Correction from GPS Data.
- 2025.01.22 Added LILYGO T-DECK PLUS (and DIY+GPS version) board support.
- 2025.01.11 Added HELTEC V3.2 board support.
- 2025.01.07 TROY_LoRa_APRS board added. GMT in quarter hour fix and Beacon fix for TNC.
- 2025.01.02 Callsign Black List added.
- 2024.12.30 Fixed missing validation for correct Digipeater mode when not connected to APRS-IS.
- 2024.12.06 APRS-IS connnection and passcode validation added.
- 2024.11.06 (Silent Update) Working now with Board "VARIANTS".
- 2024.10.29 Added LILYGO Lora32 T3S3 support.
- 2024.10.25 Added QRP Labs LightGateway 1.0 support.
- 2024.10.21 Boards with GPS can now send Real-GPS Beacon (also posible: GPS ambiguity of ~ 1 km).
- 2024.10.14 Received Packets in WebUI show real Local Time (NTP with GMT offset).
- 2024.10.08 New EcoMode for Remote Digipeaters without WiFi/WiFiAP, Screen, Leds (Example: LILYGO LoRa32 uses only 24mA, with WifiAP 150mA). APRS Message/Queries can start/stop this mode too.
- 2024.10.06 Cross Frequency Digipeater Rules added.
- 2024.09.23 Libraries Update for SDK3
- 2024.09.23 Added Enconded Telemetry for Battery (+ External Voltage) in Station GPS Beacon Packet. 
- 2024.08.23 Wemos S2 Mini DIY LoRa added.
- 2024.08.19 HELTEC Wireless Paper working (still missing Epaper code).
- 2024.08.13 Web Authentication for WebUI. Thanks Mitja S57PNX.
- 2024.08.05 WIDE2-n added to WIDE1-n in Digipeater Modes.
- 2024.06.27 External Voltage Divider Resistor configuration on WebUI. Thanks Tilen S54B.
- 2024.06.26 Personal Note information on WebUI for the Station. Thanks Tilen S54B.
- 2024.06.24 Callsign Validation fix. Thanks Helge SA7SKY.
- 2024.06.21 Tx packets coming from APRS-IS are (now) formatted into 3rd Party (as they should have been since the beginning). Thanks Lynn KJ4ERJ and Geoffrey F4FXL.
- 2024.06.18 All boards with 433 / 868 / 915 MHz versions.
- 2024.06.10 ESP32C3 + 1W LoRa Module (E22 400M30S) support added.
- 2024.06.09 Si7021 module added (with autodetected I2C Address)
- 2024.06.08 Callsign Validation for all Station that iGate/Digi hears.
- 2024.05.27 Battery Monitor for internal and External Voltages (to make board sleep and avoid low discharge of batterys) T-Beam boards now with Battery readings as well.
- 2024.05.23 Forced Reboot Mode added.
- 2024.05.22 Experimental backup-Digipeater-Mode when "only" iGate mode loses WiFi connection added.
- 2024.05.20 WebConfig update to control whether Messages and Objects should be Tx to RF.
- 2024.05.17 HELTEC Wireless Stick Lite v3 support added.
- 2024.05.14 BME modules will be autodetected (I2C Address and if it is BME280/BMP280/BME680).
- 2024.05.13 PacketBuffer for Rx (25 Seg).
- 2024.05.11 HELTEC Wireless Tracker support added.
- 2024.04.23 T-LoRa32 v1.6/v2.1 with 915MHz support added.
- 2024.04.23 ESP32 + 4G/LTE MODEM A7670SA + LoRa (SX1278) support added.
- 2024.04.22 Wemos Lolin32 OLED DIY LoRa support added .
- 2024.04.21 WEB INSTALLER (thanks Damian SQ2CPA).
- 2024.04.20 New Output Buffer process: no more packets lost.
- 2024.04.13 Received Packets added on WebUI.
- 2024.04.09 iGate/Digipeater own GPS beacon is encoded (Base91) now.
- 2024.03.18 OE5HWN MeshCom board support added.
- 2024.02.25 New Web Configuration UI with WiFi AP (thanks Damian SQ2CPA).
- 2023.01.28 Updated to ElegantOTA v.3 (AsyncElegantOTA was deprecated).
- 2024.01.19 TextSerialOutputForApp added to get text from Serial-Output over USB into PC for PinPoint App (https://www.pinpointaprs.com) and APRSIS32 App (http://aprsisce.wikidot.com)
- 2024.01.12 Added iGate Mode to also repeat packets (like a iGate+Digipeater) in stationMode 2 and 5.
- 2024.01.11 Added iGate Mode to enable APRS-IS and LoRa beacon report at the same time.
- 2024.01.05 Lilygo TTGO T-Beam V1, V1.2, V1 + SX1268, V1.2 + SX1262 support added.
- 2024.01.02 EByte 400M30S 1 Watt LoRa module for DIY ESP32 iGate support added.
- 2023.12.27 HELTEC V3 board support added. Thanks Luc ON2ON.
- 2023.12.26 BME680 module support added.
- 2023.12.07 MIC-E process and Syslog added.
- 2023.12.06 HELTEC V2 board support added.
- 2023.11.26 Small correction to enable Syslog in stationMode5.
- 2023.10.09 Added "WIDE1-1" to Tx packets from iGate to be *repeated* by Digipeaters.
- 2023.10.09 BMP280 module support added.
- 2023.08.20 Added External Voltage Measurement (Max 15V!)
- 2023.08.05 Ground Height Correction for Pressure readings added.
- 2023.07.31 StationMode5 added: iGate when WiFi and APRS available, Digipeater when not.
- 2023.07.16 Small OTA, BME module update.
- 2023.07.05 Adding monitor info of Battery connected.
- 2023.06.18 Info on Oled Screen mayor update, added RSSI and Distance to Listened Station.
- 2023.06.17 BME280 Module (Temperature, Humidity, Pressure) support added.
- 2023.06.12 Syslog added.
- 2023.06.10 OTA update support for Firmware and Filesystem.
- 2023.06.08 Adding Digipeater Functions.
- 2023.06.06 Full repack of Code and adding _enableTx_ only for Ham Ops.
- 2023.05.23 Processing Query's from RF/LoRa or APRS-IS (Send "Help" Message to test).
- 2023.05.19 Saving Last-Heard Stations for validating Tx Responses.
- 2023.05.12 Tx Packet from APRS-IS to LoRa-RF Correction.
- 2023.03.01 Tx Packet from APRS-IS to nearby LoRa Stations.
- 2023.02.17 Receiving Feed from APRS-IS.
- 2023.02.10 First Beta (receiving LoRa Beacon/Packets and uploading to APRS-IS).

__________________________________________

# Hope You Enjoy this, 73! CA2RXU, Valparaiso, Chile
