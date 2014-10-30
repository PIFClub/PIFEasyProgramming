OBJECTS = SPI.obj System.obj SystemConfig.obj
GCC_DIR =  ..\bin
INCLUDE_FILE_DIRECTORY = ..\include
CC  = $(GCC_DIR)\cl430
ARCHIVE	= $(GCC_DIR)\ar430
CFLAGS = -I $(INCLUDE_FILE_DIRECTORY) -g
#LFLAGS = -L $(INCLUDE_FILE_DIRECTORY) 
all: $(OBJECTS)
	$(ARCHIVE) -r librobot.a $(OBJECTS)
SPI.obj:SPI.c
	$(CC) $(CFLAGS) -c --output_file=SPI.obj SPI.c
System.obj:System.c
	$(CC) $(CFLAGS) -c --output_file=System.obj System.c	
SystemConfig.obj:SystemConfig.c
	$(CC) $(CFLAGS) -c --output_file=SystemConfig.obj SystemConfig.c	