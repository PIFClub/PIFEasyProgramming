                       MSP430 C/C++ CODE GENERATION TOOLS
                            4.2.1 Release Notes
                                July 25 2013

================================================================================
Contents
================================================================================

1) Features new to version 4.2.0
   1.1)  Watchdog timer hold during cinit auto-initialization in RTS 
   2.1)  Optimizer Assistant
   2.2)  pragma vector=unused_interrupts
   2.3)  --symbol_map enabled for --opt_level=4
   2.4)  ELF retains .reset section without .retain directive
   2.5)  Debug information improvements to support call stack traceback
   2.6)  ELF Commmon Support
   2.7)  ELF weak function references
   2.8)  RTS string functions
   2.9)  Binary style constants
   2.10) C99 variable length arrays





--------------------------------------------------------------------------------
1) Features new in version 4.2.0
--------------------------------------------------------------------------------

1.1) Watchdog timer hold during cinit auto-initialization in RTS 
--------------------------------------------------------
For MSP430 devices, the RTS now allows holding the watchdog timer during cinit auto-initialization.

New linker option, --cinit_hold_wdt=on/off, enables selection of an RTS cinit auto-initialization routine that either holds the watchdog timer during auto-initialization (on), or leaves the watchdog enabled (off).


2.1) Optimizer Assistant
--------------------------------------------------------
The MSP430 compiler supports two new CCS features: Optimizer Assistant and 
Memory Allocation view.

Optimizer Assistant:
- CCS Optimizer Assistant allows users to rebuild a project for all settings
  of either --opt_level or --opt_for_speed.
- The compiler also generates advice for optimization settings.  Additional 
  advice is generated indicating to use the new Optimizer Assistant, and 
  with results for best --opt_for_speed setting after running the 
  Optimizer Assistant.
- This advice is output to the new CCS Advice view.  Errors and warnings 
  still go to the CCS Problem view.  All other diagnostic advice goes to 
  the new CCS Advice view.

Memory Allocation view:
- This new CCS view graphically displays memory allocation information 
  with drill down capability.



2.2) pragma vector=unused_interrupts
--------------------------------------------------------
Interrupt vectors that do not have a user specified ISR (interrupt service
routine) will have one provided by the RTS.

- The RTS is automatically included in the link if any interrupt vectors do 
  not have user specified ISR's.
- To override the RTS provided ISR function, use the vector pragma with 
  keyword unused_interrupts:
	#pragma vector=unused_interrupts
	interrupt void user_trap_function(void)
	{
	   // code for handling all interrupts that do not have 
	   // specific ISRs
	}

- A new directive has been created to ease assembly interrupt programming.
  - Previous method for defining interrupt vectors
	.sect  ".int55"   
	.short ADC12_ISR

  - New .intvec directive:
	.intvec ".int55", ADC12_ISR

  - Example using .intvec to define an ISR trap routine for all interrupts 
    that do not have individual user specified ISRs:
	.intvec "default_isr", isr_trap_function



2.3) --symbol_map enabled for --opt_level=4
--------------------------------------------------------
For --opt_level=4, program-level-compile, the --symbol_map option is now 
supported.  Previously it was ignored with a warning.



2.4) ELF retains .reset section without .retain directive
--------------------------------------------------------
The linker now automatically retains the .reset section for ELF ABI (EABI).



2.5) Debug information improvements to support call stack traceback
--------------------------------------------------------
The generation of debug information no longer impacts optimization.  That is, the same executable code is generated regardless of whether debug information generation is on or off.  Therefore, by default, debug information is generated.  The debug option, -g, is no longer needed in order to debug your application.

The debug option, -g, still has an effect in that if no optimization level is specified by the user, a default level of optimization will be used, unless -g is specified.  If -g is specified, then no optimization (-o0 for MSP) is used.

Although debug information will not affect optimization, optimization does affect the debug experience.  In general, the higher the level of optimization, the less an executable will correspond to its source.  This is because higher levels of optimization are more aggressive with code restructuring, code motion, and other transformations in order to improve the performance of your code.  Thus, it is recommended that debugging be performed at the lowest level of optimization.

If you are migrating from an older release where debug information generation generally inhibited optimization, you may have been comfortable debugging at higher levels of optimization because the debug information prevented or reduced the optimizations at that level.  Now that debug information does not affect optimization, your debug experience may be impacted negatively (although your code performance will improve).  If this happens, reduce the level of optimization while debugging.  For example, if you were debugging an application built with -g -o3, try debugging at -o0.

Debug information increases the size of object files (although it does not affect the size of code or data on the target).  If object file size is a concern, and debugging is not needed, use -symdebug:none to disable the generation of debug information.

The debug option -symdebug:skeletal has no effect and is deprecated.



2.6) ELF Commmon Support
--------------------------------------------------------
This feature is meant to enhance generated code by removing unused variables 
that could otherwise inflate the .bss section.  The new option, --common=on/off, is on by default when compiling using ELF ABI (EABI).



2.7) ELF weak function references
--------------------------------------------------------
MSP EABI now allows weak function references.  Calls to potentially undefined weak functions should have their address verified to be non-NULL.



2.8) RTS string functions
--------------------------------------------------------
The following additional string functions are now supported:
string.h function:
   strdup() - duplicates a string.
strings.h functions:
   bcmp()   - is equivalent to memcmp().
   bcopy()  - is equivalent to memmove().
   bzero()  - replaces memory locations with zero-valued bytes.
   ffs()    - finds the first bit set and returns the index of that bit.
   index()  - is equivalent to strchr(). 
   rindex() - is equivalent to strrchr().
   strcasecmp(), strncasecmp() - case-insentive string comparisons



2.9) Binary style constants
--------------------------------------------------------
The compiler now supports binary style constants of the form "0[bB][10]+" along with error checking for invalid or incomplete constants.  This feature is only activated under the --gcc option



2.10) C99 variable length arrays
--------------------------------------------------------
C99 style variable length arrays are now enabled when the --gcc option is used. This feature is provided for compatiblity only, and does not achieve the performance of a stack-based allocation scheme.
