/*************************************
  Actions - YamaX Arduino Core v3.0
  Motor control block
  made by Nyanyan, Y-modify
  Copyright © 2017 Y-modify All Rights Reserved.

  define "stand"'s value, then +- to these values
*************************************/

#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

/*****Pulse Adjust*****/
constexpr uint16_t SERVOMIN = 150; // on 0°,0~4095
constexpr uint16_t SERVOMAX = 600; // on 180°,0~4095
constexpr uint16_t LEDREDMAX = 4095;
constexpr uint16_t LEDGREENMAX = 2400;
constexpr uint16_t LEDBLUEMAX = 2300;

/*****Object Making*****/
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40); // 1
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41); // 2

/*****Servo Ports Definition*****/

#define servoA 0

#define servoB 1
#define servoC 2
#define servoD 3

#define servoE 30 // 14
#define servoF 29 // 13
#define servoG 28 // 12

#define servoH 8
#define servoI 9

#define servoK 16 // 0
#define servoL 17 // 1
#define servoM 18 // 2
#define servoN 19 // 3
#define servoO 20 // 4

#define servoQ 15
#define servoR 14
#define servoS 13
#define servoT 12
#define servoU 11

#define LEDr 3
#define LEDg 2
#define LEDb 1

/**standDefinition**/
#define stA 75 //+100    -80

//左腕
#define stB 90 //+110   -70
#define stC 92 //+100   -80
#define stD 87 //+30    -140

//右腕
#define stE 90 //+90    -90
#define stF 85 //+110   -70
#define stG 93 //+160   -20

//腰
#define stH 90  //+100   -80
#define stI 90 //+70    -110

//右足
#define stK 70 //+105   -75
#define stL 125  //+110   -70
#define stM 85//+80    -100
#define stN 85 //+80    -100
#define stO 85 //+150   -30

//左足
#define stQ 70  //+95    -85
#define stR 70 //+65    -105
#define stS 80  //+100   -80
#define stT 83 //+120   -60*****************
#define stU 90 //+45    -135



/****calibration****/
float nstA = 1; //+100    -80

//左腕
float nstB = 1; //+110   -70
float nstC = 1; //+100   -80
float nstD = 1; //+30    -140

//右腕
float nstE = 1; //+90    -90
float nstF = 1; //+110   -70
float nstG = 1; //+160   -20

//腰
float nstH = 1; //+100   -80
float nstI = 1; //+70    -110

//右足
float nstK = 1; //+105   -75
float nstL = 1; //+110   -70
float nstM = 0.9; //+80    -100
float nstN = 1; //+80    -100
float nstO = 1; //+150   -30

//左足
float nstQ = 1; //+95    -85
float nstR = 1; //+65    -105
float nstS = 1; //+100   -80
float nstT = 1; //+120   -60
float nstU = 1; //+45    -135



int fA = 0;
int fB = 0;
int fC = 0;
int fD = 0;
int fE = 0;
int fF = 0;
int fG = 0;
int fH = 0;
int fI = 0;
int fK = 0;
int fL = 0;
int fM = 0;
int fN = 0;
int fO = 0;
int fQ = 0;
int fR = 0;
int fS = 0;
int fT = 0;
int fU = 0;

float formerDeg = 0;
int stX = 0;
float nstX = 0;



/*****Initialize Servo Driver*****/
void ServoInit() {
  pwm1.begin();
  pwm2.begin();
  pwm1.setPWMFreq(60); // Analog servos run at ~60 Hz updates
  pwm2.setPWMFreq(60); // Analog servos run at ~60 Hz updates
  delay(100);
}



/********************Base Functions********************/
void stand() {
  setServoPulse(servoA, 0); //首

  setServoPulse(servoB, 0);
  setServoPulse(servoC, 0);
  setServoPulse(servoD, 0); //左腕

  setServoPulse(servoE, 0);
  setServoPulse(servoF, 0);
  setServoPulse(servoG, 0); //右腕

  setServoPulse(servoH, 0);
  setServoPulse(servoI, 0); //腰

  setServoPulse(servoK, 0);
  setServoPulse(servoL, 0); // 170
  setServoPulse(servoM, 0); // 170
  setServoPulse(servoN, 0);
  setServoPulse(servoO, 0); //右足

  setServoPulse(servoQ, 0);
  setServoPulse(servoR, 0); // 30
  setServoPulse(servoS, 0); // 30
  setServoPulse(servoT, 0);
  setServoPulse(servoU, 0); //左足

  fA = 0;
  fB = 0;
  fC = 0;
  fD = 0;
  fE = 0;
  fF = 0;
  fG = 0;
  fH = 0;
  fI = 0;
  fK = 0;
  fL = 0;
  fM = 0;
  fN = 0;
  fO = 0;
  fQ = 0;
  fR = 0;
  fS = 0;
  fT = 0;
  fU = 0;
}

