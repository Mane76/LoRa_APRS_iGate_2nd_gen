#ifndef PINS_CONFIG_H_
#define PINS_CONFIG_H_

#include <Arduino.h>

#undef OLED_SDA
#undef OLED_SCL
#undef OLED_RST
#undef LORA_RST

// LORA MODULES
#if defined(TTGO_T_LORA_V2_1) || defined(HELTEC_V2)
#define LORA_SCK    5       // GPIO5    - SX1276 SCK
#define LORA_MISO   19      // GPIO19   - SX1276 MISO
#define LORA_MOSI   27      // GPIO27   - SX1276 MOSI
#define LORA_CS     18      // GPIO18   - SX1276 CS ---> NSS
#define LORA_RST    14      // GPIO14   - SX1276 RST
#define LORA_IRQ    26      // GPIO26   - SX1276 IRQ ---->DIO0
#endif

#ifdef HELTEC_V3
#define RADIO_SCLK_PIN  9   // SX1262 SCK
#define RADIO_MISO_PIN  11  // SX1262 MISO
#define RADIO_MOSI_PIN  10  // SX1262 MOSI
#define RADIO_CS_PIN    8   // SX1262 NSS
#define RADIO_RST_PIN   12  // SX1262 RST
#define RADIO_DIO1_PIN  14  // SX1262 DIO1
#define RADIO_BUSY_PIN  13  // SX1262 BUSY
#endif

// OLED 
#ifdef TTGO_T_LORA_V2_1
#define OLED_SDA    21
#define OLED_SCL    22
#define OLED_RESET  -1      // Reset pin # (or -1 if sharing Arduino reset pin)
#endif

#ifdef HELTEC_V2
#define OLED_SDA    4
#define OLED_SCL    15
#define OLED_RESET  16 
#endif

#ifdef HELTEC_V3
#define OLED_SDA    17
#define OLED_SCL    18
#define OLED_RESET  21 
#endif

// Led and other stuff
#if defined(TTGO_T_LORA_V2_1) || defined(HELTEC_V2)
#define greenLed    25      // Green Led
#define batteryPin  35
#endif
#ifdef HELTEC_V3
#define greenLed    35
#endif

/* (Same pins for LILYGO LoRa32 and ESP32 Wroom Dev )
SX1278-------------------> ESP32 ttgo-lora32-v21 and ESP32 WROOM Dev
GND                         GND
DIO1                        -
DIO2                        -
DIO3                        -
VCC                         3.3V
MISO                        19
MOSI                        27
SCLK                        5
NSS                         18
DIO0                        26
REST                        14
GND                         -  */
#endif
