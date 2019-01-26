//_____________________________________________________________

//                     callback ( ) - runs when MQTT message comes in
//*******************************************************
void callback(char* topic, byte * payload, unsigned int length) {

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  String readString = "";
  for (int i = 0; i < length; i++) {
    delay(2);  //delay to allow byte to arrive in input buffer
    char c = payload[i];
    readString += c;
  }
  Serial.print("Message:");
  Serial.println(readString);

  if (strcmp(topic, "esp/control") == 0) {  //0 is true


    switch  (readString.toInt()) {  // Node red sends intigers to topic esp/control from dash buttons
      case 1:
        { sendMQTT("esp/text", readString);
          blinkLED(2, 300);
          String messStr = String(repeatBlink);
          Serial.println(messStr);
          sendMQTT("esp/text", messStr);
          delayTime = 500;
        }
        break;
      case 2:
        sendMQTT("esp/text", readString);
        break;
      case 3:
        sendMQTT("esp/text", readString);
        repeatBlink = 1;
        send_Data_Flag = 1;
        break;
      case 4:
        sendMQTT("esp/text", readString);
        repeatBlink = 0;
        send_Data_Flag = 0;
        break;
      case 5:
        sendMQTT("esp/text", readString);
        break;
      case 6:
        sendMQTT("esp/text", readString);
        break;
      case 7:
        sendMQTT("esp/text", readString);
        break;
      case 8:
        sendMQTT("esp/text", "Restarting ESP");
        delay(10);
        ESP.restart();
        break;
    }
  }
  if (strcmp(topic, "esp/controlcurrent") == 0) {  //0 is true
     currentTarget = readString.toInt();
     Serial.println(readString.toInt());
     Serial.println(topic);
  }
}