void reset(int times, int frame) {
  for (int i = 1; i <= times; i++) {
    smoothmotion(servoA, 0 , times, i); //首

    smoothmotion(servoB, 0 , times, i);
    smoothmotion(servoC, 0 , times, i);
    smoothmotion(servoD, 0 , times, i); //左腕

    smoothmotion(servoE, 0 , times, i);
    smoothmotion(servoF, 0 , times, i);
    smoothmotion(servoG, 0 , times, i); //右腕

    smoothmotion(servoH, 0 , times, i);
    smoothmotion(servoI, 0 , times, i); //腰

    smoothmotion(servoK, 0 , times, i);
    smoothmotion(servoL, 0 , times, i);
    smoothmotion(servoM, 0 , times, i);
    smoothmotion(servoN, 0 , times, i);
    smoothmotion(servoO, 0 , times, i); //右脚

    smoothmotion(servoQ, 0 , times, i);
    smoothmotion(servoR, 0 , times, i);
    smoothmotion(servoS, 0 , times, i);
    smoothmotion(servoT, 0 , times, i);
    smoothmotion(servoU, 0 , times, i); //左脚
    delay(frame);
  }
}

void bowing() {
  int times = 20;
  for (int i = 1; i <= times; i++) {
    smoothmotion(servoA, 0 , times, i); //首

    smoothmotion(servoB, 0 , times, i);
    smoothmotion(servoC, 0 , times, i);
    smoothmotion(servoD, 0 , times, i); //左腕

    smoothmotion(servoE, 0 , times, i);
    smoothmotion(servoF, 0 , times, i);
    smoothmotion(servoG, 0 , times, i); //右腕

    smoothmotion(servoH, 0 , times, i);
    smoothmotion(servoI, 45 , times, i); //腰

    smoothmotion(servoK, 0 , times, i);
    smoothmotion(servoL, 20 , times, i);
    smoothmotion(servoM, -10 , times, i);
    smoothmotion(servoN, 0 , times, i);
    smoothmotion(servoO, 0 , times, i); //右脚

    smoothmotion(servoQ, 0 , times, i);
    smoothmotion(servoR, -20 , times, i);
    smoothmotion(servoS, 10 , times, i);
    smoothmotion(servoT, 0 , times, i);
    smoothmotion(servoU, 0 , times, i); //左脚
    delay(20);
  }
}

void crouch() {
  int times = 20;
  for (int i = 1; i <= times; i++) {
    smoothmotion(servoA, 0 , times, i); //首

    smoothmotion(servoB, 0 , times, i);
    smoothmotion(servoC, 0 , times, i);
    smoothmotion(servoD, 0 , times, i); //左腕

    smoothmotion(servoE, 0 , times, i);
    smoothmotion(servoF, 0 , times, i);
    smoothmotion(servoG, 0 , times, i); //右腕

    smoothmotion(servoH, 0 , times, i);
    smoothmotion(servoI, 0 , times, i); //腰

    smoothmotion(servoK, 0 , times, i);
    smoothmotion(servoL, -20 , times, i);
    smoothmotion(servoM, -40 , times, i);
    smoothmotion(servoN, -20 , times, i);
    smoothmotion(servoO, 0 , times, i); //右脚

    smoothmotion(servoQ, 0 , times, i);
    smoothmotion(servoR, 20 , times, i);
    smoothmotion(servoS, 40 , times, i);
    smoothmotion(servoT, 20 , times, i);
    smoothmotion(servoU, 0 , times, i); //左脚
    delay(20);
  }
}

