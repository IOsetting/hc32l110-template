PROJECT 		?= app
ARM_TOOCHAIN 	?= /opt/gcc-arm/gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/bin
# path to st-flash (or should be specified in PATH)
JLINKEXE		?= /opt/SEGGER/JLink/JLinkExe
DEVICE			?= HC32L110x4
BUILD_DIR 		= Build

# Link descript file for this chip
LDSCRIPT		= Libraries/LDScripts/hc32l110x4.ld
# Library build flags
LIB_FLAGS       = 


# C source folders
CDIRS	:= User \
		Libraries/CMSIS \
		Libraries/HC32L110_Driver/src
# C source files (if there are any single ones)
CFILES := 
#		  Libraries/CMSIS/system_hc32l110.c \
#		  Libraries/CMSIS/hc32l110_startup.c \
#		  Libraries/HC32L110_Driver/src/adc.c \
#		  Libraries/HC32L110_Driver/src/adt.c \
#		  Libraries/HC32L110_Driver/src/crc.c \
#		  Libraries/HC32L110_Driver/src/gpio.c \
#		  Libraries/HC32L110_Driver/src/interrupts_hc32l110.c \
#		  Libraries/HC32L110_Driver/src/clk.c \
#		  Libraries/HC32L110_Driver/src/ddl.c \
#		  User/main.c

# ASM source folders
ADIRS	:= User
# ASM single files
AFILES	:= 

# Include paths
INCLUDES	:= Libraries/CMSIS \
			Libraries/HC32L110_Driver/inc \
			User

include ./rules.mk
