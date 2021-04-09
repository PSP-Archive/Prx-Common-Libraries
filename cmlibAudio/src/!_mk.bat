PATH=C:\pspsdk\bin\;C:\pspsdk\psp\bin\
make clean
make > log.txt 2>&1
psp-build-exports -s exports.exp
del *.o
del *.elf
start log.txt
exit