/******************************Walking******************************/
void walkLUp(int frame, int hip) {
  int times = 15;
  for (int i = 1; i <= times; i++) {
    smoothmotion(servoA, 0 , times, i); //首

    smoothmotion(servoB, 0 , times, i);
    smoothmotion(servoC, 0 , times, i);
    smoothmotion(servoD, 0 , times, i); //左腕

    smoothmotion(servoE, 0 , times, i);
    smoothmotion(servoF, 0 , times, i);
    smoothmotion(servoG, 0 , times, i); //右腕

    smoothmotion(servoH, -10 , times, i);
    smoothmotion(servoI, hip , times, i); //腰

    smoothmotion(servoK, 5 , times, i);
    smoothmotion(servoL, -25 , times, i);
    smoothmotion(servoM, -60 , times, i);
    smoothmotion(servoN, -40 , times, i);
    smoothmotion(servoO, -15 , times, i); //右脚

    smoothmotion(servoQ, 0 , times, i);
    smoothmotion(servoR, 45 , times, i);
    smoothmotion(servoS, 60 , times, i);
    smoothmotion(servoT, 20 , times, i);
    smoothmotion(servoU, -15 , times, i); //左脚
    delay(frame);
  }
}

void walkRUp(int frame, int hip) {
  int times = 15;
  for (int i = 1; i <= times; i++) {
    smoothmotion(servoA, 0 , times, i); //首

    smoothmotion(servoB, 0 , times, i);
    smoothmotion(servoC, 0 , times, i);
    smoothmotion(servoD, 0 , times, i); //左腕

    smoothmotion(servoE, 0 , times, i);
    smoothmotion(servoF, 0 , times, i);
    smoothmotion(servoG, 0 , times, i); //右腕

    smoothmotion(servoH, 10 , times, i);
    smoothmotion(servoI, hip , times, i); //腰

    smoothmotion(servoK, 0 , times, i);
    smoothmotion(servoL, -45 , times, i);
    smoothmotion(servoM, -60 , times, i);
    smoothmotion(servoN, -20 , times, i);
    smoothmotion(servoO, 15 , times, i); //右脚

    smoothmotion(servoQ, -5 , times, i);
    smoothmotion(servoR, 25 , times, i);
    smoothmotion(servoS, 60 , times, i);
    smoothmotion(servoT, 40 , times, i);
    smoothmotion(servoU, 15 , times, i); //左脚
    delay(frame);
  }
}

void walkLFoward(int frame, int hip) {
  int times = 10;
  for (int i = 1; i <= times; i++) {
    smoothmotion(servoA, 0 , times, i); //首

    smoothmotion(servoB, 0 , times, i);
    smoothmotion(servoC, 0 , times, i);
    smoothmotion(servoD, 0 , times, i); //左腕

    smoothmotion(servoE, 0 , times, i);
    smoothmotion(servoF, 0 , times, i);
    smoothmotion(servoG, 0 , times, i); //右腕

    smoothmotion(servoH, -10 , times, i);
    smoothmotion(servoI, hip , times, i); //腰

    smoothmotion(servoK, 0 , times, i);
    smoothmotion(servoL, -25 , times, i);
    smoothmotion(servoM, -60 , times, i);
    smoothmotion(servoN, -40 , times, i);
    smoothmotion(servoO, 0 , times, i); //右脚

    smoothmotion(servoQ, 0 , times, i);
    smoothmotion(servoR, 45 , times, i);
    smoothmotion(servoS, 60 , times, i);
    smoothmotion(servoT, 20 , times, i);
    smoothmotion(servoU, 0 , times, i); //左脚
    delay(frame);
  }
}

void walkRFoward(int frame, int hip) {
  int times = 10;
  for (int i = 1; i <= times; i++) {
    smoothmotion(servoA, 0 , times, i); //首

    smoothmotion(servoB, 0 , times, i);
    smoothmotion(servoC, 0 , times, i);
    smoothmotion(servoD, 0 , times, i); //左腕

    smoothmotion(servoE, 0 , times, i);
    smoothmotion(servoF, 0 , times, i);
    smoothmotion(servoG, 0 , times, i); //右腕

    smoothmotion(servoH, 10 , times, i);
    smoothmotion(servoI, hip , times, i); //腰

    smoothmotion(servoK, 0 , times, i);
    smoothmotion(servoL, -45 , times, i);
    smoothmotion(servoM, -60 , times, i);
    smoothmotion(servoN, -20 , times, i);
    smoothmotion(servoO, 0 , times, i); //右脚

    smoothmotion(servoQ, 0 , times, i);
    smoothmotion(servoR, 25 , times, i);
    smoothmotion(servoS, 60 , times, i);
    smoothmotion(servoT, 40 , times, i);
    smoothmotion(servoU, 0 , times, i); //左脚
    delay(frame);
  }
}

