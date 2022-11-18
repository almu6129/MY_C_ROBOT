#include <Arduino.h>
#include<Servo.h>

#include "arduino_uno.h"

Servo sweeper_servo;
uint16_t count_down = 0x2fff;     //The countdown value
uint8_t servo_val = 0;      //The angle values (0-180)
bool up = 1;          //Boolean to represent the states of incrementing angle values or decrementing angle values
uint16_t distance_arr[180];

void setup() {
  
  Serial.begin(9600);     //Beginning serial transmission

  sweeper_servo.attach(6);      //Attatching the sweeper_servo object to the 6 pin (PWM enabled)

  DDRB |= FIRST_BIT;       //Setting the directions of the echo and trigger GPIO pins
  DDRB &= ~SECOND_BIT;


}

void handle_servo();
uint16_t ping_distance();
void move(char direction_delta);
void sample_for_180_deg();

void loop() {

    /*****************************
     * Put code in the if statement below that needs to happen in sync with the servo motor movements.
    *****************************/

    if(count_down == 1){     //When the countdown reaches the bottom

    count_down = 0x2fff;    //reset the countdown

    handle_servo();

    distance_arr[servo_val] = ping_distance();   //calling the ping distance function everytime the servo increments/decrements its angle by one

    }

    count_down--;   //Decrementing the countdown

}

/******************************************************
 * Name: handle_servo() 
 * 
  * Description:
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

/***************************************************************
 * Name: ping_distance()
 * 
 * Description:
 * This is a function that takes advantage of the HC-SRO4 ultrasound sensor and gathers the distance to an
 * object in front of the sensor.
 * 
 * Return: It returns an unsigned 16 bit variable holding the distance in centimeters
*/

uint16_t ping_distance(){

  long time;      //This holds the value of the time it takes to heart the pulse back
  uint16_t cm;    //This holds our centimeter value to be returned

  PORTB &= ~FIRST_BIT;      //This is setting our pin 8 low
  delayMicroseconds(2);

  PORTB |= FIRST_BIT;      //This is setting our pin 8 high
  delayMicroseconds(10);
  PORTB &= ~FIRST_BIT;      //This is setting our pin 8 low

  time = pulseIn(ECHO_PIN, HIGH);     

  cm = time * .034 / 2;   //Converting from our time of flight to centimeters to target

  Serial.println(cm);     //Just for debugging purposes
  
  return cm;

}

/***************************************************************
 * name: move()
 * 
 * Description: 
 * This is a function that takes in a direction change, performs that direction change, and moves forward for a set ammount of time.
****************************************************************/

void move(char direction_delta){

}

/***************************************************************
 * name: sample_for_180_deg()
 * 
 * Description: 
 * This is a function that samples the distances depending on angle of servo for 2x180 degree swings of the servo scan
****************************************************************/

void sample_for_180_deg(){

}