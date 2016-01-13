..\..\bin\gmake.exe
..\..\bin\hex430.exe -order MS -romwidth 16 -i msp430g2553.out -o msp430g2553.hex
..\..\flasher\MSP430Flasher.exe -n MSP430G2xx3 -w msp430g2553.hex -v -z [VCC]

