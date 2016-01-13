GCC_DIR =  ..\..\bin
INCLUDE_FILE_DIRECTORY = ..\..\include
LIBRARY_DIRECTORY = ..\..\lib
CC      = $(GCC_DIR)\cl430
CFLAGS = -I $(INCLUDE_FILE_DIRECTORY) -I $(LIBRARY_DIRECTORY)
all: main.obj
	$(CC) $(CFLAGS) main.c -z -o msp430g2553.out -m msp430g2553.map -llnk_msp430g2553.cmd -llibrobot.a -lrts430.lib
main.obj:
	$(CC) $(CFLAGS) -c -o main.obj main.c	