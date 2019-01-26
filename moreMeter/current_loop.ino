void current_loop() {


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
}
