#include <Arduino.h>
#include<Servo.h>

Servo sweeper_servo;
uint16_t count_down = 0xffff;
uint8_t servo_val = 0;
bool up = 1;

void setup() {
  
  Serial.begin(9600);

  sweeper_servo.attach(6);


}

void loop() {

    if(count_down == 1){

      count_down = 0xffff;

      if(up)
      {
      sweeper_servo.write(servo_val++);
      }
      else
      {
      sweeper_servo.write(servo_val--);
      }

    }

    if(servo_val == 180)
    {
    up = 0;
    }
    else if(servo_val == 0)
    {
    up = 1;
    }

    count_down--;

}