#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "i2c.h"

#define GPIO_Config_1 "config-pin P9_18 i2c"
#define GPIO_CONFIG_2 "config-pin P9_17 i2c"
#define GPIO_EXPORT_1 "/sys/class/gpio/export"
#define GPIO_EXPORT_2 "/sys/class/gpio/export"
#define GPIO_EXPORT_1NUM "61"
#define GPIO_EXPORT_2NUM "44"
#define GPIO_DIR_OUT "out"

#define I2CDRV_LINUX_BUS0 "/dev/i2c-0"
#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"
#define I2CDRV_LINUX_BUS2 "/dev/i2c-2"
#define I2C_DEVICE_ADDRESS 0x20

#define GPIO_DIRECTION_1 "/sys/class/gpio/gpio61/direction"
#define GPIO_DIRECTION_2 "/sys/class/gpio/gpio44/direction"

#define GPIO_VALUE_1 "/sys/class/gpio/gpio61/value"
#define GPIO_VALUE_2 "/sys/class/gpio/gpio44/value"

#define 0_PT1 "i2cset -y 1 0x20 0x00 0xd1"
#define 0_PT2 "i2cset -y 1 0x20 0x01 0xa5"

#define 1_PT1 "i2cset -y 1 0x20 0x00 0xc0"
#define 1_PT2 "i2cset -y 1 0x20 0x01 0x4" 

#define 2_PT1 "i2cset -y 1 0x20 0x00 0x98
#define 2_PT2 "i2cset -y 1 0x20 0x01 0x83

#define 3_PT1 "i2cset -y 1 0x20 0x00 0xD8"
#define 3_PT2 "i2cset -y 1 0x20 0x01 0x01"

#define 4_PT1 "i2cset -y 1 0x20 0x00 0xc8"
#define 4_PT2 "i2cset -y 1 0x20 0x01 0x22"

#define 5_PT1 "i2cset -y 1 0x20 0x00 0x58"
#define 5_PT2 "i2cset -y 1 0x20 0x01 0x23"

#define 6_PT1 "i2cset -y 1 0x20 0x00 0x58"
#define 6_PT2 "i2cset -y 1 0x20 0x01 0xa3"

#define 7_PT1 "i2cset -y 1 0x20 0x00 0x02"
#define 7_PT2 "i2cset -y 1 0x20 0x01 0x05"

#define 8_PT1 "i2cset -y 1 0x20 0x00 0xd8"
#define 8_PT2 "i2cset -y 1 0x20 0x01 0xa3"

#define 9_PT1 "i2cset -y 1 0x20 0x00 0xc8"
#define 9_PT2 "i2cset -y 1 0x20 0x01 0x23"


//runCommand function taken from assignment page
void runCommand(char* command){
    // Execute the shell command (output into pipe)
    FILE *pipe = popen(command, "r");
    // Ignore output of the command; but consume it
    // so we don't get an error when closing the pipe.
    char buffer[1024];
    while (!feof(pipe) && !ferror(pipe)) {
    if (fgets(buffer, sizeof(buffer), pipe) == NULL)
        break;
        // printf("--> %s", buffer); // Uncomment for debugging
    }
    // Get the exit code from the pipe; non-zero is an error:
    int exitCode = WEXITSTATUS(pclose(pipe));
    if (exitCode != 0) {
        perror("Unable to execute command:");
        printf(" command: %s\n", command);
        printf(" exit code: %d\n", exitCode);
    }
}

//echo to file for editing their values
void EchoToFile(char* filePath, char* contents){
	// Open direction file
	int file = open(filePath, O_WRONLY);
	if (file < 0) {
		printf("Failed to read file");
		return;
	}

	int written = write(file, buff, strlen(buff));
	// Close
	close(file_desc);

	return;
}

/*
static int initI2cBus(char* bus, int address) { 
	int i2cFileDesc = open(bus, O_RDWR); 
	int result = ioctl(i2cFileDesc, I2C_SLAVE, address); 
	if (result < 0) { 
		perror("I2C: Unable to set I2C device to slave address."); 
		exit(1); 
	}
	
	return i2cFileDesc; 
}*/

//Code for initializing for I2C
//Note that it will not initialize for BUS!!
void InitializeI2C(){
	runCommand(GPIO_Config_1);
	runCommand(GPIO_Config_2);
	EchoToFile(GPIO_EXPORT_1, GPIO_EXPORT_1NUM);
	EchoToFile(GPIO_EXPORT_2, GPIO_EXPORT_2NUM);
	EchoToFile(GPIO_DIRECTION_1, GPIO_DIR_OUT);
	EchoToFile(GPIO_DIRECTION_2, GPIO_DIR_OUT);	
}

//Change digit displayed based on integer given
void ChangeDigit(int number){	
	switch (number){
		case 0:
			runCommand(0_PT1);
			runCommand(0_PT2);
			break;
		
		case 1:
			runCommand(1_PT1);
			runCommand(1_PT2);
			break;
			
		case 2:
			runCommand(2_PT1);
			runCommand(2_PT2);
			break;
			
		case 3:
			runCommand(3_PT1);
			runCommand(3_PT2);
			break;
			
		case 4:
			runCommand(4_PT1);
			runCommand(4_PT2);
			break;
			
		case 5:
			runCommand(5_PT1);
			runCommand(5_PT2);
			break;
			
		case 6:
			runCommand(6_PT1);
			runCommand(6_PT2);
			break;
			
		case 7:
			runCommand(7_PT1);
			runCommand(7_PT2);
			
			break;
			
		case 8:
			runCommand(8_PT1);
			runCommand(8_PT2);
			break;
	
		case 9:
			runCommand(9_PT1);
			runCommand(9_PT2);
			break;
	}
	
	
}

//Turns on Left Digit display
void DisplayLeftDigit(){
	EchoToFile(GPIO_VALUE_1, "0");
	EchoToFile(GPIO_VALUE_2, "0");
	EchoToFile(GPIO_VALUE_1, "1");
}

//Turns on Right Digit display
void DisplayRightDigit(){
	EchoToFile(GPIO_VALUE_1, "0");
	EchoToFile(GPIO_VALUE_2, "0");
	EchoToFile(GPIO_VALUE_2, "1");
}