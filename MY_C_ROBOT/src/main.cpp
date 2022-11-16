#include <Arduino.h>
#include<Servo.h>

Servo sweeper_servo;
uint16_t count_down = 0x2fff;     //The countdown value
uint8_t servo_val = 0;      //The angle values (0-180)
bool up = 1;          //Boolean to represent the states of incrementing angle values or decrementing angle values

void setup() {
  
  Serial.begin(9600);     //Beginning serial transmission

  sweeper_servo.attach(6);      //Attatching the sweeper_servo object to the 6 pin (PWM enabled)


}

void handle_servo();

void loop() {

    /*****************************
     * Put code in the if statement below that needs to happen in sync with the servo motor movements.
    *****************************/

    if(count_down == 1){     //When the countdown reaches the bottom

    count_down = 0x2fff;    //reset the countdown

    handle_servo();

    }

    count_down--;   //Decrementing the countdown

}

/******************************************************
  * This function is meant to help with non blocking code. There is a 16 bit variable that counds down and once it reaches one it will call
  * this function and either increment or decrement the servo angle value. It makes it 
  * so the other operations in the main function can continue without any polling.
*******************************************************/

void handle_servo(){

    if(up)                  //reading a flag whether we are going up in angle values or down
    {
      sweeper_servo.write(servo_val++);   //Increment the angle if we are going up in angle values currently
    }
    else
    {
      sweeper_servo.write(servo_val--);   //decrement the angle if we are currently going downwards in angle values
    }

    if(servo_val == 180)    // checking to see if the we need to reverse the direction on increasing/decreasing angle values
    {
    up = 0;       //Changing the state of the increment/decrement
    }
    else if(servo_val == 0)   // checking to see if the we need to reverse the direction on increasing/decreasing angle values
    {
    up = 1;       //Changing the state of the increment/decrement
    }

  return;
}