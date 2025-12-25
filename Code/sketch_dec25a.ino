#include <Arduino.h>
#include <xmotionV3.h> 

int RightSensor = A3;
int FrontRightSensor = A5;
int FrontLeftSensor = A4;
int LeftSensor = A1;


int LeftLine = 1; 
int RightLine = 0;
int Start = A0;   

int motionDelay = 10;

int Led1 = 8;

int Dip1 = 5;
int Dip2 = 6;
int Dip3 = 7;


int Strategy = 0;

int LastValue = 0;

void setup() {
  xmotion.StopMotors(100); 
  xmotion.ToggleLeds(100);  
  pinMode(Led1, OUTPUT);
  pinMode(RightSensor, INPUT);
  pinMode(FrontRightSensor, INPUT);
  pinMode(FrontLeftSensor, INPUT);
  pinMode(LeftSensor, INPUT);
  pinMode(Start, INPUT);
  Serial.begin(9600);
}


void loop() {

  xmotion.StopMotors(1);
  

  while (digitalRead(Start) == 0) { 

    if (digitalRead(LeftSensor) == 1 || digitalRead(FrontLeftSensor) == 1 || 
        digitalRead(FrontRightSensor) == 1 || digitalRead(RightSensor) == 1) {
      digitalWrite(Led1, HIGH);
    } else {
      digitalWrite(Led1, LOW);
    }
    xmotion.UserLed2(100);
  }
  
 
  xmotion.CounterLeds(1000, 0);
  

  while (digitalRead(Start) == 1) { 
  
    if (digitalRead(LeftLine) == 0 && digitalRead(RightLine) == 1) {
    
      xmotion.Backward(50, 200);  
      xmotion.Right0(25, 400);     
    } 
    else if (digitalRead(LeftLine) == 1 && digitalRead(RightLine) == 0) {
     
      xmotion.Backward(50, 200);   
      xmotion.Left0(50, 400);     
    } 
    else if (digitalRead(LeftLine) == 0 && digitalRead(RightLine) == 0) {

      xmotion.Backward(50, 400);   
      xmotion.Right0(50, 400);     
    }
    
    
    else if (digitalRead(FrontLeftSensor) == 1 && digitalRead(FrontRightSensor) == 1) {
      xmotion.Forward(100, motionDelay); 
      LastValue = 0;
    }
    else if (digitalRead(FrontLeftSensor) == 1) {
      if(digitalRead(Dip1) == 1 && digitalRead(Dip2) == 0 && digitalRead(Dip3) == 0){
         xmotion.ArcTurn(50, 100, motionDelay);
         Strategy = 1;
      }
      else{
         xmotion.ArcTurn(10, 100, motionDelay);
         Strategy = 0;
      }
      LastValue = 3;
    }
    else if (digitalRead(FrontRightSensor) == 1) {
      if(digitalRead(Dip1) == 1 && digitalRead(Dip2) == 0 && digitalRead(Dip3) == 0){
         xmotion.ArcTurn(100, 50, motionDelay); 
         Strategy = 1;
      }
      else{
         xmotion.ArcTurn(100, 10, motionDelay);
         Strategy = 0;
      }
      LastValue = 4;
    } 
    else if (digitalRead(RightSensor) == 1) {
      xmotion.Right0(100, motionDelay); 
      LastValue = 1;
    }
    else if (digitalRead(LeftSensor) == 1) {
   
      xmotion.Left0(100,  motionDelay); 
      LastValue = 2;
    }
 
    else if (LastValue == 0) {
      xmotion.Forward(70, motionDelay);
    } 
    else if (LastValue == 1) {
      xmotion.Right0(100, motionDelay);
    } 
    else if (LastValue == 2) {
      xmotion.Left0(100, motionDelay); 
    } 
    else if (LastValue == 3) {
      if(Strategy == 1){
        xmotion.ArcTurn(50, 100, motionDelay);
      }
      else{
        xmotion.ArcTurn(10, 100, motionDelay);
      }
      
    } 
    else if (LastValue == 4) {
            if(Strategy == 1){
        xmotion.ArcTurn(100, 50, motionDelay);
      }
      else{
        xmotion.ArcTurn(100, 10, motionDelay);
      }
    }
    

  }
  
  xmotion.StopMotors(100);
}