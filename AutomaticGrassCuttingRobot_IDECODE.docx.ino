#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>
#define TRIG A0
#define ECHO A1
#define fl1 6
#define fl2 5
#define fr1 3
#define fr2 2
#define bl1 12
#define bl2 11
#define br1 9
#define br2 8
#define MAXDIST 200
#define MAXSPEED 100
Servo servo1;
NewPing pingobject(TRIG,ECHO,MAXDIST)
boolean move=false;
int distance=100;

void setup()
{
  pinMode(fl1, OUTPUT);
  pinMode(fl2, OUTPUT);
  pinMode(fr1, OUTPUT);
  pinMode(fr2, OUTPUT);
  pinMode(bl1, OUTPUT);
  pinMode(bl2, OUTPUT);
  pinMode(br1, OUTPUT);
  pinMode(br2, OUTPUT);

  servo1.attach(10);
  servo1.write(90);
  delay(1000);
  distance=dist();
  delay(100);
  distance=dist();
  delay(100);
}

void loop()
{
  int right=0;
  int left=0;
  if (distance<=20){
    Stop();
    delay(100);
    Back();
    delay(200);
    right=lookright();
    delay(200);
    left=lookleft();
    delay(200);
    if (right<left){
      turnleft();
      delay(100);
    }
    else{
      turnright();
      delay(100);
    }
  }
  else{
    movefront();
    delay(100);
  }
  distance=dist();
}

int lookright()
{
  servo1.write(50);
  delay(500);
  int D=dist();
  delay(100);
  servo1.write(90);
  return D;
}

int lookleft()
{
  servo1.write(140);
  delay(500);
  int D=dist();
  delay(100);
  servo1.write(90);
  return D;
}

int dist()
{
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Read echo
  long duration = pulseIn(ECHO, HIGH);

  // Convert to distance in cm
  int D = duration * 0.034 / 2;
  return D;
}

void Stop()
{
  digitalWrite(fl1,LOW);
  digitalWrite(fl2,LOW);
  digitalWrite(fr1,LOW);
  digitalWrite(fr2,LOW);
  digitalWrite(bl1,LOW);
  digitalWrite(bl2,LOW);
  digitalWrite(br1,LOW);
  digitalWrite(br2,LOW);
}

void Back()
{
  move=false;
  digitalWrite(fl1,LOW);
  digitalWrite(fl2,HIGH);
  digitalWrite(fr1,LOW);
  digitalWrite(fr2,HIGH);
  digitalWrite(bl1,LOW);
  digitalWrite(bl2,HIGH);
  digitalWrite(br1,LOW);
  digitalWrite(br2,HIGH);
}

void movefront()
{
  move=true;
  digitalWrite(fl1,HIGH);
  digitalWrite(fl2,LOW);
  digitalWrite(fr1,HIGH);
  digitalWrite(fr2,LOW);
  digitalWrite(bl1,HIGH);
  digitalWrite(bl2,LOW);
  digitalWrite(br1,HIGH);
  digitalWrite(br2,LOW);
}

void turnleft()
{
  analogWrite(fl1,0);
  analogWrite(fl2,MAXSPEED);
  analogWrite(fr1,MAXSPEED);
  analogWrite(fr2,0);
  analogWrite(bl1,0);
  analogWrite(bl2,MAXSPEED);
  analogWrite(br1,MAXSPEED);
  analogWrite(br2,0);
  delay(500);
  digitalWrite(fl1,HIGH);
  digitalWrite(fl2,LOW);
  digitalWrite(fr1,HIGH);
  digitalWrite(fr2,LOW);
  digitalWrite(bl1,HIGH);
  digitalWrite(bl2,LOW);
  digitalWrite(br1,HIGH);
  digitalWrite(br2,LOW);
}

void turnright()
{
  analogWrite(fl2,0);
  analogWrite(fl1,MAXSPEED);
  analogWrite(fr2,MAXSPEED);
  analogWrite(fr1,0);
  analogWrite(bl2,0);
  analogWrite(bl1,MAXSPEED);
  analogWrite(br2,MAXSPEED);
  analogWrite(br1,0);
  delay(500);
  digitalWrite(fl1,HIGH);
  digitalWrite(fl2,LOW);
  digitalWrite(fr1,HIGH);
  digitalWrite(fr2,LOW);
  digitalWrite(bl1,HIGH);
  digitalWrite(bl2,LOW);
  digitalWrite(br1,HIGH);
  digitalWrite(br2,LOW);
}

