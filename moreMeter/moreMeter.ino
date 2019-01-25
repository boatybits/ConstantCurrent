

#include <Wire.h>
#include <INA219.h>                  // https://github.com/flav1972/ArduinoINA219
#include <ESP8266WiFi.h>
#include <PubSubClient.h>


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
int dly_send_Data = 500;
int currentTarget = 100;
float inaCurrent = 0;
float inaVoltage = 0;

int pwmPin = D0;
int pulseWidth = 500;
//|||||||||||||||||||||||  END   Variables   ||||||||||||||||



WiFiClient espClient;
PubSubClient client(espClient);
INA219 ina219;

//*****************************************************************************************************************************************
//**************************************************************Subroutines****************************************************************
//*****************************************************************************************************************************************




//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||END Subroutines****************************************************************



//                          s e t u p ( )
//**********************************************************************

void setup() {

  Serial.begin(115200);
  Serial.println();
  Serial.println("******************");
  Serial.print("Begining setup..");
  delay(10);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);   // turn the LED off, internal LED connected to high
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected to the WiFi network - ");
  //Serial.println(WiFi.available());
  Serial.println(WiFi.status());

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {

      Serial.println("connected");
      delay(50);
      sendMQTT("esp/text", "Booting");
    } else {

      Serial.print("failed with state ");
      Serial.println(client.state());
      delay(100);

    }
  }

  client.publish("esp/text", "ESP8266 started");
  client.subscribe("esp/control");
  client.subscribe("esp/controlcurrent");
  ina219.begin();
  // begin calls:
  // configure() with default values RANGE_32V, GAIN_8_320MV, ADC_12BIT, ADC_12BIT, CONT_SH_BUS
  // calibrate() with default values D_SHUNT=0.1, D_V_BUS_MAX=32, D_V_SHUNT_MAX=0.2, D_I_MAX_EXPECTED=2
  // in order to work directly with ADAFruit's INA219B breakout
  //ina219.configure(INA219::RANGE_16V, INA219::GAIN_2_80MV, INA219::ADC_128SAMP, INA219::ADC_128SAMP, INA219::CONT_SH_BUS);
  //ina219.configure(INA219::ADC_128SAMP);


  pinMode(pwmPin, OUTPUT);
  digitalWrite(pwmPin, LOW);





  // Blink LED
  blinkLED(3, 400);
}

//                 E n d  o f  s e t u p ( )
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||




//*****************************************************************************************************************************************
//**************************************************************MAIN LOOP******************************************************************
//*****************************************************************************************************************************************

void loop() {
  client.loop();
  currentMillis = millis();

  inaCurrent = 0;
  for (int i = 1; i < 11; i++) {
    inaCurrent += ina219.shuntCurrent();
  }
  inaCurrent = inaCurrent / 10 * 1000;
  inaVoltage = ina219.busVoltage();

  if (inaCurrent < currentTarget) {
    //Serial.print("Going up       ");
    //Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
    pulseWidth++;
    if (pulseWidth > 1023) pulseWidth = 1023;
    if (inaVoltage < 2.8) pulseWidth = 0;
  }
  else if (inaCurrent > currentTarget) {
    ///Serial.print("Going down");
    //Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
    pulseWidth--;
    if (pulseWidth < 0) pulseWidth = 0;
    if (inaVoltage < 2.8) pulseWidth = 0;
  }
  analogWrite(pwmPin, pulseWidth);



  send_Data();
  blinky();
}
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||END Main Loop**************************************************************
