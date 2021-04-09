
#include "common.h"

u16 *StoU_convert_table[0x100] = {0};
u16 *UtoS_convert_table[0x100] = {0};


void libConvFreeMem()
{
	if(US != NULL){
		mem_free(US);
		memset(UtoS_convert_table, 0, sizeof(UtoS_convert_table));
	}
	if(SU != NULL){
		mem_free(SU);
		memset(StoU_convert_table, 0, sizeof(StoU_convert_table));
	}
}
