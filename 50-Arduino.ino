/*************************************
  YamaX Arduino Core v3.0
  To burn on AX-03 for YamaX 5.0
  made by Y-modify, Nyanyan & coord.e
  Copyright © 2017 Y-modify All Rights Reserved.
  QIO,80,160,4M(1M),Disabled,none,nodemcu,115200~
*************************************/

/*****Version Definition*****/
#define YAMAX_VER "5.0"
#define FIRMWARE_VER "5.0-uno"

#if defined(ARDUINO_AVR_UNO) || defined(ESP8266) // AX-01 or something nice
#define S_STABLE
#define BOARD_VER "01"
#else
#error This board is not supported! Please use ESP8266 or Arduino UNO.
#endif

/*****System Setup*****/
void setup() {
  Serial.begin(115200);
  delay(1000);

  //  print_c("HELLO YamaX %s\n", YAMAX_VER);
  // delay(500);
  verInfo(); // Print Version Information
  // delay(500);
  // print_c("test\n");
  print_c("Initializing...\n");
  // delay(100);
  ControlInit(); // Serial Command Control Initialize
  // delay(100);
  ServoInit(); // Servo Driver Setup
  // delay(100);
  //standdelay(50);
  stand();

  // Start

  print_c("Initialization Complete.\n");

  /*   for(int i = 0; i <5; i++)
     {
       stand();
       delay(5000);
      bow();
       delay(900);
       stand();
       delay(2000);
       walk(10,300);
       stand();
       delay(1000);
      bye(10);
       stand();
       delay(1000);
       no(5);
     }*/
  //  delay(4000);
  //  walk(10,300);
  //  stand();
  // kusoran();
  // bye(10,0);
  // bye(10,1);
  // bye(10,2);
  // nadenade(10,0);
  // nadenade(10,1);
  // walk(10,200);
}

/*****Waiting Loop*****/
void loop() {
  CommandCheck();

  delay(1);
}

/*****Print Version Information*****/
void verInfo() {
  print_c("\n*************************************\n");
  print_c("YamaX Arduino Core (MCore) v%s\n", FIRMWARE_VER);
  print_c("To burn on AX-%s for YamaX %s\n", BOARD_VER, YAMAX_VER);
  print_c("Made by Y-modify, Nyanyan & coord.e\n");
  print_c("Copyright (c) 2016 Y-modify All Rights Reserved.\n");
  print_c("*************************************\n\n");
}

/*****That's all. Enjoy!*****/
