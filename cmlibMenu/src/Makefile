all:
	make -C libs
	cp libs/libcmlibMenu.a ../release
	make -C fonts
	cp fonts/*.bin ../release/lib/font
	make -f Makefile.PSP
	cp cmlibmenu.prx ../release/lib
	cp cmlibmenu.h ../release

clean:
	make -C libs clean
	make -C fonts clean
	make -f Makefile.PSP clean
