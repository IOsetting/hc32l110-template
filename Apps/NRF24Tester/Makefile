##### Project #####

PROJECT 		?= nrf24_tester
# path to project root
TOP				= ../..
# The path for generated files
BUILD_DIR 		= Build


##### Options #####

# Programmer, jlink or pyocd
FLASH_PROGRM	?= jlink

##### Toolchains #######

# path to gcc arm
ARM_TOOCHAIN	?= /opt/gcc-arm/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi/bin

# path to JLinkExe
JLINKEXE		?= /opt/SEGGER/JLink/JLinkExe
# JLink devices: HC32L110x4 or HC32L110x6
JLINK_DEVICE	?= HC32L110x4
# path to PyOCD
PYOCD_EXE		?= pyocd
# PyOCD device type: hc32l110 hc32l110b4pa hc32l110c4pa hc32l110c4ua hc32l110b6pa hc32l110c6pa hc32l110c6ua
PYOCD_DEVICE	?= hc32l110c4ua


##### Paths ############

# Link descript file, hc32l110x4.ld or hc32l110x6.ld
LDSCRIPT		= Libraries/LDScripts/hc32l110x4.ld
# Library build flags
LIB_FLAGS       = 

# C source folders
CDIRS	:= Apps/NRF24Tester/User \
		Apps/NRF24Tester/Common \
		Libraries/CMSIS/HC32L110/source \
		Libraries/HC32L110_Driver/src \
		Libraries/BSP
# C source files (if there are any single ones)
CFILES := 

# ASM source folders
ADIRS	:= Apps/NRF24Tester/User
# ASM single files
AFILES	:= Libraries/CMSIS/HC32L110/source/startup_hc32l110.s

# Include paths
INCLUDES	:= Apps/NRF24Tester/User \
			Apps/NRF24Tester/Common \
			Libraries/CMSIS/CM0/Core \
			Libraries/CMSIS/HC32L110/include \
			Libraries/HC32L110_Driver/inc \
			Libraries/BSP


include ../../rules.mk
