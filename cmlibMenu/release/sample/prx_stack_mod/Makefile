TARGET		=	menu_test

PRX_EXPORTS	=	exports.exp
USE_KERNEL_LIBC	=	1
USE_KERNEL_LIBS	=	1

#6.35 Pro用で作る場合は PSP_HEN_VERSION を有効にしてコンパイル (先頭の#を外してコメントアウト）
#PSP_HEN_VERSION	= 	635

OBJS		=	exports.o 	\
			syslibc.o 	\
			cmlibMenu.o	\
			main.o

ifeq ($(PSP_HEN_VERSION),635)
OBJS		+=	../nidResolve/635/sceCtrl_driver.o
OBJS		+=	../nidResolve/635/sceDisplay_driver.o 
endif



INCDIR		=	
CFLAGS		=	-Os -G 0 -Wall -fno-strict-aliasing
ASFLAGS		=	$(CFLAGS)

LIBDIR		= 
LDFLAGS		=	-mno-crt0 -nostartfiles
LIBS		=	


PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak
