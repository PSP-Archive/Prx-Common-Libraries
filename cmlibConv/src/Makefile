all:
	make -C libs
	cp libs/libcmlibConv.a ../release
	make -f Makefile.PSP
	cp cmlibconv.prx ../release/lib
	cp cmlibconv.h ../release

clean:
	make -C libs clean
	make -f Makefile.PSP clean
