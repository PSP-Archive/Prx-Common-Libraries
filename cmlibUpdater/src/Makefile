release: all
	rm *.elf
	rm *.prx
#	rm *.o
	rm *.SFO

TARGET = cmlibUpdater
OBJS = main.o script.o file.o net.o http.o oe_malloc.o gui.o menu.o md5c.o

PSP_EBOOT_TITLE = cmLibUpdater
PSP_FW_VERSION = 200
EXTRA_TARGETS = EBOOT.PBP
BUILD_PRX = 1


INCDIR = 
CFLAGS = -O3 -G0 -Wall -DDEBUG
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LIBS = -lpspgu -lpsppower


PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
