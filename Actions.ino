/*************************************
  Debug - YamaX Arduino Core v3.0
  Actions block
  made by coord.e, Y-modify
  Copyright © 2017 Y-modify All Rights Reserved.
*************************************/

void walk(int times, int delaytime)
{
  /*  if (delaytime < 20)
      delaytime = 20;  //20未満は危険*/

  print_c("Walking %d steps with %dms\n", times, delaytime);

  if (times <= 2)
    times = times;
  else
    times = times - 2;

  crouch();
  delay(500);
  for (int i = 0; i < times; i += 2)
  {
    walkLUp(delaytime, -2);
    walkLFoward(delaytime, -2);
    walkLDown(delaytime, -2);
    walkRUp(delaytime, -2);
    walkRFoward(delaytime, -2);
    walkRDown(delaytime, -2);
  }
  crouch();
  delay(500);
  reset(20, 20);
}




void turnright(int times, int delaytime)//左足の歩幅小さくする
{
  print_c("Turning right %d times with %dms\n", times, delaytime);
  /*  if (delaytime < 20)
      delaytime = 20;  //20未満は危険*/

  if (times <= 2)
    times = times;
  else
    times = times - 2;

  crouch();
  delay(500);
  for (int i = 0; i < times; i += 2)
  {
    walkLUp(delaytime + 10, -5);
    walkLFoward(delaytime, -5);
    turnLDown(delaytime, -5);
    turnRUp(delaytime + 10, -5);
    turnRDown(delaytime, -5);
  }
  delay(500);
  reset(20, 20);
}






void turnleft(int times, int delaytime)//右足の歩幅小さくする
{
  print_c("Turning left %d times with %dms\n", times, delaytime);
  /*if (delaytime < 20)
    delaytime = 20;  //20未満は危険*/

  if (times <= 2)
    times = times;
  else
    times = times - 2;

  crouch();
  delay(500);
  for (int i = 0; i < times; i += 2)
  {
    walkRUp(delaytime + 10, -5);
    walkRFoward(delaytime, -5);
    turnRDown(delaytime, -5);
    turnLUp(delaytime + 10, -5);
    turnLDown(delaytime, -5);
  }
  delay(500);
  reset(20, 20);
}




void back(int times, int delaytime)
{
  if (delaytime < 20)
    delaytime = 20;  //20未満は危険

  print_c("Walking %d steps with %dms\n", times, delaytime);

  if (times <= 2)
    times = times;
  else
    times = times - 2;

  crouch();
  delay(500);
  /*  LEFTwalkBeginUp(delaytime);//最初に左足上げる
    LEFTbackBeginFoward(delaytime);
    LEFTbackBeginDown(delaytime);

    for (int i = 0; i < times; i += 2)
    {
      if (i != 0)
      {
        backLEFTUp(delaytime);
        backLEFTFoward(delaytime);
        backLEFTDown(delaytime);
      }
      backRIGHTUp(delaytime);
      backRIGHTFoward(delaytime);
      backRIGHTDown(delaytime);
    }
    backLEFTUp(delaytime);
    backLEFTEndFoward(delaytime);
    backLEFTEnd(delaytime);*/
  //delay(500);
  //backRIGHTToCrouch(40);
  delay(500);
  reset(20, 10);
}



void oneleg(int delaytime)
{
  print_c("Standing on one leg %dms \n", delaytime);

  standonOneLegFirst(20);
  delay(1000);
  standonOneLegSecond(20);
  delay(1000);
  standonOneLegThird(20);
  delay(1000);
  standonOneLegFourth(20);
  delay(delaytime);
  
  standonOneLegThird(20);
  delay(1000);
  standonOneLegSecond(20);
  delay(1000);
  standonOneLegFirst(20);
  delay(1000);
  reset(20, 20);
}



void crabWalkingRight(int times, int delaytime)
{
  if (delaytime < 20)
    delaytime = 20;  //20未満は危険

  print_c("CrabWalkingRight %d steps with %dms\n", times, delaytime);

  crouch();
  delay(500);
  /*  for (int i = 0; i < times; i ++)
    {
      RIGHTwalkBeginUp(delaytime);
      RIGHTrightCrabFoward(delaytime);
      RIGHTrightCrabDown(delaytime);

      RIGHTleftCrabUp(delaytime);
      RIGHTleftCrabFoward(delaytime);
      RIGHTleftCrabDown(delaytime);
    }
    delay(500);*/
  reset(20, 10);
  delay(2000);
}






