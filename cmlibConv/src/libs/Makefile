TARGET=libcmlibConv.a

all: $(TARGET)

OBJS = cmlibConv_0000.o cmlibConv_0001.o cmlibConv_0002.o cmlibConv_0003.o cmlibConv_0004.o cmlibConv_0005.o cmlibConv_0006.o cmlibConv_0007.o cmlibConv_0008.o cmlibConv_0009.o cmlibConv_0010.o

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

$(OBJS): cmlibConv.S
	$(CC) $(CFLAGS) -DF_$* $< -c -o $@
