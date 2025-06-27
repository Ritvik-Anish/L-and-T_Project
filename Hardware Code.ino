#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>
#define TRIG A0
#define ECHO A1
AF_DCMotor motor3(3, MOTOR12_1KHZ);
AF_DCMotor motor4(4, MOTOR12_1KHZ);
#define MAXDIST 200
#define MAXSPEED 200
Servo servo1;
NewPing pingobject(TRIG,ECHO,MAXDIST);
boolean move=false;
int distance=100;

void setup()
{
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  motor3.setSpeed(MAXSPEED);
  motor4.setSpeed(MAXSPEED);
  servo1.attach(10);
  servo1.write(90);
  delay(100);
  distance=dist();
  delay(100);
  distance=dist();
  delay(100);
}

void loop()
{
  int right=0;
  int left=0;
  if (distance<=40){
    Stop();
    delay(100);
    Back();
    delay(100);
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
  int d = pingobject.ping_cm();
  if (d == 0) d = 190; // If no ping detected, assume very far (optional safety)
  return d;
}

void Stop()
{
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void Back()
{
  move=false;
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void movefront()
{
  move=true;
  motor3.run(FORWARD); 
  motor4.run(FORWARD);
}

void turnleft()
{
  motor4.run(FORWARD);
  motor3.run(BACKWARD);
  delay(500);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void turnright()
{
  motor4.run(BACKWARD);
  motor3.run(FORWARD);
  delay(500);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