void walkLDown(int frame, int hip) {
  int times = 10;
  for (int i = 1; i <= times; i++) {
    smoothmotion(servoA, 0 , times, i); //首

    smoothmotion(servoB, 0 , times, i);
    smoothmotion(servoC, 0 , times, i);
    smoothmotion(servoD, 0 , times, i); //左腕

    smoothmotion(servoE, 0 , times, i);
    smoothmotion(servoF, 0 , times, i);
    smoothmotion(servoG, 0 , times, i); //右腕

    smoothmotion(servoH, 0 , times, i);
    smoothmotion(servoI, hip , times, i); //腰

    smoothmotion(servoK, -5 , times, i);
    smoothmotion(servoL, -25 , times, i);
    smoothmotion(servoM, -50 , times, i);
    smoothmotion(servoN, -30 , times, i);
    smoothmotion(servoO, 15 , times, i); //右脚

    smoothmotion(servoQ, 0 , times, i);
    smoothmotion(servoR, 35 , times, i);
    smoothmotion(servoS, 50 , times, i);
    smoothmotion(servoT, 20 , times, i);
    smoothmotion(servoU, 15 , times, i); //左脚
    delay(frame);
  }
}

void walkRDown(int frame, int hip) {
  int times = 10;
  for (int i = 1; i <= times; i++) {
    smoothmotion(servoA, 0 , times, i); //首

    smoothmotion(servoB, 0 , times, i);
    smoothmotion(servoC, 0 , times, i);
    smoothmotion(servoD, 0 , times, i); //左腕

    smoothmotion(servoE, 0 , times, i);
    smoothmotion(servoF, 0 , times, i);
    smoothmotion(servoG, 0 , times, i); //右腕

    smoothmotion(servoH, 0 , times, i);
    smoothmotion(servoI, hip , times, i); //腰

    smoothmotion(servoK, 0 , times, i);
    smoothmotion(servoL, -35 , times, i);
    smoothmotion(servoM, -50 , times, i);
    smoothmotion(servoN, -20 , times, i);
    smoothmotion(servoO, -15 , times, i); //右脚

    smoothmotion(servoQ, 5 , times, i);
    smoothmotion(servoR, 25 , times, i);
    smoothmotion(servoS, 50 , times, i);
    smoothmotion(servoT, 30 , times, i);
    smoothmotion(servoU, -15 , times, i); //左脚
    delay(frame);
  }
}





/******************************turn******************************/
void turnLUp(int frame, int hip) {
  int times = 15;
  for (int i = 1; i <= times; i++) {
    smoothmotion(servoA, 0 , times, i); //首

    smoothmotion(servoB, 0 , times, i);
    smoothmotion(servoC, 0 , times, i);
    smoothmotion(servoD, 0 , times, i); //左腕

    smoothmotion(servoE, 0 , times, i);
    smoothmotion(servoF, 0 , times, i);
    smoothmotion(servoG, 0 , times, i); //右腕

    smoothmotion(servoH, 0 , times, i);
    smoothmotion(servoI, hip , times, i); //腰

    smoothmotion(servoK, 5 , times, i);
    smoothmotion(servoL, -25 , times, i);
    smoothmotion(servoM, -60 , times, i);
    smoothmotion(servoN, -40 , times, i);
    smoothmotion(servoO, 0 , times, i); //右脚

    smoothmotion(servoQ, 0 , times, i);
    smoothmotion(servoR, 20 , times, i);
    smoothmotion(servoS, 40 , times, i);
    smoothmotion(servoT, 20 , times, i);
    smoothmotion(servoU, 15 , times, i); //左脚
    delay(frame);

  }
}

void turnRUp(int frame, int hip) {
  int times = 15;
  for (int i = 1; i <= times; i++) {
    smoothmotion(servoA, 0 , times, i); //首

    smoothmotion(servoB, 0 , times, i);
    smoothmotion(servoC, 0 , times, i);
    smoothmotion(servoD, 0 , times, i); //左腕

    smoothmotion(servoE, 0 , times, i);
    smoothmotion(servoF, 0 , times, i);
    smoothmotion(servoG, 0 , times, i); //右腕

    smoothmotion(servoH, 0 , times, i);
    smoothmotion(servoI, hip , times, i); //腰

    smoothmotion(servoK, 0 , times, i);
    smoothmotion(servoL, -20 , times, i);
    smoothmotion(servoM, -40 , times, i);
    smoothmotion(servoN, -20 , times, i);
    smoothmotion(servoO, -15 , times, i); //右脚

    smoothmotion(servoQ, -5 , times, i);
    smoothmotion(servoR, 25 , times, i);
    smoothmotion(servoS, 60 , times, i);
    smoothmotion(servoT, 40 , times, i);
    smoothmotion(servoU, 0 , times, i); //左脚
    delay(frame);
  }
}

