/*************************************
  Controls - YamaX Arduino Core v3.0
  Command control block
  made by coord.e, Y-modify
  Copyright © 2017 Y-modify All Rights Reserved.
*************************************/

#include <SerialCommand.h>

SerialCommand SCmd;

void ControlInit() {
  SCmd.addCommand("walk", walkStep);
  SCmd.addCommand("back", backStep);
  SCmd.addCommand("crabright", crabRightStep);
  SCmd.addCommand("crableft", crabLeftStep);
  SCmd.addCommand("right", tRightStep);
  SCmd.addCommand("left", tLeftStep);
  SCmd.addCommand("bow", bowS);
  SCmd.addCommand("dogeza", dogezaS);
  SCmd.addCommand("crouch", crouch);
  SCmd.addCommand("sitdown", sitDown);
  SCmd.addCommand("situp", sitUp);
  SCmd.addCommand("reset", Reset);
  SCmd.addCommand("dance", danceS);
  SCmd.addCommand("stand", stand);
  SCmd.addCommand("bye", byeS);
  SCmd.addCommand("no", noS);
  SCmd.addCommand("oneleg", oneLeg);
  SCmd.addCommand("setred", ledRedAdj);
  SCmd.addCommand("setgreen", ledGreenAdj);
  SCmd.addCommand("setblue", ledBlueAdj);
  SCmd.addCommand("version", verInfo);
  SCmd.addCommand("setdeg", setDeg);
  SCmd.setDefaultHandler(what);
}

void CommandCheck() {
  SCmd.readSerial();
}

/*****Functions for Response*****/
void Reset() {
  char *arg;
  print_c("reset");
  arg = SCmd.next();
  if (arg != NULL) {
    int times = atoi(arg); // Converts a char string to an integer
    arg = SCmd.next();
    if (arg != NULL) {
      int delaytime = atol(arg);
      reset(times, delaytime);
    } else {
      reset(times, 20);
    }
  } else {
    reset(20, 20);
  }
  stand();
  clearBuf();
}


void walkStep() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL) {
    int steps = atoi(arg); // Converts a char string to an integer
    arg = SCmd.next();
    if (arg != NULL) {
      int del = atol(arg);
      walk(steps, del);
    } else {
      walk(steps, 15);
    }
  } else {
    walk(10, 15);
  }
  stand();
  clearBuf();
}

void backStep() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL) {
    int steps = atoi(arg); // Converts a char string to an integer
    arg = SCmd.next();
    if (arg != NULL) {
      int del = atol(arg);
      back(steps, del);
    } else {
      what();
    }
  } else {
    what();
  }
  stand();
  clearBuf();
}

void crabRightStep() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL) {
    int steps = atoi(arg); // Converts a char string to an integer
    arg = SCmd.next();
    if (arg != NULL) {
      int del = atol(arg);
      crabWalkingRight(steps, del);
    } else {
      what();
    }
  } else {
    what();
  }
  stand();
  clearBuf();
}

void crabLeftStep() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL) {
    int steps = atoi(arg); // Converts a char string to an integer
    arg = SCmd.next();
    if (arg != NULL) {
      int del = atol(arg);
      crabWalkingLeft(steps, del);
    } else {
      what();
    }
  } else {
    what();
  }
  stand();
  clearBuf();
}

void bowS() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL) {
    int val = atoi(arg);
    bow(val);
  } else {
    bow(900);
  }
  stand();
  clearBuf();
}

void oneLeg() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL) {
    int delaytime = atoi(arg); // Converts a char string to an integer
    arg = SCmd.next();
    oneleg(delaytime);
  } else {
    oneleg(1000);
  }
  //  stand();
  clearBuf();
}

void dogezaS() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL) {
    int val = atoi(arg);
    automaDogeza(val);
  } else {
    what();
  }
  stand();
  clearBuf();
}

void noS() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL) {
    int val = atoi(arg);
    no(val);
  } else {
    no(4);
  }
  //stand();
  clearBuf();
}

void danceS() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL) {
    int val = atoi(arg);
    //dance(val);
  } else {
    what();
  }
  //stand();
  clearBuf();
}

void byeS() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL) {
    int steps = atoi(arg); // Converts a char string to an integer
    arg = SCmd.next();
    if (arg != NULL) {
      int val = atoi(arg);
      bye(steps, val == 0 ? true : false);
    } else {
      what();
    }
  } else {
    what();
  }
  stand();
  clearBuf();
}

void tRightStep() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL) {
    int steps = atoi(arg); // Converts a char string to an integer
    arg = SCmd.next();
    if (arg != NULL) {
      int del = atol(arg);
      turnright(steps, del);
    } else {
      turnright(steps, 15);
    }
  } else {
    turnright(10, 15);
  }
  stand();
  clearBuf();
}

void tLeftStep() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL) {
    int steps = atoi(arg); // Converts a char string to an integer
    arg = SCmd.next();
    if (arg != NULL) {
      int del = atol(arg);
      turnleft(steps, del);
    } else {
      turnleft(steps, 15);
    }
  } else {
    turnleft(10, 15);
  }
  stand();
  clearBuf();
}

void ledRedAdj() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL) {
    int val = atoi(arg); // Converts a char string to an integer
    print_c("Set red LED to %d\n", val);
    setLEDr(map(val, 0, 100, 0, LEDREDMAX));
  } else {
    what();
  }
  clearBuf();
}

void ledGreenAdj() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL) {
    int val = atoi(arg); // Converts a char string to an integer
    print_c("Set green LED to %d\n", val);
    setLEDg(map(val, 0, 100, 0, LEDGREENMAX));
  } else {
    what();
  }
  clearBuf();
}

void ledBlueAdj() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL) {
    int val = atoi(arg); // Converts a char string to an integer
    print_c("Set blue LED to %d\n", val);
    setLEDb(map(val, 0, 100, 0, LEDBLUEMAX));
  } else {
    what();
  }
  clearBuf();
}

void setDeg() {
  char *arg;

  arg = SCmd.next();
  if (arg != NULL) {
    int n = atoi(arg); // Converts a char string to an integer
    arg = SCmd.next();
    if (arg != NULL) {
      int degress = atol(arg);
      setdeg(n, degress);
    } else {
      what();
    }
  } else {
    what();
  }
  clearBuf();
}

void what() {
  print_c("I can't understand.\n");
  no(2);
}

void what(const char *command) {
  Serial.print("Commamnd ");
  Serial.print(command);
  Serial.print("is not defined\n");
  no(2);
}

void clearBuf() {
  while (Serial.available())
    Serial.read();
}
