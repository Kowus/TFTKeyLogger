/*
   TFT LCD Keypad sketch by Barnabas Nomo

    Materials
      Arduino Uno
      TFT LCD Screen (MCUFRIEND_kbv for this project)

    PseudoCode for MVP
      1. LCD Black background
      2. Print Numbers and controls on Screen in 12 grids.
        a. Numbers from 0 - 9, include space and return key


*/



#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>


#include "colors.h"

MCUFRIEND_kbv tft;


#include <TouchScreen.h>

#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

uint8_t YP = A1;  // must be an analog pin, use "An" notation!
uint8_t XM = A2;  // must be an analog pin, use "An" notation!
uint8_t YM = 7;   // can be a digital pin
uint8_t XP = 6;   // can be a digital pin
uint8_t SwapXY = 0;

uint16_t TS_LEFT = 920;
uint16_t TS_RT  = 150;
uint16_t TS_TOP = 940;
uint16_t TS_BOT = 120;
char *name = "Unknown controller";


TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;


#define MINPRESSURE 20
#define MAXPRESSURE 1000

#define SWAP(a, b) {uint16_t tmp = a; a = b; b = tmp;}
///*
int16_t BOXSIZE ;

//*/





uint16_t rectHeight = 64;
uint16_t endRect = 320 - rectHeight;

uint16_t textBoxStart = 16;
uint16_t endTextBox = 40;

String pass = "";
int mode = 1000;
String alert = "";
void setup() {
  initlz();

  formal();

}

void loop() {
  // put your main code here, to run repeatedly:
  firstScreenInput();

}





/*
   Functions
*/

void initlz() {
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.setRotation(0);
  tft.begin(identifier);
}

void formal() {
  Serial.begin(9600);

  instructions();
  textBox();
  keyPad();



}
void instructions() {
  tft.fillScreen(BLACK);
  tft.setTextSize(0);
  tft.setCursor(10, 0);
  tft.print("TFT KeyLogger");
}
void keyPad() {
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.drawRect(0, rectHeight, tft.width(), endRect, YELLOW);
  tft.drawLine(80, rectHeight + 3, 80, 316, YELLOW);
  tft.drawLine(160, rectHeight + 3, 160, 316, YELLOW);
  tft.drawLine(3, 128,  316, 128, YELLOW);
  tft.drawLine(3, 192,  316, 192, YELLOW);
  tft.drawLine(3, 256,  316, 256, YELLOW);
  tft.setCursor(37, 90);
  tft.println("1");
  tft.setCursor(117, 90);
  tft.println("2");
  tft.setCursor(197, 90);
  tft.println("3");
  tft.setCursor(37, 154);
  tft.println("4");
  tft.setCursor(117, 154);
  tft.println("5");
  tft.setCursor(197, 154);
  tft.println("6");
  tft.setCursor(37, 218);
  tft.println("7");
  tft.setCursor(117, 218);
  tft.println("8");
  tft.setCursor(197, 218);
  tft.println("9");
  tft.setCursor(10, 282);
  tft.println("Clear");
  tft.setCursor(117, 282);
  tft.println("0");
  tft.setCursor(170, 282);
  tft.println("Enter");

}
void textBox() {
  tft.drawRect(0, textBoxStart, tft.width(), endTextBox, GREEN);
  tft.fillRect(3, textBoxStart + 3, tft.width() - 6, endTextBox - 6, WHITE);
}

void firstScreenInput() {
  tft.setTextColor(WHITE, BLACK);
  uint16_t xpos, ypos;
  tp = ts.getPoint();


  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  pinMode(XP, OUTPUT);
  pinMode(YM, OUTPUT);


  xpos = map(tp.x, TS_LEFT, TS_RT, 0, 240);
  ypos = map(tp.y, TS_TOP, TS_BOT, 0, 320);

  tft.setTextSize(0);
  tft.setCursor(120, 0);
  tft.print("tp.x=" + String(xpos) + " tp.y=" + String(ypos) + " tp.z=" + String(tp.z));

  // 1 Zone
  if (xpos > 180 && xpos < 205 && ypos > 136 && ypos <  180) {
    mode = 1;
  }

  // 2 Zone
  else if (xpos > 210 && xpos < 230 && ypos > 122 && ypos < 146) {
    mode = 2;
  }

  // 3 Zone
  else if (xpos > 230 && xpos < 263 && ypos > 110 && ypos < 133) {
    mode = 3;
  }

  // 4 Zone
  else if (xpos > 199 && xpos < 214 && ypos > 102 && ypos < 133) {
    mode = 4;
  }

  // 5 Zone
  else if (xpos > 216 && xpos < 235 && ypos > 92 && ypos < 120) {
    mode = 5;
  }

  // 6 Zone
  else if (xpos > 236 && xpos < 266 && ypos > 77 && ypos < 100) {
    mode = 6;
  }

  // 7 Zone
  else if (xpos > 207 && xpos < 220 && ypos > 64 && ypos < 100) {
    mode = 7;
  }

  //8 Zone
  else if (xpos > 223 && xpos < 235 && ypos > 53 && ypos < 88) {
    mode = 8;
  }

  // 9 Zone
  else if (xpos > 237 && xpos < 259 && ypos > 43 && ypos < 80) {
    mode = 9;
  }
  // 0 Zone
  else if (xpos > 227 && xpos < 248 && ypos > 13 && ypos < 58) {
    mode = 0;
  }

  // Clear Zone
  else if (xpos > 206 && xpos < 225 && ypos > 20 && ypos < 65) {
    mode = 11;
  }
  else if (/*enter zone*/) {
    mode = 12;
  }

  // Shouldn't exceed 17 characters
  if (pass.length() >= 17) {
    mode = 17;
  }



  switch (mode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      Serial.println(mode);
      pass += mode;
      mode = 10;
      break;

    case 11:
      pass = "";
      Serial.println("Cleared");
      textBox();
      keyPad();
      break;


    case 12:
      break;




    case 17:
      alert = "Max Char Reached";
      tft.setCursor(tft.width() / 2 - ((alert.length() / 2) * 6), textBoxStart + 28);
      tft.setTextSize(0);
      tft.setTextColor(RED, BLACK);
      tft.print(alert);
      if (xpos > 206 && xpos < 225 && ypos > 20 && ypos < 65) {
        pass = "";
        Serial.println("Cleared");
        textBox();
        keyPad();
        mode = 10;
      }

      break;

    default:
      break;
  }





  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.setCursor(20, textBoxStart + 12);
  tft.print(pass);


  tft.setTextColor(WHITE, BLACK);
  tft.setTextSize(0);
  tft.setCursor(90, 0);
  tft.print(pass.length());
  delay(200);
}

