#define L1Pin 14
#define L2Pin 27
#define M1Pin 26
#define M2Pin 25
#define R1Pin 35
#define R2Pin 34
#define I2C_SLAVE_ADDR 0x04
#include <Wire.h>

int leftMotor_speed = 255;
int rightMotor_speed = 253;
int black_value=1,white_value=1, distance=1;
int servoAngle;

void setup() {
 Serial.begin(9600);
 Wire.begin();

}

void loop() {
 double Left_1 = map(constrain(analogRead(L1Pin),black_value,white_value),black_value,white_value,5,0);
 double Left_2 = map(constrain(analogRead(L2Pin),black_value,white_value),black_value,white_value,5,0);
 double Mid_1 = map(constrain(analogRead(M1Pin),black_value,white_value),black_value,white_value,5,0);
 double Mid_2 = map(constrain(analogRead(M2Pin),black_value,white_value),black_value,white_value,5,0);
 double Right_1 = map(constrain(analogRead(R1Pin),black_value,white_value),black_value,white_value,5,0);
 double Right_2 = map(constrain(analogRead(R2Pin),black_value,white_value),black_value,white_value,5,0);
 double weighted_avg = ((Left_1*distance)+(Left_2*distance)+(Mid_1*distance)+(Mid_1*distance)+(Mid_2*distance)+(Right_1* distance)+(Right_2* distance))/(Left_1 + Left_2 + Mid_1 + Mid_2 + Right_1 + Right_2);

if (weighted_avg < 0)
{
  servoAngle = 35; 
}
else if  (weighted_avg > 0) {
  servoAngle = 145;
}
else 
{
  servoAngle = 85;
}
Transmit_to_arduino(leftMotor_speed,  rightMotor_speed, servoAngle);

}
 void Transmit_to_arduino(int leftMotor_speed, int rightMotor_speed, int servoAngle)

{
  Wire.beginTransmission(I2C_SLAVE_ADDR); // transmit to device #4
  Wire.write((byte)((leftMotor_speed & 0x0000FF00) >> 8));    // first byte of x, containing bits 16 to 9
  Wire.write((byte)(leftMotor_speed & 0x000000FF));           // second byte of x, containing the 8 LSB - bits 8 to 1
  Wire.write((byte)((rightMotor_speed & 0x0000FF00) >> 8));   // first byte of y, containing bits 16 to 9
  Wire.write((byte)(rightMotor_speed & 0x000000FF));          // second byte of y, containing the 8 LSB - bits 8 to 1
  Wire.write((byte)((servoAngle & 0x0000FF00) >> 8));    // first byte of x, containing bits 16 to 9
  Wire.write((byte)(servoAngle & 0x000000FF));
  Wire.endTransmission();   // stop transmitting
}