void turnLDown(int frame, int hip) {
  int times = 20;
  for (int i = 1; i <= times; i++) {
    smoothmotion(servoA, 0 , times, i); //首

    smoothmotion(servoB, 0 , times, i);
    smoothmotion(servoC, 0 , times, i);
    smoothmotion(servoD, 0 , times, i); //左腕

    smoothmotion(servoE, 0 , times, i);
    smoothmotion(servoF, 0 , times, i);
    smoothmotion(servoG, 0 , times, i); //右腕

    smoothmotion(servoH, 0 , times, i);
    smoothmotion(servoI, hip , times, i); //腰

    smoothmotion(servoK, -5 , times, i);
    smoothmotion(servoL, -20 , times, i);
    smoothmotion(servoM, -40 , times, i);
    smoothmotion(servoN, -20 , times, i);
    smoothmotion(servoO, 0 , times, i); //右脚

    smoothmotion(servoQ, 0 , times, i);
    smoothmotion(servoR, 35 , times, i);
    smoothmotion(servoS, 50 , times, i);
    smoothmotion(servoT, 20 , times, i);
    smoothmotion(servoU, 15 , times, i); //左脚
    delay(frame);
  }
}

void turnRDown(int frame, int hip) {
  int times = 20;
  for (int i = 1; i <= times; i++) {
    smoothmotion(servoA, 0 , times, i); //首

    smoothmotion(servoB, 0 , times, i);
    smoothmotion(servoC, 0 , times, i);
    smoothmotion(servoD, 0 , times, i); //左腕

    smoothmotion(servoE, 0 , times, i);
    smoothmotion(servoF, 0 , times, i);
    smoothmotion(servoG, 0 , times, i); //右腕

    smoothmotion(servoH, 0 , times, i);
    smoothmotion(servoI, hip , times, i); //腰

    smoothmotion(servoK, 0 , times, i);
    smoothmotion(servoL, -35 , times, i);
    smoothmotion(servoM, -50 , times, i);
    smoothmotion(servoN, -20 , times, i);
    smoothmotion(servoO, -15 , times, i); //右脚

    smoothmotion(servoQ, 5 , times, i);
    smoothmotion(servoR, 20 , times, i);
    smoothmotion(servoS, 40 , times, i);
    smoothmotion(servoT, 20 , times, i);
    smoothmotion(servoU, 0 , times, i); //左脚
    delay(frame);
  }
}





/************************stand on one leg************************/
void standonOneLegFirst(int frame) {//stand with left leg
  int times = 40;
  for (int i = 1; i <= times; i++) {
    smoothmotion(servoA, 0 , times, i); //首

    smoothmotion(servoB, 0 , times, i);
    smoothmotion(servoC, 0 , times, i);
    smoothmotion(servoD, 0 , times, i); //左腕

    smoothmotion(servoE, 0 , times, i);
    smoothmotion(servoF, 0 , times, i);
    smoothmotion(servoG, 0 , times, i); //右腕

    smoothmotion(servoH, 0 , times, i);
    smoothmotion(servoI, 0 , times, i); //腰

    smoothmotion(servoK, -10 , times, i);
    smoothmotion(servoL, 0 , times, i);
    smoothmotion(servoM, 0 , times, i);
    smoothmotion(servoN, 0 , times, i);
    smoothmotion(servoO, 10 , times, i); //右脚

    smoothmotion(servoQ, -10 , times, i);
    smoothmotion(servoR, 0 , times, i);
    smoothmotion(servoS, 0 , times, i);
    smoothmotion(servoT, 0 , times, i);
    smoothmotion(servoU, 10 , times, i); //左脚
    delay(frame);
  }
}

