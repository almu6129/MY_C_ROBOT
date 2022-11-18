/*********************************************************************
 * File name: arduino_uno.h
 * 
 * Description:
 * This file is a board specific header file meant to make the main functionality of my code more portable. It
 * contains all the definitions specific to the arduino uno's GPIO config and usage info. This is meant to be
 * the only (or one of the only) thing(s) you need to change in the event of a board type change.
*********************************************************************/

#ifndef ARDUINO_UNO
#define ARDUINO_UNO

#define ULTRA_SONIC_CONT PORTB
#define ULTRA_SONIC_DIR DDRB

#define FIRST_BIT 1
#define SECOND_BIT (1 << 1)

#define ECHO_PIN 9

#define SERVO_SWEEPER_PIN 6


#endif