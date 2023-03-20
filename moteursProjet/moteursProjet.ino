#include <IRremote.hpp>

#define IR_receiver 3

#define Left_Motor_1 13
#define Left_Motor_2 12
#define Left_PWM 5

#define Right_Motor_1 8
#define Right_Motor_2 7
#define Right_PWM 10

#define Servo_1 9
#define Servo_2 6
#define Servo_3 11

int valPot = 0;
bool tourneX = false;
bool tourneY = false;


int servo1State = 0;
int servo2State = 0;
int servo3State = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Left_Motor_1, OUTPUT);
  pinMode(Left_Motor_2, OUTPUT);
  pinMode(Left_PWM, OUTPUT);

  pinMode(Right_Motor_1, OUTPUT);
  pinMode(Right_Motor_2, OUTPUT);
  pinMode(Right_PWM, OUTPUT);

  pinMode(Servo_1, OUTPUT);
  pinMode(Servo_2, OUTPUT);
  pinMode(Servo_3, OUTPUT);
  analogWrite(Servo_1, servo1State);
  analogWrite(Servo_2, servo2State);
  analogWrite(Servo_3, servo2State);


  IrReceiver.begin(IR_receiver);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(IrReceiver.decode()){
    boolean tourne = false;
    
    valPot = IrReceiver.decodedIRData.command;
    int valTrans = 0;
    if(IrReceiver.decodedIRData.address == 258 || IrReceiver.decodedIRData.address == 256){
      valTrans = map(valPot, 0, 255, -255, 255);
      if(valTrans > 20 || valTrans < -20){
        tourne = true;
      }

    }
    if(IrReceiver.decodedIRData.address == 258 ){

      

      if (valTrans > 60){
        tourneY = true;
        digitalWrite(Right_Motor_1, HIGH);
        digitalWrite(Right_Motor_2, LOW);
        analogWrite(Right_PWM, valTrans);
        // analogWrite(Right_PWM, valTrans);

        digitalWrite(Left_Motor_1, HIGH);
        digitalWrite(Left_Motor_2, LOW);
        analogWrite(Left_PWM, valTrans);
        
      }
      else if (valTrans < -60){
        tourneY = true;
        digitalWrite(Right_Motor_1, LOW);
        digitalWrite(Right_Motor_2, HIGH);
        analogWrite(Right_PWM, -valTrans);

        digitalWrite(Left_Motor_1, LOW);
        digitalWrite(Left_Motor_2, HIGH);
        analogWrite(Left_PWM, -valTrans);
      }
      else if(tourneX == false) {
        tourneY = false;
        digitalWrite(Right_Motor_1, HIGH);
        digitalWrite(Right_Motor_2, HIGH);
        analogWrite(Right_PWM, 0);

        digitalWrite(Left_Motor_1, HIGH);
        digitalWrite(Left_Motor_2, HIGH);
        analogWrite(Left_PWM, 0);
      }else{
        tourneY = false;
      }


    

    }
    
    if(IrReceiver.decodedIRData.address == 256){

      if (valTrans > 60){
        tourneX = true;
        digitalWrite(Right_Motor_1, HIGH);
        digitalWrite(Right_Motor_2, LOW);
        analogWrite(Right_PWM, valTrans);
        // analogWrite(Right_PWM, valTrans);

        digitalWrite(Left_Motor_1, LOW);
        digitalWrite(Left_Motor_2, HIGH);
        analogWrite(Left_PWM, valTrans);
        
      }
      else if (valTrans < -60){
        tourneX = true;
        digitalWrite(Right_Motor_1, LOW);
        digitalWrite(Right_Motor_2, HIGH);
        analogWrite(Right_PWM, -valTrans);

        digitalWrite(Left_Motor_1, HIGH);
        digitalWrite(Left_Motor_2, LOW);
        analogWrite(Left_PWM, -valTrans);
      }
      else if(!tourneY){
        tourneX = false;
        digitalWrite(Right_Motor_1, HIGH);
        digitalWrite(Right_Motor_2, HIGH);
        analogWrite(Right_PWM, 0);

        digitalWrite(Left_Motor_1, HIGH);
        digitalWrite(Left_Motor_2, HIGH);
        analogWrite(Left_PWM, 0);
      }
      else{
        tourneX = false;
      }
    }
    if(IrReceiver.decodedIRData.address == 0x0103){
      Serial.print("Servo1 : ");
      Serial.println(servo1State);      
      if(IrReceiver.decodedIRData.command == 1 && servo1State < 179){
        servo1State += 45;
        if(servo1State>179){
          servo1State = 179;
        }
        analogWrite(Servo_1, servo1State);
      }else if (IrReceiver.decodedIRData.command == 0 && servo1State > 0){
        servo1State -= 45;
        if(servo1State<0){
          servo1State = 0;
        }
        analogWrite(Servo_1, servo1State);
      }
    }
    if(IrReceiver.decodedIRData.address == 0x0104){
      Serial.print("Servo2 : "); 
      Serial.println(servo2State);  
      if(IrReceiver.decodedIRData.command == 1 && servo2State < 179){
        servo2State += 20;
        if(servo2State>179){
          servo2State = 179;
        }
        analogWrite(Servo_2, servo2State);
      }else if (IrReceiver.decodedIRData.command == 0 && servo2State > 0){
        servo2State -= 20;
        if(servo2State<0){
          servo2State = 0;
        }
        analogWrite(Servo_2, servo2State);
      }
    }
    if(IrReceiver.decodedIRData.address == 0x0105){
      Serial.print("Servo3 : ");

      Serial.println(servo3State);
      if(IrReceiver.decodedIRData.command == 1 && servo3State < 179){
        servo3State += 20;
        if(servo3State>179){
          servo3State = 179;
        }
        analogWrite(Servo_3, servo3State);
      }else if (IrReceiver.decodedIRData.command == 0 && servo3State > 0){
        servo3State -= 20;
        if(servo3State<0){
          servo3State = 0;
        }
        analogWrite(Servo_3, servo3State);
      }
    }
    IrReceiver.resume();
  }
  // else{
  //   analogWrite(Left_PWM, 0);
  //   analogWrite(Right_PWM, 0);
  // }
}
