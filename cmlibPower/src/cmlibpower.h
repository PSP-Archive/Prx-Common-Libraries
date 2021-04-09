#ifndef _CM_LIB_POWER_
#define _CM_LIB_POWER_

#include <psppower.h>

typedef struct {
	int chargeStatus;
	int lifePer;
	int lifeTime;
	int cpuClock;
	int busClock;
	int temp;
	int volt;
	int acStatus;
	int isExist;
	int isLow;
	int isCharging;
} POWER_INFO;

typedef struct {
	int cpuClock;
	int busClock;
} CPU_INFO;

#define SLEEP_MODE    0
#define REBOOT_MODE   1
#define SHUTDOWN_MODE 2

#define NO_CHARGING   0
#define CHARGING      1

#define POWER_ONLINE  1
#define POWER_OFFLINE 0

int  libPowerControll(int mode);
void libExeSoftReset(void);
int  libSetCpuClock(int cpuClock);
CPU_INFO libGetCpuClock(void);
int  libGetChargeStatus(void);
int  libGetBatteryLifePer(void);
int  libGetBatteryLifeTime(void);
int  libGetBatteryTemp(void);
float libGetBatteryVolt(void);
int  libIsPowerOnline(void);
int  libIsBatteryExist(void);
int  libIsLowBattery(void);
int  libIsBatteryCharging(void);
POWER_INFO libGetPowerInfo(void);

#endif

