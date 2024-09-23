#ifndef DataLogger_h
#define DataLogger_h

#include <DHT.h>
#include <MFRC522.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>

#define PIN_DHT 27
#define DHT_TYPE DHT11

Servo servoCochera;
DHT dht(PIN_DHT,DHT_TYPE);
LiquidCrystal_I2C lcd ( 0x27, 16, 2);

#include "Sensores.h"
Sensores SENSORES;


#include "Actuadores.h"
Actuadores ACTUADORES;

#include "Json.h"
JsonClass Json;

#include "MQTT.h"
MQTT INFORMACION;

#include "RTC.h"
DS1307_RTC Myrtc;


#include "MicroSD.h"
MicroSD MSD;

#include "RFID.h"
rfid Myrfid;

#include "Tareas.h"
millis_tasks Tareas;


#endif
