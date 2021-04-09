release: all
	rm *.o
	rm *.elf

TARGET		=	sample_prx

PRX_EXPORTS	=	exports.exp
USE_KERNEL_LIBC	=	1
USE_KERNEL_LIBS	=	1

OBJS		=	cmliblog.o main.o

INCDIR		=	
CFLAGS		=	-Os -G 0 -Wall -fno-strict-aliasing
ASFLAGS		=	$(CFLAGS)

LIBDIR		= 
LDFLAGS		=	-mno-crt0 -nostartfiles
LIBS		=	


PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak

