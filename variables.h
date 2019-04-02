

#include <Wire.h>
#include <INA219.h>                  // https://github.com/flav1972/ArduinoINA219
#include <ESP8266WiFi.h>
#include <PubSubClient.h>            // MQTT library


//                         Variables
//*****************************************************************************************************************************************
const char* ssid = "openplotter";
const char* password =  "12345678";
IPAddress mqttServer(10, 10, 10, 1);
const int mqttPort = 1883;
const char* mqttUser = "YOUR MQTT USER NAME";
const char* mqttPassword = "YOUR MQTT PASSWORD";

int ledPin   = 2;         // onboard LED on esp8266 is pin 2


bool ledState = HIGH;
int repeatBlink = 1;
unsigned long dlyBlink = 500;
unsigned long currentMillis;
unsigned long myLEDmillis = 0;
int delayTime = 1000;
int send_Data_Flag = 1;
int mySendDatamillis = 0;
int myCurrentLoopmillis = 0;
int currentLoopDelay = 10;

int dly_send_Data = 50;

int currentTarget = 100;
float inaCurrent = 0;
float inaVoltage = 0;
float currentArray[1000];
float voltageArray[1000];
float cTotal;
float vTotal;

int pwmPin = D0;
int pulseWidth = 500;
//|||||||||||||||||||||||  END   Variables   ||||||||||||||||
