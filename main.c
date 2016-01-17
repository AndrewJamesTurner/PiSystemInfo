#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* sleep */
#include <wiringPi.h>           //WiringPi headers
#include <lcd.h>                //LCD headers from WiringPi
#include "functions.h"


//Pin numbers below are the WiringPi pin numbers

#define LCD_RS  11               //Register select pin
#define LCD_E   10               //Enable Pin
#define LCD_D4  6               //Data pin 4
#define LCD_D5  5               //Data pin 5
#define LCD_D6  4               //Data pin 6
#define LCD_D7  1               //Data pin 7


int main(int argc, char const *argv[]) {

	int refreshRate = 5; /*sec*/
	char* wired = getWiredIPaddress();
	char* wireless = getWirelessIPaddress();
	long t;
	int hours, mins, secs;

	 int lcd;                //Handle for LCD
   	 wiringPiSetup();        //Initialise WiringPi

	char* line1 = malloc(16 * sizeof(char));
	char* line2 = malloc(16 * sizeof(char));


	//Initialise LCD(int rows, int cols, int bits, int rs, int enable, int d0, int d1, int d2, int d3, int d4, int d$
	if (lcd = lcdInit (2, 16,4, LCD_RS, LCD_E ,LCD_D4 , LCD_D5, LCD_D6,LCD_D7,0,0,0,0)){
		printf ("lcd init failed! \n");
		return -1 ;
	}

//	sprintf(line1, "QWERTY");


//	 lcdPosition(lcd,0,0);  //Position cursor on the first line in the first column
//    lcdPuts(lcd, line1);  //Print the text on the LCD at the current cursor postion
//    getchar();                      //Wait for key press



	lcdPosition(lcd, 0, 0);

	if (wired){
		sprintf(line1, "%s", wired);
		lcdPuts(lcd, line1);
	}
	else if (wireless){
		sprintf(line1, "%s", wireless);
		lcdPuts(lcd, line1);
	}
	else{
		lcdPuts(lcd, "No Connection");
	}


	while (1) {

		sprintf(line2, "CPU:%.0f%% RAM:%.0f%% ", 100 * getCpuUsage(), 100 * (getTotalMemoryKB() - getAvalibleMemoryeKB()) / ((float)getTotalMemoryKB()));
		lcdPosition(lcd,0,1);
		lcdPuts(lcd, line2);

		sleep(refreshRate);

		t = getUpTimeSec();
		hours = t / 3600;
		t = t % 3600;
		mins = t / 60;
		secs = t % 60;

		sprintf(line2, "%02dh : %02dm : %02ds", hours, mins, secs);
		lcdPosition(lcd,0,1);
		lcdPuts(lcd, line2);

		sleep(refreshRate);
	}

	return 0;
}