void standonOneLegSecond(int frame) {//stand with left leg
  int times = 50;
  for (int i = 1; i <= times; i++) {
    smoothmotion(servoA, 0 , times, i); //首

    smoothmotion(servoB, 0 , times, i);
    smoothmotion(servoC, 0 , times, i);
    smoothmotion(servoD, 0 , times, i); //左腕

    smoothmotion(servoE, 0 , times, i);
    smoothmotion(servoF, 0 , times, i);
    smoothmotion(servoG, 0 , times, i); //右腕

    smoothmotion(servoH, 0 , times, i);
    smoothmotion(servoI, -5 , times, i); //腰

    smoothmotion(servoK, 0 , times, i);
    smoothmotion(servoL, -30 , times, i);
    smoothmotion(servoM, -60 , times, i);
    smoothmotion(servoN, -30 , times, i);
    smoothmotion(servoO, 20 , times, i); //右脚

    smoothmotion(servoQ, 0 , times, i);
    smoothmotion(servoR, 0 , times, i);
    smoothmotion(servoS, 0 , times, i);
    smoothmotion(servoT, 0 , times, i);
    smoothmotion(servoU, 30 , times, i); //左脚
    delay(frame);
  }
}

void standonOneLegThird(int frame) {//stand with left leg
  int times = 50;
  for (int i = 1; i <= times; i++) {
    smoothmotion(servoA, 0 , times, i); //首

    smoothmotion(servoB, 0 , times, i);
    smoothmotion(servoC, 0 , times, i);
    smoothmotion(servoD, 0 , times, i); //左腕

    smoothmotion(servoE, 0 , times, i);
    smoothmotion(servoF, 0 , times, i);
    smoothmotion(servoG, 0 , times, i); //右腕

    smoothmotion(servoH, 0 , times, i);
    smoothmotion(servoI, -5 , times, i); //腰

    smoothmotion(servoK, -70 , times, i);
    smoothmotion(servoL, -30 , times, i);
    smoothmotion(servoM, -60 , times, i);
    smoothmotion(servoN, -30 , times, i);
    smoothmotion(servoO, 10 , times, i); //右脚

    smoothmotion(servoQ, 0 , times, i);
    smoothmotion(servoR, 0 , times, i);
    smoothmotion(servoS, 0 , times, i);
    smoothmotion(servoT, 0 , times, i);
    smoothmotion(servoU, 30 , times, i); //左脚
    delay(frame);
  }
}

void standonOneLegFourth(int frame) {//stand with left leg
  int times = 50;
  for (int i = 1; i <= times; i++) {
    smoothmotion(servoA, 0 , times, i); //首

    smoothmotion(servoB, 0 , times, i);
    smoothmotion(servoC, -80 , times, i);
    smoothmotion(servoD, 0 , times, i); //左腕

    smoothmotion(servoE, 0 , times, i);
    smoothmotion(servoF, 80 , times, i);
    smoothmotion(servoG, 0 , times, i); //右腕

    smoothmotion(servoH, 0 , times, i);
    smoothmotion(servoI, -5 , times, i); //腰

    smoothmotion(servoK, -70 , times, i);
    smoothmotion(servoL, 0 , times, i);
    smoothmotion(servoM, 0 , times, i);
    smoothmotion(servoN, 0 , times, i);
    smoothmotion(servoO, 0 , times, i); //右脚

    smoothmotion(servoQ, 0 , times, i);
    smoothmotion(servoR, 0 , times, i);
    smoothmotion(servoS, 0 , times, i);
    smoothmotion(servoT, 0 , times, i);
    smoothmotion(servoU, 30 , times, i); //左脚
    delay(frame);
  }
}



/******************************back******************************/

/******************************crab******************************/

/*****************************dogeza*****************************/
void seiza1() {
  for (int i = 0; i <= 10; i++) {
    setServoPulse(servoA, stA); //首

    setServoPulse(servoB, stB);
    setServoPulse(servoC, stC);
    setServoPulse(servoD, stD); //左腕

    setServoPulse(servoE, stE);
    setServoPulse(servoF, stF);
    setServoPulse(servoG, stG); //右腕

    setServoPulse(servoH, stH);
    setServoPulse(servoI, stI); //腰

    setServoPulse(servoK, stK);
    setServoPulse(servoL, stL - i * 3); //-20
    setServoPulse(servoM, stM + i * 7); //+40
    setServoPulse(servoN, stN + i * 4); //+20
    setServoPulse(servoO, stO);         //右足

    setServoPulse(servoQ, stQ);
    setServoPulse(servoR, stR + i * 3); //+20
    setServoPulse(servoS, stS - i * 7); //-40
    setServoPulse(servoT, stT - i * 4); //-20
    setServoPulse(servoU, stU);         //左足

    delay(40);
  }
}

