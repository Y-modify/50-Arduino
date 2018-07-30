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

const uint8_t ports[] = {
  0, // A
  1, // B
  2, // C
  3, // D

  30, // E // 14
  29, // F // 13
  28, // G // 12

  8, // H
  9, // I

  16, // K // 0
  17, // L // 1
  18, // M // 2
  19, // N // 3
  20, // O // 4

  15, // Q
  14, // R
  13, // S
  12, // T
  11  // U
};

#define LEDr 3
#define LEDg 2
#define LEDb 1

/**standDefinition**/
const uint8_t stand_positions[] = {
  75, // A //+100    -80

//左腕
  90, // B //+110   -70
  92, // C //+100   -80
  87, // D //+30    -140

//右腕
  90, // E //+90    -90
  85, // F //+110   -70
  93, // G //+160   -20

//腰
  90, // H  //+100   -80
  90, // I //+70    -110

//右足
  70, // K //+105   -75
  125, // L  //+110   -70
  85, // M//+80    -100
  85, // N //+80    -100
  85, // O //+150   -30

//左足
  70, // Q  //+95    -85
  70, // R //+65    -105
  80, // S  //+100   -80
  83, // T //+120   -60*****************
  90  // U //+45    -135
};


/****calibration****/
float calibrations[] = {
  1, // A; //+100    -80

//左腕
  1, // B; //+110   -70
  1, // C; //+100   -80
  1, // D; //+30    -140

//右腕
  1, // E; //+90    -90
  1, // F; //+110   -70
  1, // G; //+160   -20

//腰
  1, // H; //+100   -80
  1, // I; //+70    -110

//右足
  1, // K; //+105   -75
  1, // L; //+110   -70
  0, // M.9; //+80    -100
  1, // N; //+80    -100
  1, // O; //+150   -30

//左足
  1, // Q; //+95    -85
  1, // R; //+65    -105
  1, // S; //+100   -80
  1, // T; //+120   -60
  1  // U; //+45    -135
};


/* current degrees */
uint8_t current_degrees[] = {
  0, // A
  0, // B
  0, // C
  0, // D
  0, // E
  0, // F
  0, // G
  0, // H
  0, // I
  0, // K
  0, // L
  0, // M
  0, // N
  0, // O
  0, // Q
  0, // R
  0, // S
  0, // T
  0 // U
};

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
  for(uint8_t i=0; i < SERVONUM; i++) {
    setServoIdx(i, 0);
  }
}

void reset(int times, int frame) {
  for (int i = 1; i <= times; i++) {
    smoothmotion('A', 0 , times, i); //首

    smoothmotion('B', 0 , times, i);
    smoothmotion('C', 0 , times, i);
    smoothmotion('D', 0 , times, i); //左腕

    smoothmotion('E', 0 , times, i);
    smoothmotion('F', 0 , times, i);
    smoothmotion('G', 0 , times, i); //右腕

    smoothmotion('H', 0 , times, i);
    smoothmotion('I', 0 , times, i); //腰

    smoothmotion('K', 0 , times, i);
    smoothmotion('L', 0 , times, i);
    smoothmotion('M', 0 , times, i);
    smoothmotion('N', 0 , times, i);
    smoothmotion('O', 0 , times, i); //右脚

    smoothmotion('Q', 0 , times, i);
    smoothmotion('R', 0 , times, i);
    smoothmotion('S', 0 , times, i);
    smoothmotion('T', 0 , times, i);
    smoothmotion('U', 0 , times, i); //左脚
    delay(frame);
  }
}

void bowing() {
  int times = 20;
  for (int i = 1; i <= times; i++) {
    smoothmotion('A', 0 , times, i); //首

    smoothmotion('B', 0 , times, i);
    smoothmotion('C', 0 , times, i);
    smoothmotion('D', 0 , times, i); //左腕

    smoothmotion('E', 0 , times, i);
    smoothmotion('F', 0 , times, i);
    smoothmotion('G', 0 , times, i); //右腕

    smoothmotion('H', 0 , times, i);
    smoothmotion('I', 45 , times, i); //腰

    smoothmotion('K', 0 , times, i);
    smoothmotion('L', 20 , times, i);
    smoothmotion('M', -10 , times, i);
    smoothmotion('N', 0 , times, i);
    smoothmotion('O', 0 , times, i); //右脚

    smoothmotion('Q', 0 , times, i);
    smoothmotion('R', -20 , times, i);
    smoothmotion('S', 10 , times, i);
    smoothmotion('T', 0 , times, i);
    smoothmotion('U', 0 , times, i); //左脚
    delay(20);
  }
}

