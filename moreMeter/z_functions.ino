
//                     blinkLED ( )
//*******************************************************
void blinkLED(int repeat, int dl) {
  repeatBlink = repeat * 2;
  dlyBlink = dl;
}

void sendMQTT(String topic, String message) {
  char pubString[message.length() + 1];
  // make array message size plus /n
  message.toCharArray(pubString, message.length() + 1);
  char sendtopic[topic.length() + 1];
  topic.toCharArray(sendtopic, topic.length() + 1);
  //publish the data to MQTT
  client.publish(sendtopic, pubString);
}
//_____________________________________________________________

//                    Send_Data ( )
//*******************************************************
void send_Data() {


  //is it time to process the next state code?
  if (currentMillis - mySendDatamillis < dly_send_Data)
  {
    //No, it is not time
    return;
  }


  if (currentMillis - mySendDatamillis > dly_send_Data)
  {
    //Yes, it is now time

    sendMQTT("esp/current", String(inaCurrent));
    sendMQTT("esp/voltage", String(inaVoltage));
    if (send_Data_Flag > 0) {
      //Serial.println("******************");


      Serial.print("shunt current: ");
      Serial.print(inaCurrent);
      Serial.println(" mA");
      Serial.print(",");
      Serial.print("bus voltage:   ");
      Serial.println(inaVoltage * 1000, 4);
      Serial.println(" V");

      Serial.print("pulseWidth:    ");
      Serial.println(pulseWidth);

      Serial.print("currentTarget   ");
      Serial.println(currentTarget);

      //Serial.print(ina219.busPower() * 1000, 4);
      // Serial.println(" mW");

      //Serial.println(" ");
      //Serial.println(" ");
    }


    mySendDatamillis  = currentMillis;     //reset timing
  }



}//                E n d  o f  s e n d D a t a ( )

//___________________________________________________________


//                    blinky ( )
//*******************************************************
void blinky()
{
  if (repeatBlink > 0) {

    //is it time to process the next state code?
    if (currentMillis - myLEDmillis < dlyBlink)
    {
      //No, it is not time
      return;
    }

    //Yes, it is now time
    myLEDmillis = currentMillis;     //reset timing
    //Serial.print("repeatBlink = ");
    //Serial.println(repeatBlink);
    //state code
    switch (ledState)
    {
      case HIGH:
        digitalWrite(ledPin, LOW);    //turn LED on
        ledState = LOW;                //next state
        repeatBlink = repeatBlink - 1;
        break;


      case LOW:
        digitalWrite(ledPin, HIGH);   //turn LED off
        ledState = HIGH;                //next state
        repeatBlink = repeatBlink - 1;
        break;
    }      //End of switch/case for timer
  }      //End of if test for repeatBlink

  if (repeatBlink == 0) digitalWrite(ledPin, HIGH);    // make sure LED is off

}//                E n d  o f  u s i n g M i l l i s ( )

//___________________________________________________________
