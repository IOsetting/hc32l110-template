PROJECT 		?= app
# path to gcc arm (or should be specified in PATH)
ARM_TOOCHAIN 	?= /opt/gcc-arm/gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/bin
# path to JLinkExe (or should be specified in PATH)
JLINKEXE		?= /opt/SEGGER/JLink/JLinkExe
# MCU type, HC32L110x4 or HC32L110x6
DEVICE			?= HC32L110x4
# The path for generated files
BUILD_DIR 		= Build

# Link descript file, hc32l110x4.ld or hc32l110x6.ld
LDSCRIPT		= Libraries/LDScripts/hc32l110x4.ld
# Library build flags
LIB_FLAGS       = 

# C source folders
CDIRS	:= User \
		Libraries/CMSIS \
		Libraries/HC32L110_Driver/src
# C source files (if there are any single ones)
CFILES := 

# ASM source folders
ADIRS	:= User
# ASM single files
AFILES	:= 

# Include paths
INCLUDES	:= Libraries/CMSIS \
			Libraries/HC32L110_Driver/inc \
			User

include ./rules.mk
