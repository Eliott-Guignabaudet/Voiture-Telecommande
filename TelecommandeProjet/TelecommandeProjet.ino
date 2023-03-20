#include <IRremote.hpp>
//#include "TinyIRSender.hpp"



#define X_JOYSTICK A1
#define Y_JOYSTICK A0

#define BUTTON_OPEN 2
#define BUTTON_CLOSE 3
#define BUTTON_UP 4
#define BUTTON_DOWN 5
#define BUTTON_RIGHT 6
#define BUTTON_LEFT 7

#define JOYSTICK_PIN 10
#define IR_SEND_PIN 11

int delayBetwennSend = 25;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(BUTTON_OPEN, INPUT_PULLUP);
  pinMode(BUTTON_CLOSE, INPUT_PULLUP);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);

  //pinMode(IR_SEND_PIN, OUTPUT);
  IrSender.begin(IR_SEND_PIN);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool openState = digitalRead(BUTTON_OPEN);
  bool closeState = digitalRead(BUTTON_CLOSE);
  bool upState = digitalRead(BUTTON_UP);
  bool downState = digitalRead(BUTTON_DOWN);
  bool rightState = digitalRead(BUTTON_RIGHT);
  bool leftState = digitalRead(BUTTON_LEFT);

  //Serial.println(leftState);
  int xAxis = analogRead(X_JOYSTICK);
  int yAxis = analogRead(Y_JOYSTICK);


  SendIrJoystick(xAxis, yAxis);
  SendIrButtonsOpenState(openState, closeState);
  SendIrButtonRightState(rightState, leftState);
  SendIrButtonUpState(upState, downState);
  //sendFAST(IR_SEND_PIN, xAxis);
}


void SendIrJoystick(int x, int y) {
  int transformedXAxis = map(x, 0, 1023, 0, 255);
  int transformedYAxis = map(y, 0, 1023, 0, 255);
  // if (transformedXAxis <= 120 || transformedXAxis >= 135){
  //   IrSender.sendNEC(0x0102, transformedXAxis, 0 );
  //   delay(delayBetwennSend);
  // }
  // if (transformedYAxis <= 120 || transformedYAxis >= 135){
  //   IrSender.sendNEC(0x0100, transformedYAxis, 0 );
  //   delay(delayBetwennSend);
  // }
  // Serial.print("x = ");
  // Serial.print(transformedXAxis);
  // Serial.print(", y = ");
  // Serial.println(transformedYAxis);
  IrSender.sendNEC(0x0102, transformedXAxis, 2);
  delay(delayBetwennSend);
  IrSender.sendNEC(0x0100, transformedYAxis, 2);
  delay(delayBetwennSend);
}


void SendIrButtonsOpenState(bool open, bool close) {
  if (!open) {
    IrSender.sendNEC(0x0103, 1, 0);
    delay(delayBetwennSend);
  }
  if (!close) {
    IrSender.sendNEC(0x0103, 0, 0);
    delay(delayBetwennSend);
  }
}

void SendIrButtonRightState(bool right, bool left) {
  if (!right) {
    IrSender.sendNEC(0x0104, 1, 0);
    delay(delayBetwennSend);
  }
  if (!left) {
    IrSender.sendNEC(0x0104, 0, 0);
    delay(delayBetwennSend);
  }
}

void SendIrButtonUpState(bool up, bool down) {
  if (!up) {
    IrSender.sendNEC(0x0105, 1, 0);
    delay(delayBetwennSend);
  }
  if (!down) {
    IrSender.sendNEC(0x0105, 0, 0);
    delay(delayBetwennSend);
  }
}