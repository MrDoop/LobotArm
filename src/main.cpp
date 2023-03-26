#include <Arduino.h>
#include <Servo.h>

#include "robot_arm.hpp"

char buffer[20];
RobotArm ra;

Servo base;
Servo joint1;
Servo joint2;
Servo hand;
Servo gripper;

void startUpSequence();
void readSerial();
void writePosition();
void setState();

float x = 0, y = 100, z = 0, w = 0, h = 0;
double currentJoint1Pos = -90;


void setup()
{
  Serial.begin(115200);

  while (!Serial.available())
    ;


  delay(100);
  while (Serial.available()) Serial.read();
  delay(100);

  base.attach(3);
  joint1.attach(5);
  joint2.attach(6);
  hand.attach(9);
  gripper.attach(10);

  // Serial.print("Startup Sequence:");

  startUpSequence();

  // Serial.print("{0.1443, 0, -0.0138}");
  ra.setPosition({0.1443, 0, -0.0138});
  setState();

}

void loop()
{
  readSerial();
  ra.setPosition({x, y, z});
  setState();
}


void setState()
{
  // write base
  base.write(ra.state[0]);

  // write joint1
  for (double i = currentJoint1Pos; i != ra.state[1]; i += constrain(ra.state[1] - i, -1, 1))
  {
    joint1.write(i + 90);
    delay(20);
  }

  currentJoint1Pos = ra.state[1];
  joint1.write(currentJoint1Pos + 90);


  double dest = ra.state[2];
  joint2.write(-dest + 120);


  hand.write(w);
  gripper.write(h);
  //-45 --> 90


  // joint2.write(ra.state[2] + 45);
  // hand.write(ra.state[3]);
}

void startUpSequence()
{

  base.write(55);
  delay(1000);


  joint2.write(35);
  delay(1000);

  for (int i = 0; i < 180; i++)
  {
    joint1.write(i);
    delay(30);
  }

  for (int i = 180; i > 0; i--)
  {
    joint1.write(i);
    delay(30);
  }

  for (int i = 0; i < 90; i++)
  {
    joint1.write(i);
    delay(30);
  }
  delay(1000);
  //ARM upside
  
  for (int i = 35; i > 0; i--)
  {
    joint2.write(i);
    delay(10);
  }

  for (int i = 0; i < 180; i++)
  {
    joint2.write(i);
    delay(10);
  }

  for (int i = 180; i > 35; i--)
  {
    joint2.write(i);
    delay(10);
  }

  delay(100);

    hand.write(0);

    delay(1000);
     hand.write(180);

    delay(1000);

    gripper.write(0);

    delay(1000);
     gripper.write(180);

    delay(1000);

}

void printReceived()
{
  Serial.print("Received: ");

  Serial.print("x:");
  Serial.print(x, 4);

  Serial.print(" y:");
  Serial.print(y, 4);

  Serial.print(" z:");
  Serial.print(z, 4);

    Serial.print(" w:");
  Serial.print(w, 4);

    Serial.print(" h:");
  Serial.println(h, 4);
}

void readSerial()
{
  if (Serial.available() < 40)
    return;

  while(Serial.peek() == 'A') Serial.read();

  for (int i = 0; i < 20; i++)
    buffer[i] = Serial.read();

  float *vector = (float *)buffer;
  x = vector[0], y = vector[1], z = vector[2], w = vector[3], h = vector[4];

  printReceived();
}

