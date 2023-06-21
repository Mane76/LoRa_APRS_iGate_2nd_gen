#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include "configuration.h"
#include "station_utils.h"
#include "syslog_utils.h"
#include "pins_config.h"
#include "wifi_utils.h"
#include "lora_utils.h"
#include "gps_utils.h"
#include "bme_utils.h"
#include "display.h"
#include "utils.h"


AsyncWebServer  server(80);

extern WiFiClient           espClient;
extern Configuration        Config;
extern String               versionDate;
extern bool                 statusAfterBoot;
extern String               firstLine;
extern String               secondLine;
extern String               thirdLine;
extern String               fourthLine;
extern String               fifthLine;
extern String               sixthLine;
extern String               seventhLine;
extern uint32_t             lastBeaconTx;
extern uint32_t             lastScreenOn;
extern bool                 beacon_update;
extern int                  stationMode;
extern String               iGateBeaconPacket;
extern std::vector<String>  lastHeardStation;
extern int                  rssi;
extern float                snr;
extern int                  freqError;
extern String               distance;

namespace Utils {

void processStatus() {
    String status = Config.callsign + ">APLRG1";
    if (stationMode==1 || stationMode==2) {
        delay(1000);
        status += ",qAC:>https://github.com/richonguzman/LoRa_APRS_iGate";
        espClient.write((status + "\n").c_str());
        SYSLOG_Utils::log("APRSIS Tx", status,0,0,0);
    } else {
        delay(5000);
        status += ":>https://github.com/richonguzman/LoRa_APRS_iGate";
        if (stationMode == 4) {
            LoRa_Utils::changeFreqTx();
        }
        LoRa_Utils::sendNewPacket("APRS", status);
        if (stationMode == 4) {
            LoRa_Utils::changeFreqRx();
        }        
    }
    statusAfterBoot = false;
}

String getLocalIP() {
    return "IP :  " + String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(WiFi.localIP()[3]);
}

void setupDisplay() {
    setup_display();
    digitalWrite(greenLed,HIGH);
    Serial.println("\nStarting iGate: " + Config.callsign + "   Version: " + versionDate);
    show_display(" LoRa APRS", "      ( iGate )", "", "     Richonguzman", "     -- CD2RXU --", "", "      " + versionDate, 4000);
    digitalWrite(greenLed,LOW);
    firstLine   = Config.callsign;
    if (stationMode==3 || stationMode==4) {
        thirdLine = "<<   DigiRepeater  >>";
    }
    seventhLine = "     listening...";
}

void activeStations() {
    fourthLine = "Stations (" + String(Config.rememberStationTime) + "min) = ";
    if (lastHeardStation.size() < 10) {
        fourthLine += " ";
    }
    fourthLine += String(lastHeardStation.size());            
}

void checkBeaconInterval() {
    uint32_t lastTx = millis() - lastBeaconTx;
    if (lastTx >= Config.beaconInterval*60*1000) {
        beacon_update = true;    
    }
    if (beacon_update) {
        display_toggle(true);
        Serial.println("---- Sending iGate Beacon ----");
        STATION_Utils::deleteNotHeard();
        activeStations();
        if (stationMode==1 || stationMode==2) {
            thirdLine = getLocalIP();
            if (!Config.bme.active) {
                fifthLine = "";
            }
            sixthLine = "";
            show_display(firstLine, secondLine, thirdLine, fourthLine, fifthLine, sixthLine, "SENDING iGate BEACON", 1000);         
            seventhLine = "     listening...";
            if (Config.bme.active) {
                espClient.write((iGateBeaconPacket.substring(0,iGateBeaconPacket.indexOf(":=")+20) + "_" + BME_Utils::readDataSensor() + iGateBeaconPacket.substring(iGateBeaconPacket.indexOf(":=")+21) + " + WX" + "\n").c_str());
            } else {
                espClient.write((iGateBeaconPacket + "\n").c_str());
            }
            show_display(firstLine, secondLine, thirdLine, fourthLine, fifthLine, sixthLine, seventhLine, 0);
        } else if (stationMode==3 || stationMode==4) {
            String Rx = String(Config.loramodule.digirepeaterRxFreq);
            String Tx = String(Config.loramodule.digirepeaterTxFreq);
            if (stationMode==3) {
                secondLine = "Rx:" + String(Tx.substring(0,3)) + "." + String(Tx.substring(3,6));
            } else {
                secondLine = "Rx:" + String(Rx.substring(0,3)) + "." + String(Rx.substring(3,6));
            }
            secondLine += " Tx:" + String(Tx.substring(0,3)) + "." + String(Tx.substring(3,6));
            fifthLine = "";
            sixthLine = "";
            show_display(firstLine, secondLine, thirdLine, fourthLine, fifthLine, sixthLine, "SENDING iGate BEACON", 0);
            seventhLine = "     listening...";
            if (stationMode == 4) {
                LoRa_Utils::changeFreqTx();
            }
            if (Config.bme.active) {
                LoRa_Utils::sendNewPacket("APRS",iGateBeaconPacket.substring(0,iGateBeaconPacket.indexOf(":=")+20) + "_" + BME_Utils::readDataSensor() + iGateBeaconPacket.substring(iGateBeaconPacket.indexOf(":=")+21) + " + WX");
            } else {
                LoRa_Utils::sendNewPacket("APRS",iGateBeaconPacket);
            }
            if (stationMode == 4) {
                LoRa_Utils::changeFreqRx();
            }           
        }
        lastBeaconTx = millis();
        lastScreenOn = millis();
        beacon_update = false;
        
    }
    if (statusAfterBoot) {
        processStatus();
    }
}

void checkDisplayInterval() {
    uint32_t lastDisplayTime = millis() - lastScreenOn;
    if (!Config.display.alwaysOn) {
        if (lastDisplayTime >= Config.display.timeout*1000) {
            display_toggle(false);
        }
    }
}

void validateDigiFreqs() {
    if (stationMode == 4) {
        if (abs(Config.loramodule.digirepeaterTxFreq - Config.loramodule.digirepeaterRxFreq) < 125000) {
            Serial.println("Tx Freq less than 125kHz from Rx Freq ---> NOT VALID, check 'data/igate_conf.json'");
            show_display("Tx Freq is less than ", "125kHz from Rx Freq", "change it on : /data/", "igate_conf.json", 0);
            while (1);
        }
    }
}

void typeOfPacket(String packet, String packetType) {
    String sender;
    if (stationMode==1 || stationMode==2) {
        if (packetType == "LoRa-APRS") {
            fifthLine = "LoRa Rx ----> APRS-IS";
        } else if (packetType == "APRS-LoRa") {
            fifthLine = "APRS-IS ----> LoRa Tx";
        }
        sender = packet.substring(0,packet.indexOf(">"));
    } else {
        fifthLine = "LoRa Rx ----> LoRa Tx";
        sender = packet.substring(3,packet.indexOf(">"));
    }
    for (int i=sender.length();i<9;i++) {
        sender += " ";
    }
    if (packet.indexOf("::") >= 10) {
        if (packetType == "APRS-LoRa") {
            String addresseeAndMessage = packet.substring(packet.indexOf("::")+2);
            String addressee = addresseeAndMessage.substring(0, addresseeAndMessage.indexOf(":"));
            addressee.trim();
            sixthLine = sender + " > " + addressee;
        } else {
            sixthLine = sender + "> MESSAGE";
        }
        seventhLine = "RSSI:" + String(rssi) + "dBm SNR: " + String(snr) + "dBm";
    } else if (packet.indexOf(":>") >= 10) {
        sixthLine = sender + "> NEW STATUS";
        seventhLine = "RSSI:" + String(rssi) + "dBm SNR: " + String(snr) + "dBm";
    } else if (packet.indexOf(":!") >= 10 || packet.indexOf(":=") >= 10) {
        sixthLine = sender + "> GPS BEACON";
        GPS_Utils::getDistance(packet);
        seventhLine = "RSSI:" + String(rssi) + "dBm";
        if (rssi <= -100) {
            seventhLine += " ";
        } else {
            seventhLine += "  ";
        }
        if (distance.indexOf(".") == 1) {
            seventhLine += " ";
        }
        seventhLine += "D:" + distance + "km";
    } else {
        sixthLine = sender + "> ??????????";
        seventhLine = "RSSI:" + String(rssi) + "dBm SNR: " + String(snr) + "dBm";
    }
}

void startOTAServer() {
    if (stationMode==1 || stationMode==2) {
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "Hi " + Config.callsign + ", this is your (Richonguzman/CD2RXU) LoRa iGate.\n\nTo update your firmware or filesystem go to: http://" + getLocalIP().substring(getLocalIP().indexOf(":")+2) + "/update\n\n\n73!");
        });
        AsyncElegantOTA.begin(&server);
        server.begin();
        Serial.println("init : OTA Server     ...     done!");
    }
}

}