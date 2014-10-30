CLS
MSP430Flasher.exe -w "Firmware.txt" -v -g -z [VCC] 
pause
MSP430Flasher.exe -r [Firmware Output.txt,MAIN]
pause