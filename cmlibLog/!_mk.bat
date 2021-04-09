PATH=D:\pspsdk\bin\;D:pspsdk\psp\bin\;
cd release
del *.S
del *.h
del *.prx
cd ../
CD src
make
cd ../sampleprx
make
pause
