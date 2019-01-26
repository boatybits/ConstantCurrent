

#include <Wire.h>
#include <INA219.h>                  // https://github.com/flav1972/ArduinoINA219
#include <ESP8266WiFi.h>
#include <PubSubClient.h>            // MQTT libraryccdd


//                         Variables
//*****************************************************************************************************************************************
const char* ssid = "openplotter";
const char* password =  "12345678";
IPAddress mqttServer(10, 10, 10, 1);
const int mqttPort = 1883;
const char* mqttUser = "cafonhvu";
const char* mqttPassword = "Usp_VhNLl897";

int ledPin   = 2;         // onboard LED on esp8266 is pin 2


bool ledState = HIGH;
int repeatBlink = 1;
unsigned long dlyBlink = 500;
unsigned long currentMillis;
unsigned long myLEDmillis = 0;
int delayTime = 1000;
int send_Data_Flag = 0;
int mySendDatamillis = 0;
int myCurrentLoopmillis = 0;
int currentLoopDelay = 10;

int dly_send_Data = 500;
int currentTarget = 100;
float inaCurrent = 0;
float inaVoltage = 0;

int pwmPin = D0;
int pulseWidth = 500;
//|||||||||||||||||||||||  END   Variables   ||||||||||||||||
