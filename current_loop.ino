void current_loop() {



  currentArray[0] = ina219.shuntCurrent() * 1000;
  voltageArray[0] = ina219.busVoltage();

  for (int i = 0; i < 9; i++) {
    cTotal = cTotal + currentArray[i];
    vTotal = vTotal + voltageArray[i]  ;

    currentArray[i + 1] = currentArray[i];
    voltageArray[i + 1] = voltageArray[i];
  }

  inaCurrent = cTotal / 10;
  inaVoltage = vTotal / 10;
  cTotal = 0;
  vTotal = 0;

  inaCurrent = ina219.shuntCurrent() * 1000;
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

  ina219.recalibrate();
  ina219.reconfig();
}
