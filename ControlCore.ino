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


void smoothmotion(uint8_t n, float degress, uint8_t times, uint8_t now) { //times:cutting time  now:now cut
  float cut = 0;
  degMake(n, 1, 0); //make formerDeg
  degMake(n, 4, 0); //make nstX
  degress = degress * nstX;
  cut = (degress - formerDeg) / (times - now + 1);
  setServoPulse(n, formerDeg + cut);
  degMake(n, 3, formerDeg + cut); //update fX
}

void degMake(uint8_t n, uint8_t mode, float val) {
  /* mode1: make formerDeg
     mode2: make stX
     mode3: update fX
     mode4: make nstX
  */
  switch (n) {
    case servoA:
      if (mode == 1)
        formerDeg = fA;
      else if (mode == 2)
        stX = stA;
      else if (mode == 3)
        fA = val;
      else if (mode == 4)
        nstX = nstA;
      break;

    case servoB:
      if (mode == 1)
        formerDeg = fB;
      else if (mode == 2)
        stX = stB;
      else if (mode == 3)
        fB = val;
      else if (mode == 4)
        nstX = nstB;
      break;

    case servoC:
      if (mode == 1)
        formerDeg = fC;
      else if (mode == 2)
        stX = stC;
      else if (mode == 3)
        fC = val;
      else if (mode == 4)
        nstX = nstC;
      break;

    case servoD:
      if (mode == 1)
        formerDeg = fD;
      else if (mode == 2)
        stX = stD;
      else if (mode == 3)
        fD = val;
      else if (mode == 4)
        nstX = nstD;
      break;

    case servoE:
      if (mode == 1)
        formerDeg = fE;
      else if (mode == 2)
        stX = stE;
      else if (mode == 3)
        fE = val;
      else if (mode == 4)
        nstX = nstE;
      break;

    case servoF:
      if (mode == 1)
        formerDeg = fF;
      else if (mode == 2)
        stX = stF;
      else if (mode == 3)
        fF = val;
      else if (mode == 4)
        nstX = nstF;
      break;

    case servoG:
      if (mode == 1)
        formerDeg = fG;
      else if (mode == 2)
        stX = stG;
      else if (mode == 3)
        fG = val;
      else if (mode == 4)
        nstX = nstG;
      break;

    case servoH:
      if (mode == 1)
        formerDeg = fH;
      else if (mode == 2)
        stX = stH;
      else if (mode == 3)
        fH = val;
      else if (mode == 4)
        nstX = nstH;
      break;

    case servoI:
      if (mode == 1)
        formerDeg = fI;
      else if (mode == 2)
        stX = stI;
      else if (mode == 3)
        fI = val;
      else if (mode == 4)
        nstX = nstI;
      break;

    case servoK:
      if (mode == 1)
        formerDeg = fK;
      else if (mode == 2)
        stX = stK;
      else if (mode == 3)
        fK = val;
      else if (mode == 4)
        nstX = nstK;
      break;

    case servoL:
      if (mode == 1)
        formerDeg = fL;
      else if (mode == 2)
        stX = stL;
      else if (mode == 3)
        fL = val;
      else if (mode == 4)
        nstX = nstL;
      break;

    case servoM:
      if (mode == 1)
        formerDeg = fM;
      else if (mode == 2)
        stX = stM;
      else if (mode == 3)
        fM = val;
      else if (mode == 4)
        nstX = nstM;
      break;

    case servoN:
      if (mode == 1)
        formerDeg = fN;
      else if (mode == 2)
        stX = stN;
      else if (mode == 3)
        fN = val;
      else if (mode == 4)
        nstX = nstN;
      break;

    case servoO:
      if (mode == 1)
        formerDeg = fO;
      else if (mode == 2)
        stX = stO;
      else if (mode == 3)
        fO = val;
      else if (mode == 4)
        nstX = nstO;
      break;

    case servoQ:
      if (mode == 1)
        formerDeg = fQ;
      else if (mode == 2)
        stX = stQ;
      else if (mode == 3)
        fQ = val;
      else if (mode == 4)
        nstX = nstQ;
      break;

    case servoR:
      if (mode == 1)
        formerDeg = fR;
      else if (mode == 2)
        stX = stR;
      else if (mode == 3)
        fR = val;
      else if (mode == 4)
        nstX = nstR;
      break;

    case servoS:
      if (mode == 1)
        formerDeg = fS;
      else if (mode == 2)
        stX = stS;
      else if (mode == 3)
        fS = val;
      else if (mode == 4)
        nstX = nstS;
      break;

    case servoT:
      if (mode == 1)
        formerDeg = fT;
      else if (mode == 2)
        stX = stT;
      else if (mode == 3)
        fT = val;
      else if (mode == 4)
        nstX = nstT;
      break;

    case servoU:
      if (mode == 1)
        formerDeg = fU;
      else if (mode == 2)
        stX = stU;
      else if (mode == 3)
        fU = val;
      else if (mode == 4)
        nstX = nstU;
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
