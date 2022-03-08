
//19/05/2021
#define CUSTOM_SETTINGS 0
#define INCLUDE_GAMEPAD_MODULE 1 

#include <Dabble.h>
//#include <SoftwareSerial.h>
//SoftwareSerial bluetooth(0, 1); // TX, RX
#include "pitches.h"

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int noteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4};

int MA1 = 4;     // Motor A1
int MA2 = 5;     // Motor A
int PWM_A =  9;   // Speed Motor A

int MB1 =  6;     // Motor B1
int MB2 =  7;     // Motor B2
int PWM_B =  10;  // Speed Motor B

int SPEED1_FOWARD = 115; //ขวา     // Speed PWM สามารถปรับความเร็วได้ถึง 0 - 255
int SPEED2_FOWARD = 120;  //ซ้าย

int SPEED1_BACKWARD = 115;     
int SPEED2_BACKWARD = 120; 

int SPEED1_TURNRIGHT = 120;     

int SPEED1_TURNLEFT = 120;     



void setup() {
  Serial.begin(250000);      
  Dabble.begin(9600);

  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
   }
  delay(200);      
}
void Backward(int time)
{
  digitalWrite(MA1, HIGH);
  digitalWrite(MA2, LOW);
  analogWrite(PWM_A, SPEED1_BACKWARD);

  digitalWrite(MB1, HIGH);
  digitalWrite(MB2, LOW);
  analogWrite(PWM_B, SPEED2_BACKWARD);

  delay(time);
}

void Forward (int time)
{
  digitalWrite(MA1, LOW);
  digitalWrite(MA2, HIGH);
  analogWrite(PWM_A, SPEED1_FOWARD);

  digitalWrite(MB1, LOW);
  digitalWrite(MB2, HIGH);
  analogWrite(PWM_B, SPEED2_FOWARD);

  delay(time);
}

void turnLeft(int time)
{
  digitalWrite(MA1, LOW);
  digitalWrite(MA2, HIGH);
  analogWrite(PWM_A, SPEED1_TURNLEFT);

  digitalWrite(MB1, LOW);
  digitalWrite(MB2, LOW);
  analogWrite(PWM_B, 0);

  delay(time);
}

void turnRight(int time)
{
  digitalWrite(MA1, LOW);
  digitalWrite(MA2, LOW);
  analogWrite(PWM_A, 0);

  digitalWrite(MB1, LOW);
  digitalWrite(MB2, HIGH);
  analogWrite(PWM_B, SPEED1_TURNRIGHT);

  delay(time);
}

void Stop(int time)
{
  digitalWrite(MA1, LOW);
  digitalWrite(MA2, LOW);
  analogWrite(PWM_A, 0);

  digitalWrite(MB1, LOW);
  digitalWrite(MB2, LOW);
  analogWrite(PWM_B, 0);

  delay(time);

}

int count = 0;
void loop() {
  Dabble.processInput();
  if (GamePad.isUpPressed())
  {
    Forward(100);
  }else if (!(GamePad.isUpPressed())&& !(GamePad.isDownPressed()) &&!(GamePad.isLeftPressed())&& !(GamePad.isRightPressed())){
    Stop(200);
  }

  if (GamePad.isDownPressed())
  {
    Backward(100);
    Serial.println("DOWN");
  }else if (!(GamePad.isUpPressed())&& !(GamePad.isDownPressed()) &&!(GamePad.isLeftPressed())&& !(GamePad.isRightPressed())){
    Stop(200);
  }

  if (GamePad.isLeftPressed())
  {
    turnLeft(450);
    Stop(200);
    Serial.println("Left");
  }else if(!(GamePad.isUpPressed())&& !(GamePad.isDownPressed()) &&!(GamePad.isLeftPressed())&& !(GamePad.isRightPressed())){
    Stop(200);
  }

  if (GamePad.isRightPressed())
  {
    turnRight(460);
    Stop(200);
    Serial.print("Right");
  }else if(!(GamePad.isUpPressed())&& !(GamePad.isDownPressed()) &&!(GamePad.isLeftPressed())&& !(GamePad.isRightPressed())){
    Stop(200);
  }

  if (GamePad.isSquarePressed())
  {
    Serial.print("Square");
  }

  if (GamePad.isCirclePressed())
  {
    Serial.print("Circle");
  }

  if (GamePad.isCrossPressed())
  {
    Serial.print("Cross");
  }

  if (GamePad.isTrianglePressed())
  {
    Serial.print("Triangle");
  }

  if (GamePad.isStartPressed())
  {
    Serial.print("Start");
  }

  if (GamePad.isSelectPressed())
  {
    Stop(200);
    Serial.print("Select");
  }
  else if(GamePad.isUpPressed()){
      Serial.print("0");
    }
}
