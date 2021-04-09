	.set noreorder

#include "pspstub.s"

	STUB_START "scePower", 0x40090000, 0x000D0005
	STUB_FUNC	0x2085D15D, scePowerGetBatteryLifePercent
	STUB_FUNC	0x8EFB3FA2, scePowerGetBatteryLifeTime
	STUB_FUNC	0xB4432BC8, scePowerGetBatteryChargingStatus
	STUB_FUNC	0xAC32C9CC, scePowerRequestSuspend
	STUB_FUNC	0x2B7C7CF4, scePowerRequestStandby
	STUB_FUNC	0x483CE86B, scePowerGetBatteryVolt
	STUB_FUNC	0x28E12023, scePowerGetBatteryTemp
	STUB_FUNC	0x87440F5E, scePowerIsPowerOnline
	STUB_FUNC	0xFEE03A2F, scePowerGetCpuClockFrequency
	STUB_FUNC	0x478FE6F5, scePowerGetBusClockFrequency
	STUB_FUNC	0x0AFD0D8B, scePowerIsBatteryExist
	STUB_FUNC	0xD3075926, scePowerIsLowBattery
	STUB_FUNC	0x1E490401, scePowerIsBatteryCharging
	STUB_END
