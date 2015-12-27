#ifndef FUNCTIONS_H
#define FUNCTIONS_H

char* getWirelessIPaddress(void);
char* getWiredIPaddress(void);

float getCpuUsage(void);

int getTotalMemoryKB(void);
int getAvalibleMemoryeKB(void);
int getUsedMemoryeKB(void);

long getUpTimeSec(void);

#endif /* FUNCTIONS_H */