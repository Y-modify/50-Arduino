/*************************************
  ControlCore - YamaX Arduino Core v3.0
  Provides servo controlling feature
  made by coord.e, Y-modify
  Copyright © 2017 Y-modify All Rights Reserved.
*************************************/

uint8_t chToIdx(char servoCh) {
  return servoCh - 'A';
}

/*****Core Functions*****/
uint8_t setServo(char ch, int8_t deg) {
  return setServoIdx(chToIdx(ch), deg);
}

uint8_t setServoIdx(uint8_t idx, int8_t deg) {
  current_degrees[idx] = deg;
  return setServoPulse(ports(idx), deg)
}

uint8_t setServoPulse(uint8_t n, int degress) {
  degMake(n, 2, 0); //make stX
  degMake(n, 4, 0); //make nstX
  if (stX + degress > 180) {
    print_c("over 180 degs.");
    return false;
  }
  if (stX + degress < 0) {
    print_c("under 0 degs");
    return false;
  }
  double pulse = map(stX + degress, 0, 180, SERVOMIN, SERVOMAX);
  // Serial.println(pulse);
  if (n < 16) {
    pwm1.setPWM(n, 0, pulse);
  } else if (n < 32) {
    pwm2.setPWM(n - 16, 0, pulse);
  } else {
    return false;
  }
  return pulse;
}

bool setLEDr(uint16_t value) {
  if (value > 4095 || value < 0)
    return false;
  pwm1.setPWM(LEDr, 0, value);
}

bool setLEDb(uint16_t value) {
  if (value > 4095 || value < 0)
    return false;
  pwm1.setPWM(LEDb, 0, value);
}

bool setLEDg(uint16_t value) {
  if (value > 4095 || value < 0)
    return false;
  pwm1.setPWM(LEDg, 0, value);
}


void smoothmotion(char ch, float degress, uint8_t times, uint8_t now) { //times:cutting time  now:now cut
  float cut = 0;
  uint8_t idx = chToIdx(ch);
  degMake(idx, 1, 0); //make formerDeg
  degMake(idx, 4, 0); //make nstX
  degress = degress * nstX;
  cut = (degress - formerDeg) / (times - now + 1);
  setServoIdx(idx, formerDeg + cut);
  degMake(idx, 3, formerDeg + cut); //update fX
}

void degMake(uint8_t idx, uint8_t mode, float val) {
  /* mode1: make formerDeg
     mode2: make stX
     mode3: update fX
     mode4: make nstX
  */
  switch(mode) {
    case 1:
      formerDeg = current_degrees[idx];
      break;
    case 2:
      stX = stand_positions[idx];
      break;
    case 3:
      current_degrees[idx] = val;
      break;
    case 4:
      nstX = calibration[idx];
      break;
  }
}


void setdeg(uint8_t n, int degress) {
  //degMake(n, 2, 0); //make stX
  int times = 20;
  for (int i = 1; i <= times; i++) {
    //smoothmotion(n, degress - stX, times, i);
    smoothmotion(n, degress, times, i);
    delay(20);
  }
  print_c("set deg finished");
  Serial.print(n);
  Serial.print("\t");
  Serial.println(degress);
}
