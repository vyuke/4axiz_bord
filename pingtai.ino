#include "I2Cdev.h"
#include "Wire.h"
#include "MPU6050.h"
#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;
int mind = 40;
int maxd = 130;

#define LED_PIN 13
bool blinkState = false;

void setup() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();

  // initialize serial communication
  // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
  // it's really up to you depending on your project)
  Serial.begin(9600);

  // initialize device
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();

  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  // configure Arduino LED for
  pinMode(LED_PIN, OUTPUT);

  myservo1.attach(8);
  myservo2.attach(9);
  myservo3.attach(10);
  myservo4.attach(11);

}

void servomin()
{
  myservo1.write(mind);
  myservo2.write(mind);
  myservo3.write(mind);
  myservo4.write(mind);
  delay(100);
}
void servomax()
{
  myservo1.write(maxd);
  myservo2.write(maxd);
  myservo3.write(maxd);
  myservo4.write(maxd);
  delay(100);
}

void servowork(int x, int y)
{

  int servo1 = map(x, -100, 100, 150, 40);
  int servo3 = map(x, -100, 100, 30, 150);
  int servo2 = map(y, -100, 100, 30, 150);
  int servo4 = map(y, -100, 100, 150, 40);
  myservo1.write(servo1);
  myservo3.write(servo3);
  ///////////////////x
  myservo2.write(servo2);
  myservo4.write(servo4);
  /////////////y
  Serial.println(x);



  //myservo1.write(servo1);
  // myservo3.write(servo3);
  //servomin();
  // servomax();

}
void mpu()
{
  // read raw accel/gyro measurements from device
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // these methods (and a few others) are also available
  //accelgyro.getAcceleration(&ax, &ay, &az);
  //accelgyro.getRotation(&gx, &gy, &gz);

  // display tab-separated accel/gyro x/y/z values
  // Serial.print("a/g:\t");
  // Serial.println(ax / 100);// Serial.print("\t");
  // Serial.print(ay / 100); Serial.print("\t");
  // Serial.print(az/100); Serial.print("\t");
  //Serial.print(gx/100); Serial.print("\t");
  //Serial.print(gy/100); Serial.print("\t");
  // Serial.println(gz/100);
  delay(5);
  // blink LED to indicate activity
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);

}

void loop() {
  mpu();
  servowork(ax / 100, ay / 100);
}