void crabWalkingLeft(int times, int delaytime)
{
  if (delaytime < 20)
    delaytime = 20;  //20未満は危険

  print_c("CrabWalkingRight %d steps with %dms\n", times, delaytime);

  crouch();
  delay(500);
  /*  for (int i = 0; i < times; i ++)
    {
      LEFTwalkBeginUp(delaytime);
      LEFTleftCrabFoward(delaytime);
      LEFTleftCrabDown(delaytime);

      LEFTrightCrabUp(delaytime);
      LEFTrightCrabFoward(delaytime);
      LEFTrightCrabDown(delaytime);
    }*/
  delay(500);
  reset(20, 10);
  delay(2000);
}




void automaDogeza(int delaytime)
{
  seiza1();
  delay(delaytime);
}





void no(int times)
{
  print_c("Denying %d times\n", times);
  for (int i = 0; i <= times; i++) {
    for (int k = 1; k <= 20; k++) {
      smoothmotion(servoA, -70 , 20, k); //首
      delay(10);
    }
    for (int k = 1; k <= 20; k++) {
      smoothmotion(servoA, 70 , 20, k); //首
      delay(10);
    }
  }
  for (int k = 1; k <= 10; k++) {
    smoothmotion(servoA, 0 , 10, k); //首
    delay(10);
  }
}





void bow(int delaytime)
{
  print_c("Bowing %dms\n", delaytime);
  bowing();
  delay(delaytime);
  reset(20, 20);
}






void bye(int times, int dir)//0:right, 1:left 2:both
{
  print_c("Bye %d times ", times);

  stand();

  if (dir == 0)
  {
    print_c("with right hand\n", times);
    setServoPulse(servoE, stE + 80);
    setServoPulse(servoF, stF - 70);
    for (int i = 0; i < times; i ++)
    {
      int tim = 20;
      for (int j = 0; j < 8; j++)
      {
        setServoPulse(servoG, stG + 80 - j * 10); //右腕
        delay(tim);
      }
      for (int j = 0; j < 8; j++)
      {
        setServoPulse(servoG, stG + j * 10); //右腕
        delay(tim);
      }
    }
  }

  if (dir == 1) {
    print_c("with left hand\n", times);
    setServoPulse(servoB, stB - 50);
    setServoPulse(servoC, stC + 80);
    for (int i = 0; i < times; i ++)
    {
      int tim = 20;
      for (int j = 0; j < 8; j++)
      {
        setServoPulse(servoD, stD - 80 + j * 10); //左腕
        delay(tim);
      }
      for (int j = 0; j < 8; j++)
      {
        setServoPulse(servoD, stD - j * 10); //左腕
        delay(tim);
      }
    }


  }

  if (dir == 2)
  {
    print_c("with both hand\n", times);

    setServoPulse(servoB, stB - 50);
    setServoPulse(servoC, stC + 80);
    setServoPulse(servoE, stE + 50);
    setServoPulse(servoF, stF - 60);
    for (int i = 0; i < times; i ++)
    {
      int tim = 20;
      for (int j = 0; j < 8; j++)
      {
        setServoPulse(servoG, stG + 80 - j * 10); //右腕
        setServoPulse(servoD, stD - 80 + j * 10); //左腕
        delay(tim);
      }
      for (int j = 0; j < 8; j++)
      {
        setServoPulse(servoG, stG + j * 10); //右腕
        setServoPulse(servoD, stD - j * 10); //左腕
        delay(tim);
      }
    }
  }
}







void nadenade(int times, bool dir) //0:right 1:left
{
  print_c("Nadenade %d times\n", times);

  stand();

  if (dir)
  {
    print_c("with left hand\n", times);
    setServoPulse(servoC, stC + 80);

    for (int i = 0; i < times; i ++)
    {
      int tim = 20;
      for (int j = 0; j < 8; j++)
      {
        setServoPulse(servoD, stD - 80 + j * 10); //左腕
        delay(tim);
      }
      for (int j = 0; j < 8; j++)
      {
        setServoPulse(servoD, stD - j * 10); //左腕
        delay(tim);
      }
    }
  }

  if (!dir)
  {
    print_c("with right hand\n", times);
    setServoPulse(servoF, stF - 60);
    for (int i = 0; i < times; i ++)
    {
      int tim = 20;
      for (int j = 0; j < 8; j++)
      {
        setServoPulse(servoG, stG + 80 - j * 10); //右腕
        delay(tim);
      }
      for (int j = 0; j < 8; j++)
      {
        setServoPulse(servoG, stG + j * 10); //右腕
        delay(tim);
      }
    }
  }
}


void sitDown()
{
  sitdown1();
  sitdown2();
}

void sitUp()
{
  situp1();
  delay(1000);
  situp2();
}




void dance(int times)
{
  print_c("Dancing %d times\n", times);
  for (int i = 0; i < times; i ++)
  {
  }
}

