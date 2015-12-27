#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/sysinfo.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

char* getIPaddress(char* name);

int getTotalMemoryKB(void) {

	int MemTotal = -1;
	int tmp;
	FILE *meminfo = fopen("/proc/meminfo", "r");

	if (meminfo != NULL) {

		char line[256];
		while (fgets(line, sizeof(line), meminfo)) {

			if (sscanf(line, "MemTotal: %d kB", &tmp) == 1)
				MemTotal = tmp;
		}

		fclose(meminfo);
	}

	return MemTotal;
}


int getAvalibleMemoryeKB(void) {

	int MemAvailable = -1;
	int tmp;
	FILE *meminfo = fopen("/proc/meminfo", "r");

	if (meminfo != NULL) {

		char line[256];
		while (fgets(line, sizeof(line), meminfo)) {

			if (sscanf(line, "MemAvailable: %d kB", &tmp) == 1)
				MemAvailable = tmp;
		}

		fclose(meminfo);
	}

	return MemAvailable;
}

int getUsedMemoryeKB(void) {
	return getTotalMemoryKB() - getAvalibleMemoryeKB();
}

long getUpTimeSec(void) {

	struct sysinfo info;
	sysinfo(&info);

	return info.uptime;
}

int getNumProcesses(void) {

	struct sysinfo info;
	sysinfo(&info);

	return info.procs;
}


char* getIPaddress(char* name) {

	struct ifaddrs *ifaddr, *ifa;
	int s;
	char* host = malloc(NI_MAXHOST * sizeof(char));

	if (getifaddrs(&ifaddr) == -1) {
		return NULL;
	}

	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL)
			continue;

		s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

		if ((strcmp(ifa->ifa_name, name) == 0) && (ifa->ifa_addr->sa_family == AF_INET)) {

			if (s != 0) {
				return NULL;
			}

			return host;
		}
	}

	return NULL;

}

char* getWirelessIPaddress(void) {
	return getIPaddress("wlan0");
}

char* getWiredIPaddress(void) {
	return getIPaddress("eth0");
}

float getCpuUsage(void) {

	long double a[4], b[4], loadavg;
	FILE *fp;

	fp = fopen("/proc/stat", "r");
	fscanf(fp, "%*s %Lf %Lf %Lf %Lf", &a[0], &a[1], &a[2], &a[3]);
	fclose(fp);
	sleep(1);

	fp = fopen("/proc/stat", "r");
	fscanf(fp, "%*s %Lf %Lf %Lf %Lf", &b[0], &b[1], &b[2], &b[3]);
	fclose(fp);

	loadavg = ((b[0] + b[1] + b[2]) - (a[0] + a[1] + a[2])) / ((b[0] + b[1] + b[2] + b[3]) - (a[0] + a[1] + a[2] + a[3]));

	return (float)(loadavg * 100);
}