
//Thanks takka!!
#include "common.h"

PSP_MODULE_INFO( "cmlibConv", PSP_MODULE_KERNEL, 0, 1 );



void SetSUPoint()
{
	StoU_convert_table[0x00] = SU->S00;
	StoU_convert_table[0x81] = SU->S81;
	StoU_convert_table[0x82] = SU->S82;
	StoU_convert_table[0x83] = SU->S83;
	StoU_convert_table[0x84] = SU->S84;
	StoU_convert_table[0x87] = SU->S87;
	StoU_convert_table[0x88] = SU->S88;
	StoU_convert_table[0x89] = SU->S89;
	StoU_convert_table[0x8a] = SU->S8a;
	StoU_convert_table[0x8b] = SU->S8b;
	StoU_convert_table[0x8c] = SU->S8c;
	StoU_convert_table[0x8d] = SU->S8d;
	StoU_convert_table[0x8e] = SU->S8e;
	StoU_convert_table[0x8f] = SU->S8f;
	StoU_convert_table[0x90] = SU->S90;
	StoU_convert_table[0x91] = SU->S91;
	StoU_convert_table[0x92] = SU->S92;
	StoU_convert_table[0x93] = SU->S93;
	StoU_convert_table[0x94] = SU->S94;
	StoU_convert_table[0x95] = SU->S95;
	StoU_convert_table[0x96] = SU->S96;
	StoU_convert_table[0x97] = SU->S97;
	StoU_convert_table[0x98] = SU->S98;
	StoU_convert_table[0x99] = SU->S99;
	StoU_convert_table[0x9a] = SU->S9a;
	StoU_convert_table[0x9b] = SU->S9b;
	StoU_convert_table[0x9c] = SU->S9c;
	StoU_convert_table[0x9d] = SU->S9d;
	StoU_convert_table[0x9e] = SU->S9e;
	StoU_convert_table[0x9f] = SU->S9f;
	StoU_convert_table[0xe0] = SU->Se0;
	StoU_convert_table[0xe1] = SU->Se1;
	StoU_convert_table[0xe2] = SU->Se2;
	StoU_convert_table[0xe3] = SU->Se3;
	StoU_convert_table[0xe4] = SU->Se4;
	StoU_convert_table[0xe5] = SU->Se5;
	StoU_convert_table[0xe6] = SU->Se6;
	StoU_convert_table[0xe7] = SU->Se7;
	StoU_convert_table[0xe8] = SU->Se8;
	StoU_convert_table[0xe9] = SU->Se9;
	StoU_convert_table[0xea] = SU->Sea;
	StoU_convert_table[0xed] = SU->Sed;
	StoU_convert_table[0xee] = SU->See;
	StoU_convert_table[0xfa] = SU->Sfa;
	StoU_convert_table[0xfb] = SU->Sfb;
	StoU_convert_table[0xfc] = SU->Sfc;
}