void crouch() {
  int times = 20;
  for (int i = 1; i <= times; i++) {
    smoothmotion('A', 0 , times, i); //首

    smoothmotion('B', 0 , times, i);
    smoothmotion('C', 0 , times, i);
    smoothmotion('D', 0 , times, i); //左腕

    smoothmotion('E', 0 , times, i);
    smoothmotion('F', 0 , times, i);
    smoothmotion('G', 0 , times, i); //右腕

    smoothmotion('H', 0 , times, i);
    smoothmotion('I', 0 , times, i); //腰

    smoothmotion('K', 0 , times, i);
    smoothmotion('L', -20 , times, i);
    smoothmotion('M', -40 , times, i);
    smoothmotion('N', -20 , times, i);
    smoothmotion('O', 0 , times, i); //右脚

    smoothmotion('Q', 0 , times, i);
    smoothmotion('R', 20 , times, i);
    smoothmotion('S', 40 , times, i);
    smoothmotion('T', 20 , times, i);
    smoothmotion('U', 0 , times, i); //左脚
    delay(20);
  }
}

/******************************Walking******************************/
void walkLUp(int frame, int hip) {
  int times = 15;
  for (int i = 1; i <= times; i++) {
    smoothmotion('A', 0 , times, i); //首

    smoothmotion('B', 0 , times, i);
    smoothmotion('C', 0 , times, i);
    smoothmotion('D', 0 , times, i); //左腕

    smoothmotion('E', 0 , times, i);
    smoothmotion('F', 0 , times, i);
    smoothmotion('G', 0 , times, i); //右腕

    smoothmotion('H', -10 , times, i);
    smoothmotion('I', hip , times, i); //腰

    smoothmotion('K', 5 , times, i);
    smoothmotion('L', -25 , times, i);
    smoothmotion('M', -60 , times, i);
    smoothmotion('N', -40 , times, i);
    smoothmotion('O', -15 , times, i); //右脚

    smoothmotion('Q', 0 , times, i);
    smoothmotion('R', 45 , times, i);
    smoothmotion('S', 60 , times, i);
    smoothmotion('T', 20 , times, i);
    smoothmotion('U', -15 , times, i); //左脚
    delay(frame);
  }
}

void walkRUp(int frame, int hip) {
  int times = 15;
  for (int i = 1; i <= times; i++) {
    smoothmotion('A', 0 , times, i); //首

    smoothmotion('B', 0 , times, i);
    smoothmotion('C', 0 , times, i);
    smoothmotion('D', 0 , times, i); //左腕

    smoothmotion('E', 0 , times, i);
    smoothmotion('F', 0 , times, i);
    smoothmotion('G', 0 , times, i); //右腕

    smoothmotion('H', 10 , times, i);
    smoothmotion('I', hip , times, i); //腰

    smoothmotion('K', 0 , times, i);
    smoothmotion('L', -45 , times, i);
    smoothmotion('M', -60 , times, i);
    smoothmotion('N', -20 , times, i);
    smoothmotion('O', 15 , times, i); //右脚

    smoothmotion('Q', -5 , times, i);
    smoothmotion('R', 25 , times, i);
    smoothmotion('S', 60 , times, i);
    smoothmotion('T', 40 , times, i);
    smoothmotion('U', 15 , times, i); //左脚
    delay(frame);
  }
}

void walkLFoward(int frame, int hip) {
  int times = 10;
  for (int i = 1; i <= times; i++) {
    smoothmotion('A', 0 , times, i); //首

    smoothmotion('B', 0 , times, i);
    smoothmotion('C', 0 , times, i);
    smoothmotion('D', 0 , times, i); //左腕

    smoothmotion('E', 0 , times, i);
    smoothmotion('F', 0 , times, i);
    smoothmotion('G', 0 , times, i); //右腕

    smoothmotion('H', -10 , times, i);
    smoothmotion('I', hip , times, i); //腰

    smoothmotion('K', 0 , times, i);
    smoothmotion('L', -25 , times, i);
    smoothmotion('M', -60 , times, i);
    smoothmotion('N', -40 , times, i);
    smoothmotion('O', 0 , times, i); //右脚

    smoothmotion('Q', 0 , times, i);
    smoothmotion('R', 45 , times, i);
    smoothmotion('S', 60 , times, i);
    smoothmotion('T', 20 , times, i);
    smoothmotion('U', 0 , times, i); //左脚
    delay(frame);
  }
}

