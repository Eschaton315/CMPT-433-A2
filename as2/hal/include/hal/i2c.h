#ifndef _I2C_H_
#define _I2C_H_

//Code for initializing for I2C
//Note that it will not initialize for BUS!!
void InitializeI2C();

//Change digit displayed based on integer given
void ChangeDigit(int number);

//Turns on Left Digit display
void DisplayLeftDigit();

//Turns on Right Digit display
void DisplayRightDigit();

#endif 