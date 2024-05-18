# Richonguzman / CA2RXU LoRa APRS iGate/Digirepeater

This firmware is for using ESP32 based boards with LoRa Modules and GPS to live in the APRS world.

Attention users of TTGO 2.1 v1.6 (boards labeled “T3_V1.6” on pcb): Read <a href="https://web.archive.org/web/20210125073301/https://www.thethingsnetwork.org/community/berlin/post/warning-attention-users-of-ttgo21-v16-boards-labeled-t3_v16-on-pcb-battery-exploded-and-got-on-fire" target="_blank">this</a> if you plan to use a LI-PO battery attached to the connector

![Screenshot](https://github.com/richonguzman/LoRa_APRS_iGate/blob/main/images/iGateOledScreen.jpeg)

__(NOTE: This iGate Firmware was develop to work with all LoRa APRS Trackers and specially with this firmware <a href="https://github.com/richonguzman/LoRa_APRS_Tracker" target="_blank">LoRa APRS Tracker</a>)__

___________________________________________________

## You can support this project to continue to grow:

[<img src="https://github.com/richonguzman/LoRa_APRS_Tracker/blob/main/images/github-sponsors.png">](https://github.com/sponsors/richonguzman)     [<img src="https://github.com/richonguzman/LoRa_APRS_Tracker/blob/main/images/paypalme.png">](http://paypal.me/richonguzman)

____________________________________________________

### This repo is a fork of Richonguzman's iGate with adjusted parameters in config. 


This next generation LoRa iGate can work as:
- pure RX-iGate, 
- Rx+Tx-iGate and distribute messages and weather forecasts to heard trackers, and 
- Digipeater in simplex or split-frequency environment.

# WEB INSTALLER

As easy as it gets, the new <a href="https://sq2cpa.github.io/lora-flasher/ca2rxu.html" target="_blank">Web Installer</a> (thanks Damian SQ2CPA)

[<img src="https://github.com/richonguzman/LoRa_APRS_iGate/blob/main/images/WebFlasher.png">](https://sq2cpa.github.io/lora-flasher/ca2rxu.html)

This installs the original version from Ricardo with a few clicks, my fork can then be installed via OTA and the binaries matching your hardware in this repo.

____________________________________________________

# SUPPORTED BOARDS

- TTGO Lilygo LoRa32 v2.1 / v1.6 (they work the same)

- TTGO T-Beam v1.0 , v1.1, v1.2 (also variations with SX1262 and SX1268 LoRa Modules)

- HELTEC V2, V3 , Wireless Stick, HT-CT62, Wireless Tracker

- ESP32 Wroom + SX1278 LoRa Module or 400M30S 1W LoRa Module for a DIY Versions.

- ESP32 + 4G/LTE A7670 Modem + SX1278 DIY Version.

- Wemos Lolin32 Oled + SX1278 DIY Version.


### Buying links --> <a href="https://github.com/richonguzman/LoRa_APRS_iGate/wiki/Z.-------Supported-Boards-and-Buying-Links" target="_blank">here</a>.

____________________________________________________

# WIKI

### Installation Guide --> <a href="https://github.com/richonguzman/LoRa_APRS_iGate/wiki/01.-Installation-Guide" target="_blank">here</a>.

*(Wiki has all configuration explanation, supported boards list, adding BME/BMP Wx modules and more)*

____________________________________________________
## Timeline (Versions):


- 2024.05.17 HELTEC Wireless Stick Lite v3 support added.
- 2024.05.14 BME modules will be autodetected (I2C Address and if it is BME280/BMP280/BME680).
- 2024.05.13 PacketBuffer for Rx (25 Seg).
- 2024.05.11 HELTEC Wireless Tracker support added.
- 2024.04.23 T-LoRa32 v1.6/v2.1 with 915MHz support added.
- 2024.04.23 ESP32 + 4G/LTE MODEM A7670SA + LoRa (SX1278) support added.
- 2024.04.22 Wemos Lolin32 OLED DIY LoRa support added .
- 2024.04.21 WEB INSTALLER (thanks Damian SQ2CPA).
- 2024.04.20 CRC with additional information shown in Syslog
- 2024.04.20 New Output Buffer process: no more packets lost.
- 2024.04.13 Received Packets added on WebUI.
- 2024.04.09 iGate/Digirepeater own GPS beacon is encoded (Base91) now.
- 2024.03.18 OE5HWN MeshCom board support added.
- 2024.02.25 New Web Configuration UI with WiFi AP (thanks Damian SQ2CPA).
- 2023.01.28 Updated to ElegantOTA v.3 (AsyncElegantOTA was deprecated).
- 2024.01.19 TextSerialOutputForApp added to get text from Serial-Output over USB into PC for PinPoint App (https://www.pinpointaprs.com) and APRSIS32 App (http://aprsisce.wikidot.com)
- 2024.01.12 Added iGate Mode to also repeat packets (like a iGate+DigiRepeater) in stationMode 2 and 5.
- 2024.01.11 Added iGate Mode to enable APRS-IS and LoRa beacon report at the same time.
- 2024.01.05 Lilygo TTGO T-Beam V1, V1.2, V1 + SX1268, V1.2 + SX1262 support added.
- 2024.01.02 EByte 400M30S 1 Watt LoRa module for DIY ESP32 iGate support added.
- 2023.12.27 HELTEC V3 board support added. Thanks Luc ON2ON.
- 2023.12.26 BME680 module support added.
- 2023.12.07 MIC-E process and Syslog added.
- 2023.12.06 HELTEC V2 board support added.
- 2023.11.26 Small correction to enable Syslog in stationMode5.
- 2023.10.09 Added "WIDE1-1" to Tx packets from iGate to be *repeated* by Digirepeaters.
- 2023.10.09 BMP280 module support added.
- 2023.08.20 Added External Voltage Measurement (Max 15V!)
- 2023.08.05 Ground Height Correction for Pressure readings added.
- 2023.07.31 StationMode5 added: iGate when WiFi and APRS available, DigiRepeater when not.
- 2023.07.16 Small OTA, BME module update.
- 2023.07.05 Adding monitor info of Battery connected.
- 2023.06.18 Info on Oled Screen mayor update, added RSSI and Distance to Listened Station.
- 2023.06.17 BME280 Module (Temperature, Humidity, Pressure) support added.
- 2023.06.12 Syslog added.
- 2023.06.10 OTA update support for Firmware and Filesystem.
- 2023.06.08 Adding Digirepeater Functions.
- 2023.06.06 Full repack of Code and adding _enableTx_ only for Ham Ops.
- 2023.05.23 Processing Query's from RF/LoRa or APRS-IS (Send "Help" Message to test).
- 2023.05.19 Saving Last-Heard Stations for validating Tx Responses.
- 2023.05.12 Tx Packet from APRS-IS to LoRa-RF Correction.
- 2023.03.01 Tx Packet from APRS-IS to nearby LoRa Stations.
- 2023.02.17 Receiving Feed from APRS-IS.
- 2023.02.10 First Beta (receiving LoRa Beacon/Packets and uploading to APRS-IS).

____________________________________________________


Instructions for the configuration in WebUI in order to match the "old" stationModes: 

a) Change _callsign_ from "NOCALL-10" to your CALLSIGN + SSID as well as _beacon path_ to WIDE1-1

b) Choose _stationMode_:

    1 = RX iGate, black "L" as symbol
    Section "Station", Symbol, set to "Black Diamond with L"
    Section "WiFi Access", set SSID and Passphrase
    Section "APRS-IS", enable "Enable APRS-IS connection" and "Send our beacon to APRS-IS"
    Section "LoRa", enable "Enable LoRa-RX", set RX Frequency (e.g. 433775000)

    2 = Rx + TX iGate, red "L" as symbol, HAM only. RX will be sent to APRS-IS, Messages will be sent via Lora. Same frequency for RX and TX. By using this feature you have comply with the regulations of your country.
    Section "Station", Symbol, set to "Red Diamond with L"
    Section "WiFi Access", set SSID and Passphrase
    Section "APRS-IS", enable "Enable APRS-IS connection" and "Send our beacon to APRS-IS"
    Section "LoRa", enable "Enable LoRa-TX" and "Enable LoRa-RX", set Frequencies to same frequency (e.g. 433775000, TX 433775000)

    3 = Digipeater simplex, green "L" as symbol, HAM only. Received packets containing WIDEx-x in path will be digipeated on the same frequency. By using this feature you have comply with the regulations of your country.
    Section "Station", Symbol, set to "Green Star with L"
    Section "Digipeating", choose "WIDE1"
    Section "Beaconing", enable "Send beacon via RF"
    Section "LoRa", enable "Enable LoRa-TX" and "Enable LoRa-RX", set Frequencies to same frequency (e.g. 433775000, TX 433775000)

    4 = Digipeater split frequency, green "L" as symbol, HAM only. Received packets will be digipeated on a different frequency. Frequency separation must be 125kHz or more. By using this feature you have comply with the regulations of your country.
    Section "Station", Symbol, set to "Green Star with L"
    Section "Digipeating", choose "WIDE1"
    Section "Beaconing", enable "Send beacon via RF"
    Section "LoRa", enable "Enable LoRa-TX" and "Enable LoRa-RX", set Frequencies to split frequency (e.g. RX 433775000, TX 433900000, offset > 125kHz)

__________________________________________


# Hope You Enjoy this, 73 !!  CA2RXU , Valparaiso, Chile