void walkRFoward(int frame, int hip) {
  int times = 10;
  for (int i = 1; i <= times; i++) {
    smoothmotion('A', 0 , times, i); //首

    smoothmotion('B', 0 , times, i);
    smoothmotion('C', 0 , times, i);
    smoothmotion('D', 0 , times, i); //左腕

    smoothmotion('E', 0 , times, i);
    smoothmotion('F', 0 , times, i);
    smoothmotion('G', 0 , times, i); //右腕

    smoothmotion('H', 10 , times, i);
    smoothmotion('I', hip , times, i); //腰

    smoothmotion('K', 0 , times, i);
    smoothmotion('L', -45 , times, i);
    smoothmotion('M', -60 , times, i);
    smoothmotion('N', -20 , times, i);
    smoothmotion('O', 0 , times, i); //右脚

    smoothmotion('Q', 0 , times, i);
    smoothmotion('R', 25 , times, i);
    smoothmotion('S', 60 , times, i);
    smoothmotion('T', 40 , times, i);
    smoothmotion('U', 0 , times, i); //左脚
    delay(frame);
  }
}

void walkLDown(int frame, int hip) {
  int times = 10;
  for (int i = 1; i <= times; i++) {
    smoothmotion('A', 0 , times, i); //首

    smoothmotion('B', 0 , times, i);
    smoothmotion('C', 0 , times, i);
    smoothmotion('D', 0 , times, i); //左腕

    smoothmotion('E', 0 , times, i);
    smoothmotion('F', 0 , times, i);
    smoothmotion('G', 0 , times, i); //右腕

    smoothmotion('H', 0 , times, i);
    smoothmotion('I', hip , times, i); //腰

    smoothmotion('K', -5 , times, i);
    smoothmotion('L', -25 , times, i);
    smoothmotion('M', -50 , times, i);
    smoothmotion('N', -30 , times, i);
    smoothmotion('O', 15 , times, i); //右脚

    smoothmotion('Q', 0 , times, i);
    smoothmotion('R', 35 , times, i);
    smoothmotion('S', 50 , times, i);
    smoothmotion('T', 20 , times, i);
    smoothmotion('U', 15 , times, i); //左脚
    delay(frame);
  }
}

void walkRDown(int frame, int hip) {
  int times = 10;
  for (int i = 1; i <= times; i++) {
    smoothmotion('A', 0 , times, i); //首

    smoothmotion('B', 0 , times, i);
    smoothmotion('C', 0 , times, i);
    smoothmotion('D', 0 , times, i); //左腕

    smoothmotion('E', 0 , times, i);
    smoothmotion('F', 0 , times, i);
    smoothmotion('G', 0 , times, i); //右腕

    smoothmotion('H', 0 , times, i);
    smoothmotion('I', hip , times, i); //腰

    smoothmotion('K', 0 , times, i);
    smoothmotion('L', -35 , times, i);
    smoothmotion('M', -50 , times, i);
    smoothmotion('N', -20 , times, i);
    smoothmotion('O', -15 , times, i); //右脚

    smoothmotion('Q', 5 , times, i);
    smoothmotion('R', 25 , times, i);
    smoothmotion('S', 50 , times, i);
    smoothmotion('T', 30 , times, i);
    smoothmotion('U', -15 , times, i); //左脚
    delay(frame);
  }
}





