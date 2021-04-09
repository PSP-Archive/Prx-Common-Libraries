	.set noreorder

#include "pspstub.s"

	STUB_START "cmlibPower",0x40090000,0x000E0005
	STUB_FUNC  0x04BDE8E2,libPowerControll
	STUB_FUNC  0x7B9CE7F9,libExeSoftReset
	STUB_FUNC  0xC1684665,libSetCpuClock
	STUB_FUNC  0x2707003B,libGetCpuClock
	STUB_FUNC  0x9870F0B0,libGetChargeStatus
	STUB_FUNC  0xA0FB7B88,libGetBatteryLifePer
	STUB_FUNC  0xA2922AA2,libGetBatteryLifeTime
	STUB_FUNC  0x3FDAD4C3,libGetBatteryTemp
	STUB_FUNC  0x1D0B5DC4,libGetBatteryVolt
	STUB_FUNC  0x2EC95275,libIsPowerOnline
	STUB_FUNC  0x81502A81,libIsBatteryExist
	STUB_FUNC  0x9557B46A,libIsLowBattery
	STUB_FUNC  0x941319EB,libIsBatteryCharging
	STUB_FUNC  0x6DCF2BAF,libGetPowerInfo
	STUB_END
