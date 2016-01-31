#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 		/* sleep */
#include <wiringPi.h>           /* WiringPi headers */
#include <lcd.h>                /* LCD headers from WiringPi */
#include "functions.h"


/* Pin numbers below are the WiringPi pin numbers */

#define LCD_RS  11              /* Register select pin */
#define LCD_E   10              /* Enable Pin */
#define LCD_D4  6               /* Data pin 4 */
#define LCD_D5  5               /* Data pin 5 */
#define LCD_D6  4               /* Data pin 6 */
#define LCD_D7  1               /* Data pin 7 */


void clearLCD(int lcd);

int main(int argc, char const *argv[]) {

	int refreshRate = 10; /*sec*/
	char* wired = getWiredIPaddress();
	char* wireless = getWirelessIPaddress();
	long t;
	int hours, mins, secs;
	int i;
	int lcd;                /* Handle for LCD */
	char* line;

	wiringPiSetup();        /* Initialise WiringPi */

	line = malloc(16 * sizeof(char));


	lcd = lcdInit (2, 16, 4, LCD_RS, LCD_E , LCD_D4 , LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);


	/* Initialise LCD(int rows, int cols, int bits, int rs, int enable, int d0, int d1, int d2, int d3, int d4, int d$ */
	if (lcd) {
		printf ("lcd init failed! \n");
		return -1;
	}

	while (1) {

		if (wired)
			sprintf(line, "%s", wired);
		else if (wireless)
			sprintf(line, "%s", wireless);
		else
			sprintf(line, "%s", "No Connection");

		clearLCD(lcd);
		lcdPosition(lcd, 0, 0);
		lcdPuts(lcd, line);

		for (i = 0; i < refreshRate; ++i) {

			sprintf(line, "CPU:%.0f%% RAM:%.0f%% ", 100 * getCpuUsage(), 100 * (getTotalMemoryKB() - getAvalibleMemoryeKB()) / ((float)getTotalMemoryKB()));

			clearLCD(lcd);
			lcdPosition(lcd, 0, 1);
			lcdPuts(lcd, line);
			sleep(1);
		}

		for (i = 0; i < refreshRate; ++i) {

			t = getUpTimeSec();
			hours = t / 3600;
			t = t % 3600;
			mins = t / 60;
			secs = t % 60;

			sprintf(line, "%02dh : %02dm : %02ds", hours, mins, secs);

			clearLCD(lcd);
			lcdPosition(lcd, 0, 1);
			lcdPuts(lcd, line);

			sleep(1);
		}
	}

	return 0;
}

void clearLCD(int lcd) {

	lcdPosition(lcd, 0, 0);
	lcdPuts(lcd, "                ");

	lcdPosition(lcd, 0, 1);
	lcdPuts(lcd, "                ");
}