/******************************turn******************************/
void turnLUp(int frame, int hip) {
  int times = 15;
  for (int i = 1; i <= times; i++) {
    smoothmotion('A', 0 , times, i); //首

    smoothmotion('B', 0 , times, i);
    smoothmotion('C', 0 , times, i);
    smoothmotion('D', 0 , times, i); //左腕

    smoothmotion('E', 0 , times, i);
    smoothmotion('F', 0 , times, i);
    smoothmotion('G', 0 , times, i); //右腕

    smoothmotion('H', 0 , times, i);
    smoothmotion('I', hip , times, i); //腰

    smoothmotion('K', 5 , times, i);
    smoothmotion('L', -25 , times, i);
    smoothmotion('M', -60 , times, i);
    smoothmotion('N', -40 , times, i);
    smoothmotion('O', 0 , times, i); //右脚

    smoothmotion('Q', 0 , times, i);
    smoothmotion('R', 20 , times, i);
    smoothmotion('S', 40 , times, i);
    smoothmotion('T', 20 , times, i);
    smoothmotion('U', 15 , times, i); //左脚
    delay(frame);

  }
}

void turnRUp(int frame, int hip) {
  int times = 15;
  for (int i = 1; i <= times; i++) {
    smoothmotion('A', 0 , times, i); //首

    smoothmotion('B', 0 , times, i);
    smoothmotion('C', 0 , times, i);
    smoothmotion('D', 0 , times, i); //左腕

    smoothmotion('E', 0 , times, i);
    smoothmotion('F', 0 , times, i);
    smoothmotion('G', 0 , times, i); //右腕

    smoothmotion('H', 0 , times, i);
    smoothmotion('I', hip , times, i); //腰

    smoothmotion('K', 0 , times, i);
    smoothmotion('L', -20 , times, i);
    smoothmotion('M', -40 , times, i);
    smoothmotion('N', -20 , times, i);
    smoothmotion('O', -15 , times, i); //右脚

    smoothmotion('Q', -5 , times, i);
    smoothmotion('R', 25 , times, i);
    smoothmotion('S', 60 , times, i);
    smoothmotion('T', 40 , times, i);
    smoothmotion('U', 0 , times, i); //左脚
    delay(frame);
  }
}

void turnLDown(int frame, int hip) {
  int times = 20;
  for (int i = 1; i <= times; i++) {
    smoothmotion('A', 0 , times, i); //首

    smoothmotion('B', 0 , times, i);
    smoothmotion('C', 0 , times, i);
    smoothmotion('D', 0 , times, i); //左腕

    smoothmotion('E', 0 , times, i);
    smoothmotion('F', 0 , times, i);
    smoothmotion('G', 0 , times, i); //右腕

    smoothmotion('H', 0 , times, i);
    smoothmotion('I', hip , times, i); //腰

    smoothmotion('K', -5 , times, i);
    smoothmotion('L', -20 , times, i);
    smoothmotion('M', -40 , times, i);
    smoothmotion('N', -20 , times, i);
    smoothmotion('O', 0 , times, i); //右脚

    smoothmotion('Q', 0 , times, i);
    smoothmotion('R', 35 , times, i);
    smoothmotion('S', 50 , times, i);
    smoothmotion('T', 20 , times, i);
    smoothmotion('U', 15 , times, i); //左脚
    delay(frame);
  }
}

void turnRDown(int frame, int hip) {
  int times = 20;
  for (int i = 1; i <= times; i++) {
    smoothmotion('A', 0 , times, i); //首

    smoothmotion('B', 0 , times, i);
    smoothmotion('C', 0 , times, i);
    smoothmotion('D', 0 , times, i); //左腕

    smoothmotion('E', 0 , times, i);
    smoothmotion('F', 0 , times, i);
    smoothmotion('G', 0 , times, i); //右腕

    smoothmotion('H', 0 , times, i);
    smoothmotion('I', hip , times, i); //腰

    smoothmotion('K', 0 , times, i);
    smoothmotion('L', -35 , times, i);
    smoothmotion('M', -50 , times, i);
    smoothmotion('N', -20 , times, i);
    smoothmotion('O', -15 , times, i); //右脚

    smoothmotion('Q', 5 , times, i);
    smoothmotion('R', 20 , times, i);
    smoothmotion('S', 40 , times, i);
    smoothmotion('T', 20 , times, i);
    smoothmotion('U', 0 , times, i); //左脚
    delay(frame);
  }
}





