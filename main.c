#include <stdio.h>
#include <unistd.h> /* sleep */
#include "functions.h"

int main(int argc, char const *argv[]) {

	int refreshRate = 5; /*sec*/

	char* wired = getWiredIPaddress();
	char* wireless = getWirelessIPaddress();

	long t;
	int hours, mins, secs;

	if (wired)
		printf(" %s\n", wired);
	else if (wireless)
		printf(" %s\n", wireless);
	else
		printf("No Connection\n");

	while (1) {

		printf("CPU:%02.0f%% RAM:%02.0f%% \r", 100 * getCpuUsage(), 100 * (getTotalMemoryKB() - getAvalibleMemoryeKB()) / ((float)getTotalMemoryKB()));
		fflush(stdout);

		sleep(refreshRate);

		t = getUpTimeSec();
		hours = t / 3600;
		t = t % 3600;
		mins = t / 60;
		secs = t % 60;

		printf("%02dh : %02dm : %02ds                       \r", hours, mins, secs);
		fflush(stdout);

		sleep(refreshRate);
	}

	return 0;
}
