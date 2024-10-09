#include <Servo.h>
#include <Encoder.h>
#include <Adafruit_MotorShield.h>


Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Encoder Enc1(2, 3);
Encoder Enc2(18, 19);

Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);

Servo myservo;

int pos = 0;

int value1;
int value2;

void setup() {
  AFMS.begin();
  Serial.begin(9600);
  Serial.println("Begin ");
  myservo.attach(11);

  pinMode(2, INPUT);
  pinMode(3, INPUT);

  pinMode(18, INPUT);
  pinMode(19, INPUT);

  clear();
}

void loop() {
  if (Motor1Val() > Motor2Val()) {
    LeftMotor();
    Serial.print(Motor1Val(), Motor2Val());
  } 
  else if (Motor2Val() > Motor1Val()) {
    RightMotor();
    Serial.print(Motor1Val(), Motor2Val());
  } 
  else {
    LeftMotor();
    RightMotor();
    Serial.print(Motor1Val(), Motor2Val());
  }

  if (distanceMeasure() <= 500) {
    Serial.println(distanceMeasure());
    Stop();
    delay(1000);
    myservo.write(0);
    value1 = distanceMeasure();
    delay(3000);
    myservo.write(180);
    value2 = distanceMeasure();
    delay(3000);
    myservo.write(90);

    if (value1 > value2) {
      for(int i = 0; i < 2; i++){
        turnLeft();
        delay(2000);
      }
    }

    if(value2 > value1){
      for(int i = 0; i < 2; i++){
        turnRight();
        delay(2000);
      }
    }
  }
}

void RightMotor() {
  motor1->run(BACKWARD);
  motor1->setSpeed(150);
  motor2->run(BACKWARD);
  motor2->setSpeed(50);
}

void LeftMotor() {
  motor2->run(BACKWARD);
  motor2->setSpeed(150);
  motor1->run(BACKWARD);
  motor1->setSpeed(50);
}

void Stop() {
  motor1->run(RELEASE);
  motor2->run(RELEASE);
}

int Motor1Val() {
  int Motor1val = Enc1.read();
  return Motor1val;
}

int Motor2Val() {
  int Motor2val = Enc2.read();
  return Motor2val;
}

void clear() {
  Enc1.write(0);
  Enc2.write(0);
}

int distanceMeasure() {
  Serial.begin(9600);
  int urs = 7;
  int irs = 6;
  long pingtime;
  long distance;

  pinMode(urs, OUTPUT);
  digitalWrite(urs, HIGH);
  delayMicroseconds(5);
  digitalWrite(urs, LOW);
  delayMicroseconds(2);
  pinMode(irs, INPUT);
  pingtime = pulseIn(irs, HIGH);
  distance = 343 * pingtime;
  delay(25);
  return (distance * 0.001);
}

void turnRight(){
  motor2->run(BACKWARD);
  motor2->setSpeed(50);
  motor1->run(RELEASE);
}

void turnLeft(){
  motor1->run(BACKWARD);
  motor1->setSpeed(50);
  motor2->run(RELEASE);
}