/************************stand on one leg************************/
void standonOneLegFirst(int frame) {//stand with left leg
  int times = 40;
  for (int i = 1; i <= times; i++) {
    smoothmotion('A', 0 , times, i); //首

    smoothmotion('B', 0 , times, i);
    smoothmotion('C', 0 , times, i);
    smoothmotion('D', 0 , times, i); //左腕

    smoothmotion('E', 0 , times, i);
    smoothmotion('F', 0 , times, i);
    smoothmotion('G', 0 , times, i); //右腕

    smoothmotion('H', 0 , times, i);
    smoothmotion('I', 0 , times, i); //腰

    smoothmotion('K', -10 , times, i);
    smoothmotion('L', 0 , times, i);
    smoothmotion('M', 0 , times, i);
    smoothmotion('N', 0 , times, i);
    smoothmotion('O', 10 , times, i); //右脚

    smoothmotion('Q', -10 , times, i);
    smoothmotion('R', 0 , times, i);
    smoothmotion('S', 0 , times, i);
    smoothmotion('T', 0 , times, i);
    smoothmotion('U', 10 , times, i); //左脚
    delay(frame);
  }
}

void standonOneLegSecond(int frame) {//stand with left leg
  int times = 50;
  for (int i = 1; i <= times; i++) {
    smoothmotion('A', 0 , times, i); //首

    smoothmotion('B', 0 , times, i);
    smoothmotion('C', 0 , times, i);
    smoothmotion('D', 0 , times, i); //左腕

    smoothmotion('E', 0 , times, i);
    smoothmotion('F', 0 , times, i);
    smoothmotion('G', 0 , times, i); //右腕

    smoothmotion('H', 0 , times, i);
    smoothmotion('I', -5 , times, i); //腰

    smoothmotion('K', 0 , times, i);
    smoothmotion('L', -30 , times, i);
    smoothmotion('M', -60 , times, i);
    smoothmotion('N', -30 , times, i);
    smoothmotion('O', 20 , times, i); //右脚

    smoothmotion('Q', 0 , times, i);
    smoothmotion('R', 0 , times, i);
    smoothmotion('S', 0 , times, i);
    smoothmotion('T', 0 , times, i);
    smoothmotion('U', 30 , times, i); //左脚
    delay(frame);
  }
}

void standonOneLegThird(int frame) {//stand with left leg
  int times = 50;
  for (int i = 1; i <= times; i++) {
    smoothmotion('A', 0 , times, i); //首

    smoothmotion('B', 0 , times, i);
    smoothmotion('C', 0 , times, i);
    smoothmotion('D', 0 , times, i); //左腕

    smoothmotion('E', 0 , times, i);
    smoothmotion('F', 0 , times, i);
    smoothmotion('G', 0 , times, i); //右腕

    smoothmotion('H', 0 , times, i);
    smoothmotion('I', -5 , times, i); //腰

    smoothmotion('K', -70 , times, i);
    smoothmotion('L', -30 , times, i);
    smoothmotion('M', -60 , times, i);
    smoothmotion('N', -30 , times, i);
    smoothmotion('O', 10 , times, i); //右脚

    smoothmotion('Q', 0 , times, i);
    smoothmotion('R', 0 , times, i);
    smoothmotion('S', 0 , times, i);
    smoothmotion('T', 0 , times, i);
    smoothmotion('U', 30 , times, i); //左脚
    delay(frame);
  }
}

void standonOneLegFourth(int frame) {//stand with left leg
  int times = 50;
  for (int i = 1; i <= times; i++) {
    smoothmotion('A', 0 , times, i); //首

    smoothmotion('B', 0 , times, i);
    smoothmotion('C', -80 , times, i);
    smoothmotion('D', 0 , times, i); //左腕

    smoothmotion('E', 0 , times, i);
    smoothmotion('F', 80 , times, i);
    smoothmotion('G', 0 , times, i); //右腕

    smoothmotion('H', 0 , times, i);
    smoothmotion('I', -5 , times, i); //腰

    smoothmotion('K', -70 , times, i);
    smoothmotion('L', 0 , times, i);
    smoothmotion('M', 0 , times, i);
    smoothmotion('N', 0 , times, i);
    smoothmotion('O', 0 , times, i); //右脚

    smoothmotion('Q', 0 , times, i);
    smoothmotion('R', 0 , times, i);
    smoothmotion('S', 0 , times, i);
    smoothmotion('T', 0 , times, i);
    smoothmotion('U', 30 , times, i); //左脚
    delay(frame);
  }
}



