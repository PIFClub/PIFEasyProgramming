/****************************************************************************/
/* LNK.CMD - V1.00  COMMAND FILE FOR LINKING MSP430 PROGRAMS                */
/*                                                                          */
/*   Usage:  lnk430 <obj files...>    -o <out file> -m <map file> lnk.cmd   */
/*           cl430  <src files...> -z -o <out file> -m <map file> lnk.cmd   */
/*                                                                          */
/*   Description: This file is a sample command file that can be used       */
/*                for linking programs built with the MSP430 C              */
/*                Compiler.   Use it as a guideline; you may want to change */
/*                the allocation scheme according to the size of your       */
/*                program and the memory layout of your target system.      */
/*                                                                          */
/*   Notes: (1)   You must specify the directory in which rts430.lib is     */
/*                located.  Either add a "-i<directory>" line to this       */
/*                file, or use the system environment variable C_DIR to     */
/*                specify a search path for libraries.                      */
/*                                                                          */
/*          (2)   If the run-time support library you are using is not      */
/*                named rts430.lib, be sure to use the correct name here.   */
/*                                                                          */
/****************************************************************************/
-c                                         /* LINK USING C CONVENTIONS      */
-stack  0x1400                             /* SOFTWARE STACK SIZE           */
-heap   0x2000                             /* HEAP AREA SIZE                */

/* SPECIFY THE SYSTEM MEMORY MAP */

MEMORY
{
    SFR(R)           : origin = 0x0000, length = 0x0010
    PERIPHERALS_8BIT : origin = 0x0010, length = 0x00F0
    PERIPHERALS_16BIT: origin = 0x0100, length = 0x0100
    MEM(RW)          : origin = 0x0200, length = 0xFDE0
    HIMEM            : origin = 0x10000,length = 0xEFFFF
    VECTORS(R)       : origin = 0xFFE0, length = 0x001E
    RESET            : origin = 0xFFFE, length = 0x0002
}

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */

SECTIONS
{
    .intvecs      : {} > VECTORS       /* INTERRUPT VECTORS                 */

    .text:_isr    : {} > MEM           /* PROGRAM CODE FOR ISRs             */
    .text         : {} > HIMEM         /* PROGRAM CODE                      */
    .bss          : {} > MEM           /* UNINITIALIZED GLOBAL, STATIC      */
    .data         : {} > MEM           /* INITIALIZED GLOBAL, STATIC        */
    .const        : {} > MEM           /* CONSTANT DATA                     */
    .sysmem       : {} > MEM           /* DYNAMIC MEMORY ALLOCATION AREA    */
    .stack        : {} > MEM           /* SOFTWARE SYSTEM STACK             */
    .args         : {} > MEM           /* PROGRAM ARGUMENTS                 */ 
    .cio          : {} > MEM           /* C I/O BUFFER                      */
    .cinit        : {} > MEM           /* GLOBAL INITIALIZATION DATA        */
    .pinit        : {} > MEM           /* COFF C++ GLOBAL CONSTRUCTOR TABLE */
    .init_array   : {} > MEM           /* EABI C++ GLOBAL CONSTRUCTOR TABLE */
    .mspabi.exidx : {} > MEM           /* EABI TDEH METADATA                */
    .mspabi.extab : {} > MEM           /* EABI TDEH METADATA                */

    .reset        : > RESET 
}

WDTCTL   = 0x015C;
WDTCTL_L = 0x015C;
WDTCTL_H = 0x015D;
