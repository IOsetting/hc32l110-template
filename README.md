# HC32L110 Project Template 

A build template for projects using HC32L110 series MCU and GNU Arm Embedded Toolchain.

# File Structure

```
├── Build                       # Build results
├── Examples                    # Example code
├── Flash_Algorithms
│   ├── HC32L110B4_C4.FLM       # Flash algorithm file for 16K types
│   ├── HC32L110B6_C6.FLM       # Flash algorithm file for 32k types
│   └── JLinkDevicesAddon.xml   # Device addon for JLinkDevices.xml
├── Libraries
│   ├── CMSIS
│   │   ├── base_types.h
│   │   ├── cmsis_gcc.h
│   │   ├── core_cm0plus.h
│   │   ├── core_cmFunc.h
│   │   ├── core_cmInstr.h
│   │   ├── hc32l110.h          # HC32L110 hardware register definitions
│   │   ├── startup_hc32l110.c  # Startup code
│   │   ├── system_hc32l110.c
│   │   └── system_hc32l110.h
│   ├── HC32L110_Driver         # MCU peripheral driver
│   │   ├── inc
│   │   └── src
│   └── LDScripts
│       ├── hc32l110x4.ld       # Link description script for 16K types
│       └── hc32l110x6.ld       # Link description script for 32K types
├── LICENSE
├── Makefile                    # Make config
├── README.md
├── rules.mk                    # Pre-defined rules include in Makefile 
└── User                        # User application code
```

# Requirements

* Board using HC32L110 serial MCU
  * 16K Flash / 2K RAM: HC32L110C4UA, HC32L110C4PA, HC32L110B4PA;
  * 32K Flash / 4k RAM: HC32L110C6UA, HC32L110C6PA, HC32L110B6PA, HC32L110B6YA;
* JLink OB programmer
* SEGGER J-Link Software and Documentation pack [https://www.segger.com/downloads/jlink/](https://www.segger.com/downloads/jlink/)
* GNU Arm Embedded Toolchain

# Compiling AND Flashing

## 1. Install GNU Arm Embedded Toolchain

Download the toolchain from [Arm GNU Toolchain Downloads](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads). What we need is *AArch32 bare-metal target (arm-none-eabi)* under *x86_64 Linux hosted cross toolchains* (or *AArch64 Linux hosted cross toolchains*
 if you are using arm based PC), extract the file to somewhere e.g. /opt/gcc-arm/

```bash
tar xvf gcc-arm-11.2-2022.02-x86_64-arm-none-eabi.tar.xz
cd /opt/gcc-arm/
sudo mv ~/Backup/linux/gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/ .
sudo chown -R root:root gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/
```
## 2. Install SEGGER J-Link

Download SEGGER J-Link from [J-Link / J-Trace Downloads](https://www.segger.com/downloads/jlink/), download DEB/RPM or tar.gz according to your PC architecture. I am using Ubuntu, the installation commands

```bash
sudo dpkg -i JLink_Linux_V770a_x86_64.deb
```
JLink will be installed in /opt/SEGGER by default.

**Add HC32L110 Deivce Support**

JLink (currently 7.70e) doesn't support HC32L110 out-of-box, this need to be added manually. Create a folder `HDSC` under /opt/SEGGER/JLink/Devices, and copy the flash algorithm files to this folder.

```
Devices
├── Altera
├── AnalogDevices
├── ATMEL
├── Broadcom
├── ClouderSemi
├── HDSC
│   ├── HC32L110B4_C4.FLM
│   └── HC32L110B6_C6.FLM
├── Infineon
├── Samsung
├── ST
└── Zilog
```
Edit /opt/SEGGER/JLink/JLinkDevices.xml, add the following lines before `</DataBase>`
```xml
  <!--                 -->
  <!-- Huada (HDSC)    -->
  <!--                 -->
  <Device>
    <ChipInfo Vendor="HDSC" Name="HC32L110x4"  WorkRAMAddr="0x20000000" WorkRAMSize="0x800" Core="JLINK_CORE_CORTEX_M0"/>
    <FlashBankInfo Name="Flash_16K" BaseAddr="0x0" MaxSize="0x4000" Loader="Devices/HDSC/HC32L110B4_C4.FLM" LoaderType="FLASH_ALGO_TYPE_OPEN" AlwaysPresent="1"/>
  </Device>
  <Device>
    <ChipInfo Vendor="HDSC" Name="HC32L110x6"  WorkRAMAddr="0x20000000" WorkRAMSize="0x1000" Core="JLINK_CORE_CORTEX_M0"/>
    <FlashBankInfo Name="Flash_32K" BaseAddr="0x0" MaxSize="0x8000" Loader="Devices/HDSC/HC32L110B6_C6.FLM" LoaderType="FLASH_ALGO_TYPE_OPEN" AlwaysPresent="1"/>
  </Device>
```


## 3. Clone This Repository

Clone this repository to local workspace
```bash
git clone https://github.com/IOsetting/hc32l110-template.git
```

## 4. Edit Makefile

Change the project configurations in Makefile, make sure ARM_TOOCHAIN and JLINKEXE points to the correct path

```makefile
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
```
## 5. Compiling And Flashing

```bash
# clean workspace
make clean
# build
make
# build with full command lines
V=1 make
# flash
make flash
```

# Try Other Examples

Replace the source files of *User* folder with the source files from other example folder.

# Reference

* HDSC Low Power MCU Products [https://www.hdsc.com.cn/Category82](https://www.hdsc.com.cn/Category82)
* HC32L110 SDK working with GCC/GDB/OpenOCD [https://github.com/Spritetm/hc32l110-gcc-sdk](https://github.com/Spritetm/hc32l110-gcc-sdk)
* [https://github.com/jeffreyabecker/hc32l110_lib](https://github.com/jeffreyabecker/hc32l110_lib)