/******************************back******************************/

/******************************crab******************************/

/*****************************dogeza*****************************/
void seiza1() {
  for (int i = 0; i <= 10; i++) {
    setServo('A', stA); //首

    setServo('B', stB);
    setServo('C', stC);
    setServo('D', stD); //左腕

    setServo('E', stE);
    setServo('F', stF);
    setServo('G', stG); //右腕

    setServo('H', stH);
    setServo('I', stI); //腰

    setServo('K', stK);
    setServo('L', stL - i * 3); //-20
    setServo('M', stM + i * 7); //+40
    setServo('N', stN + i * 4); //+20
    setServo('O', stO);         //右足

    setServo('Q', stQ);
    setServo('R', stR + i * 3); //+20
    setServo('S', stS - i * 7); //-40
    setServo('T', stT - i * 4); //-20
    setServo('U', stU);         //左足

    delay(40);
  }
}

/*****sit*****/

void sitdown1() {
  for (int i = 0; i <= 8; i++) {
    setServo('A', stA); //首

    setServo('B', stB);
    setServo('C', stC);
    setServo('D', stD); //左腕

    setServo('E', stE);
    setServo('F', stF);
    setServo('G', stG); //右腕

    setServo('H', stH);
    setServo('I', stI - i * 4.5); //腰 -50

    setServo('K', stK);
    setServo('L', stL + i * 2); //+20
    setServo('M', stM);
    setServo('N', stN);
    setServo('O', stO); //右足

    setServo('Q', stQ);
    setServo('R', stR - i * 2); //-20
    setServo('S', stS);
    setServo('T', stT);
    setServo('U', stU); //左足

    delay(50);
  }
}

void sitdown2() {
  for (int i = 0; i <= 16; i++) {
    setServo('A', stA); //首

    setServo('B', stB);
    setServo('C', stC);
    setServo('D', stD); //左腕

    setServo('E', stE);
    setServo('F', stF);
    setServo('G', stG); //右腕

    setServo('H', stH);
    setServo('I', stI - 36 - i * 2.25); //腰 -50

    setServo('K', stK);
    setServo('L', stL + 16 + i * 0.5); //+20
    setServo('M', stM + i);
    setServo('N', stN - i * 1.5);
    setServo('O', stO); //右足

    setServo('Q', stQ);
    setServo('R', stR - 16 - i * 0.5); //-20
    setServo('S', stS - i);
    setServo('T', stT + i * 1.5);
    setServo('U', stU); //左足

    delay(50);
  }
}

void situp1() {
  for (int i = 0; i <= 8; i++) {
    setServo('A', stA); //首

    setServo('B', stB);
    setServo('C', stC);
    setServo('D', stD); //左腕

    setServo('E', stE);
    setServo('F', stF);
    setServo('G', stG); //右腕

    setServo('H', stH);
    setServo('I', stI - 72); //腰 -50

    setServo('K', stK);
    setServo('L', stL + 24 - i * 6); //+20
    setServo('M', stM + 16 - i);
    setServo('N', stN - 24);
    setServo('O', stO); //右足

    setServo('Q', stQ);
    setServo('R', stR - 24 + i * 6); //-20
    setServo('S', stS - 16 + i);
    setServo('T', stT + 24);
    setServo('U', stU); //左足

    delay(60);
  }
}

void situp2() {
  for (int i = 0; i <= 16; i++) {
    setServo('A', stA); //首

    setServo('B', stB);
    setServo('C', stC);
    setServo('D', stD); //左腕

    setServo('E', stE);
    setServo('F', stF);
    setServo('G', stG); //右腕

    setServo('H', stH);
    setServo('I', stI - 72 + i * 4.5); //腰 -50

    setServo('K', stK);
    setServo('L', stL - 24 + i * 1.5); //+20
    setServo('M', stM + 8 - i * 0.5);
    setServo('N', stN - 24 + i * 1.5);
    setServo('O', stO); //右足

    setServo('Q', stQ);
    setServo('R', stR + 24 - i * 1.5); //-20
    setServo('S', stS - 8 + i * 0.5);
    setServo('T', stT + 24 - i * 1.5);
    setServo('U', stU); //左足

    delay(50);
  }
}
