TARGET=libcmlibMenu.a

all: $(TARGET)

OBJS = cmlibMenu_0000.o cmlibMenu_0001.o cmlibMenu_0002.o cmlibMenu_0003.o cmlibMenu_0004.o cmlibMenu_0005.o cmlibMenu_0006.o cmlibMenu_0007.o cmlibMenu_0008.o cmlibMenu_0009.o cmlibMenu_0010.o cmlibMenu_0011.o cmlibMenu_0012.o cmlibMenu_0013.o cmlibMenu_0014.o cmlibMenu_0015.o cmlibMenu_0016.o cmlibMenu_0017.o cmlibMenu_0018.o cmlibMenu_0019.o cmlibMenu_0020.o cmlibMenu_0021.o cmlibMenu_0022.o cmlibMenu_0023.o cmlibMenu_0024.o cmlibMenu_0025.o cmlibMenu_0026.o cmlibMenu_0027.o cmlibMenu_0028.o cmlibMenu_0029.o cmlibMenu_0030.o cmlibMenu_0031.o cmlibMenu_0032.o cmlibMenu_0033.o cmlibMenu_0034.o cmlibMenu_0035.o cmlibMenu_0036.o cmlibMenu_0037.o cmlibMenu_0038.o cmlibMenu_0039.o cmlibMenu_0040.o cmlibMenu_0041.o cmlibMenu_0042.o cmlibMenu_0043.o cmlibMenu_0044.o cmlibMenu_0045.o cmlibMenu_0046.o cmlibMenu_0047.o cmlibMenu_0048.o cmlibMenu_0049.o cmlibMenu_0050.o cmlibMenu_0051.o cmlibMenu_0052.o cmlibMenu_0053.o cmlibMenu_0054.o cmlibMenu_0055.o cmlibMenu_0056.o cmlibMenu_0057.o cmlibMenu_0058.o cmlibMenu_0059.o cmlibMenu_0060.o

PSPSDK=$(shell psp-config --pspsdk-path)

clean:
	rm -f $(OBJS) $(TARGET)

CC=psp-gcc
INCDIR = 
CFLAGS = -Os -G0 -Wall -fno-builtin-printf -I$(PSPSDK)/include
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LDFLAGS = -nodefaultlibs

LIBDIR =

$(TARGET): $(OBJS)
	psp-ar q $(TARGET) $(OBJS)
	psp-ranlib $(TARGET)

$(OBJS): cmlibMenu.S
	$(CC) $(CFLAGS) -DF_$* $< -c -o $@