void SetUSPoint()
{
	UtoS_convert_table[0x00] = US->U00;
	UtoS_convert_table[0x03] = US->U03;
	UtoS_convert_table[0x04] = US->U04;
	UtoS_convert_table[0x20] = US->U20;
	UtoS_convert_table[0x21] = US->U21;
	UtoS_convert_table[0x22] = US->U22;
	UtoS_convert_table[0x23] = US->U23;
	UtoS_convert_table[0x25] = US->U25;
	UtoS_convert_table[0x26] = US->U26;
	UtoS_convert_table[0x30] = US->U30;
	UtoS_convert_table[0x4e] = US->U4e;
	UtoS_convert_table[0x4f] = US->U4f;
	UtoS_convert_table[0x50] = US->U50;
	UtoS_convert_table[0x51] = US->U51;
	UtoS_convert_table[0x52] = US->U52;
	UtoS_convert_table[0x53] = US->U53;
	UtoS_convert_table[0x54] = US->U54;
	UtoS_convert_table[0x55] = US->U55;
	UtoS_convert_table[0x56] = US->U56;
	UtoS_convert_table[0x57] = US->U57;
	UtoS_convert_table[0x58] = US->U58;
	UtoS_convert_table[0x59] = US->U59;
	UtoS_convert_table[0x5a] = US->U5a;
	UtoS_convert_table[0x5b] = US->U5b;
	UtoS_convert_table[0x5c] = US->U5c;
	UtoS_convert_table[0x5d] = US->U5d;
	UtoS_convert_table[0x5e] = US->U5e;
	UtoS_convert_table[0x5f] = US->U5f;
	UtoS_convert_table[0x60] = US->U60;
	UtoS_convert_table[0x61] = US->U61;
	UtoS_convert_table[0x62] = US->U62;
	UtoS_convert_table[0x63] = US->U63;
	UtoS_convert_table[0x64] = US->U64;
	UtoS_convert_table[0x65] = US->U65;
	UtoS_convert_table[0x66] = US->U66;
	UtoS_convert_table[0x67] = US->U67;
	UtoS_convert_table[0x68] = US->U68;
	UtoS_convert_table[0x69] = US->U69;
	UtoS_convert_table[0x6a] = US->U6a;
	UtoS_convert_table[0x6b] = US->U6b;
	UtoS_convert_table[0x6c] = US->U6c;
	UtoS_convert_table[0x6d] = US->U6d;
	UtoS_convert_table[0x6e] = US->U6e;
	UtoS_convert_table[0x6f] = US->U6f;
	UtoS_convert_table[0x70] = US->U70;
	UtoS_convert_table[0x71] = US->U71;
	UtoS_convert_table[0x72] = US->U72;
	UtoS_convert_table[0x73] = US->U73;
	UtoS_convert_table[0x74] = US->U74;
	UtoS_convert_table[0x75] = US->U75;
	UtoS_convert_table[0x76] = US->U76;
	UtoS_convert_table[0x77] = US->U77;
	UtoS_convert_table[0x78] = US->U78;
	UtoS_convert_table[0x79] = US->U79;
	UtoS_convert_table[0x7a] = US->U7a;
	UtoS_convert_table[0x7b] = US->U7b;
	UtoS_convert_table[0x7c] = US->U7c;
	UtoS_convert_table[0x7d] = US->U7d;
	UtoS_convert_table[0x7e] = US->U7e;
	UtoS_convert_table[0x7f] = US->U7f;
	UtoS_convert_table[0x80] = US->U80;
	UtoS_convert_table[0x81] = US->U81;
	UtoS_convert_table[0x82] = US->U82;
	UtoS_convert_table[0x83] = US->U83;
	UtoS_convert_table[0x84] = US->U84;
	UtoS_convert_table[0x85] = US->U85;
	UtoS_convert_table[0x86] = US->U86;
	UtoS_convert_table[0x87] = US->U87;
	UtoS_convert_table[0x88] = US->U88;
	UtoS_convert_table[0x89] = US->U89;
	UtoS_convert_table[0x8a] = US->U8a;
	UtoS_convert_table[0x8b] = US->U8b;
	UtoS_convert_table[0x8c] = US->U8c;
	UtoS_convert_table[0x8d] = US->U8d;
	UtoS_convert_table[0x8e] = US->U8e;
	UtoS_convert_table[0x8f] = US->U8f;
	UtoS_convert_table[0x90] = US->U90;
	UtoS_convert_table[0x91] = US->U91;
	UtoS_convert_table[0x92] = US->U92;
	UtoS_convert_table[0x93] = US->U93;
	UtoS_convert_table[0x94] = US->U94;
	UtoS_convert_table[0x95] = US->U95;
	UtoS_convert_table[0x96] = US->U96;
	UtoS_convert_table[0x97] = US->U97;
	UtoS_convert_table[0x98] = US->U98;
	UtoS_convert_table[0x99] = US->U99;
	UtoS_convert_table[0x9a] = US->U9a;
	UtoS_convert_table[0x9b] = US->U9b;
	UtoS_convert_table[0x9c] = US->U9c;
	UtoS_convert_table[0x9d] = US->U9d;
	UtoS_convert_table[0x9e] = US->U9e;
	UtoS_convert_table[0x9f] = US->U9f;
	UtoS_convert_table[0xff] = US->Uff;
}

int LoadFile(int flag){
    SceUID fd;
    SceSize size, readsize, struct_zize = flag == 1 ? sizeof(StoU) : sizeof(UtoS);
    char path[64] = "ms0:/seplugins/lib/conv/";
    char *conv_bin[] = {"StoU.bin", "UtoS.bin"};
	void *conv_buf;
    
    // make path
    strcat(path, conv_bin[flag - 1]);
    
    // file open
    fd = sceIoOpen(path, PSP_O_RDONLY, 0777);
    if(fd < 0){
        path[0] = 'e';
        path[1] = 'f';
        fd = sceIoOpen(path, PSP_O_RDONLY, 0777);
        if(fd < 0){
            return fd;
        }
    }
    
    // get file size
    size = sceIoLseek(fd, 0, SEEK_END);
    if(size <= 0 || struct_zize != size){
        sceIoClose(fd);
        return -2;
    }
    
    // malloc
    //mem_set_alloc_mode(MEM_AUTO);
    conv_buf = mem_alloc(size);
    if(conv_buf == NULL){
        sceIoClose(fd);
        return -3;
    }
    
    // read font
    sceIoLseek(fd, 0, SEEK_SET);
    readsize = sceIoRead(fd, conv_buf, size);
    sceIoClose(fd);
    if(readsize != size){
        mem_free(conv_buf);
		conv_buf = NULL;
        return -4;
    }
	if(flag == 1)
	{
		SU = conv_buf;
	} else {
		US = conv_buf;
	}
    return 0;
}


// entry point
int module_start(SceSize args, void *argp){
	return 0;
}

int module_stop(SceSize args, void *argp){
	return 0;
}

