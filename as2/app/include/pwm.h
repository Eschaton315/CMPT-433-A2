#ifndef _PWM_H_
#define _PWM_H_

//configure pin to LED
void configLED(void);

//Creates the thread for pwm
void pwmThreadCreate(void);

//Runs join to successfully close the thread
void pwmThreadJoin(void);

//Calculate PWMFrequency
bool PWMledsOff(char* LEDPath);

//Turn PWM LEDs Off
bool PWMledsOn(char* LEDPath);

//Turn PWM LEDs On
int CalculatePWMFrequency(void);

//Change the frequency of LEDs with PWM
bool ChangePWMFrequency(int frequency);

//Change the LED colour to purple
void SetPWMledPurple(void);

//Check the period of the LED (blur as example) to determine 
//whether to switch or not to switch
int CheckPWMFrequency(void);

#endif 