/*****sit*****/

void sitdown1() {
  for (int i = 0; i <= 8; i++) {
    setServoPulse(servoA, stA); //首

    setServoPulse(servoB, stB);
    setServoPulse(servoC, stC);
    setServoPulse(servoD, stD); //左腕

    setServoPulse(servoE, stE);
    setServoPulse(servoF, stF);
    setServoPulse(servoG, stG); //右腕

    setServoPulse(servoH, stH);
    setServoPulse(servoI, stI - i * 4.5); //腰 -50

    setServoPulse(servoK, stK);
    setServoPulse(servoL, stL + i * 2); //+20
    setServoPulse(servoM, stM);
    setServoPulse(servoN, stN);
    setServoPulse(servoO, stO); //右足

    setServoPulse(servoQ, stQ);
    setServoPulse(servoR, stR - i * 2); //-20
    setServoPulse(servoS, stS);
    setServoPulse(servoT, stT);
    setServoPulse(servoU, stU); //左足

    delay(50);
  }
}

void sitdown2() {
  for (int i = 0; i <= 16; i++) {
    setServoPulse(servoA, stA); //首

    setServoPulse(servoB, stB);
    setServoPulse(servoC, stC);
    setServoPulse(servoD, stD); //左腕

    setServoPulse(servoE, stE);
    setServoPulse(servoF, stF);
    setServoPulse(servoG, stG); //右腕

    setServoPulse(servoH, stH);
    setServoPulse(servoI, stI - 36 - i * 2.25); //腰 -50

    setServoPulse(servoK, stK);
    setServoPulse(servoL, stL + 16 + i * 0.5); //+20
    setServoPulse(servoM, stM + i);
    setServoPulse(servoN, stN - i * 1.5);
    setServoPulse(servoO, stO); //右足

    setServoPulse(servoQ, stQ);
    setServoPulse(servoR, stR - 16 - i * 0.5); //-20
    setServoPulse(servoS, stS - i);
    setServoPulse(servoT, stT + i * 1.5);
    setServoPulse(servoU, stU); //左足

    delay(50);
  }
}

void situp1() {
  for (int i = 0; i <= 8; i++) {
    setServoPulse(servoA, stA); //首

    setServoPulse(servoB, stB);
    setServoPulse(servoC, stC);
    setServoPulse(servoD, stD); //左腕

    setServoPulse(servoE, stE);
    setServoPulse(servoF, stF);
    setServoPulse(servoG, stG); //右腕

    setServoPulse(servoH, stH);
    setServoPulse(servoI, stI - 72); //腰 -50

    setServoPulse(servoK, stK);
    setServoPulse(servoL, stL + 24 - i * 6); //+20
    setServoPulse(servoM, stM + 16 - i);
    setServoPulse(servoN, stN - 24);
    setServoPulse(servoO, stO); //右足

    setServoPulse(servoQ, stQ);
    setServoPulse(servoR, stR - 24 + i * 6); //-20
    setServoPulse(servoS, stS - 16 + i);
    setServoPulse(servoT, stT + 24);
    setServoPulse(servoU, stU); //左足

    delay(60);
  }
}

void situp2() {
  for (int i = 0; i <= 16; i++) {
    setServoPulse(servoA, stA); //首

    setServoPulse(servoB, stB);
    setServoPulse(servoC, stC);
    setServoPulse(servoD, stD); //左腕

    setServoPulse(servoE, stE);
    setServoPulse(servoF, stF);
    setServoPulse(servoG, stG); //右腕

    setServoPulse(servoH, stH);
    setServoPulse(servoI, stI - 72 + i * 4.5); //腰 -50

    setServoPulse(servoK, stK);
    setServoPulse(servoL, stL - 24 + i * 1.5); //+20
    setServoPulse(servoM, stM + 8 - i * 0.5);
    setServoPulse(servoN, stN - 24 + i * 1.5);
    setServoPulse(servoO, stO); //右足

    setServoPulse(servoQ, stQ);
    setServoPulse(servoR, stR + 24 - i * 1.5); //-20
    setServoPulse(servoS, stS - 8 + i * 0.5);
    setServoPulse(servoT, stT + 24 - i * 1.5);
    setServoPulse(servoU, stU); //左足

    delay(50);
  }
}
