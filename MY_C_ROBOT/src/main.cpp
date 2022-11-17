#include <Arduino.h>
#include<Servo.h>

#define TRIG 8
#define ECHO 9

Servo sweeper_servo;
uint16_t count_down = 0x2fff;     //The countdown value
uint8_t servo_val = 0;      //The angle values (0-180)
uint8_t direction_curr;
bool up = 1;          //Boolean to represent the states of incrementing angle values or decrementing angle values
uint16_t distance_arr[180];

void setup() {
  
  Serial.begin(9600);     //Beginning serial transmission

  sweeper_servo.attach(6);      //Attatching the sweeper_servo object to the 6 pin (PWM enabled)

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);


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

uint16_t ping_distance(){

  long time;
  uint16_t cm;

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  time = pulseIn(ECHO, HIGH);

  cm = time * .034 / 2;

  Serial.println(cm);
  
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