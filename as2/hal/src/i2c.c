#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "hal/i2c.h"

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

#define NUM0_PT1 "i2cset -y 1 0x20 0x00 0xd1"
#define NUM0_PT2 "i2cset -y 1 0x20 0x01 0xa5"

#define NUM1_PT1 "i2cset -y 1 0x20 0x00 0xc0"
#define NUM1_PT2 "i2cset -y 1 0x20 0x01 0x4" 

#define NUM2_PT1 "i2cset -y 1 0x20 0x00 0x98"
#define NUM2_PT2 "i2cset -y 1 0x20 0x01 0x83"

#define NUM3_PT1 "i2cset -y 1 0x20 0x00 0xD8"
#define NUM3_PT2 "i2cset -y 1 0x20 0x01 0x01"

#define NUM4_PT1 "i2cset -y 1 0x20 0x00 0xc8"
#define NUM4_PT2 "i2cset -y 1 0x20 0x01 0x22"

#define NUM5_PT1 "i2cset -y 1 0x20 0x00 0x58"
#define NUM5_PT2 "i2cset -y 1 0x20 0x01 0x23"

#define NUM6_PT1 "i2cset -y 1 0x20 0x00 0x58"
#define NUM6_PT2 "i2cset -y 1 0x20 0x01 0xa3"

#define NUM7_PT1 "i2cset -y 1 0x20 0x00 0x02"
#define NUM7_PT2 "i2cset -y 1 0x20 0x01 0x05"

#define NUM8_PT1 "i2cset -y 1 0x20 0x00 0xd8"
#define NUM8_PT2 "i2cset -y 1 0x20 0x01 0xa3"

#define NUM9_PT1 "i2cset -y 1 0x20 0x00 0xc8"
#define NUM9_PT2 "i2cset -y 1 0x20 0x01 0x23"


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

	int written = write(file, contents, strlen(contents));
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
			runCommand(NUM0_PT1);
			runCommand(NUM0_PT2);
			break;
		
		case 1:
			runCommand(NUM1_PT1);
			runCommand(NUM1_PT2);
			break;
			
		case 2:
			runCommand(NUM2_PT1);
			runCommand(NUM2_PT2);
			break;
			
		case 3:
			runCommand(NUM3_PT1);
			runCommand(NUM3_PT2);
			break;
			
		case 4:
			runCommand(NUM4_PT1);
			runCommand(NUM4_PT2);
			break;
			
		case 5:
			runCommand(NUM5_PT1);
			runCommand(NUM5_PT2);
			break;
			
		case 6:
			runCommand(NUM6_PT1);
			runCommand(NUM6_PT2);
			break;
			
		case 7:
			runCommand(NUM7_PT1);
			runCommand(NUM7_PT2);
			
			break;
			
		case 8:
			runCommand(NUM8_PT1);
			runCommand(NUM8_PT2);
			break;
	
		case 9:
			runCommand(NUM9_PT1);
			runCommand(NUM9_PT2);
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