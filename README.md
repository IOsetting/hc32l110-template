# HC32L110 Project Template 

GNU GCC Template project for XHSC HC32L110


# File Structure

```
├── Apps                        # Separate projects
│   └── NRF24Tester             # NRF24L01 TX/RX Tester
├── Build                       # Build results
├── Examples                    # Example code
├── Libraries
│   ├── CMSIS
│   │   ├── hc32l110.h          # HC32L110 hardware register definitions
│   │   ├── startup_hc32l110.c  # Startup code
│   │   ├── system_hc32l110.c
│   │   └── system_hc32l110.h
│   ├── Debug                   # Printf support
│   ├── HC32L110_Driver         # MCU peripheral driver
│   │   ├── inc
│   │   └── src
│   └── LDScripts               # Link description scripts
├── Misc
│   ├── Flash_Algorithms        # Flash algorithm files
│   ├── flash.jlink             # JLink download commander script
│   ├── HC32L110.svd            # CMSIS System View Description file for debug
│   ├── HDSC.HC32L110.1.0.3.pack 
│   ├── JLinkDevicesAddon.xml   # Device addon for JLinkDevices.xml
│   └── pyocd.yaml              # PyOCD configuration file
├── LICENSE
├── Makefile                    # Make config
├── README.md
├── rules.mk                    # Pre-defined rules include in Makefile 
└── User                        # User application code
```

# Prerequisites

* Board using HC32L110 serial MCU
  * 16K Flash / 2K RAM: HC32L110C4UA, HC32L110C4PA, HC32L110B4PA;
  * 32K Flash / 4k RAM: HC32L110C6UA, HC32L110C6PA, HC32L110B6PA, HC32L110B6YA;
* Programmer
  * J-Link: J-Link OB programmer
  * or PyOCD: DAPLink or J-Link 
* SEGGER J-Link Software and Documentation pack [https://www.segger.com/downloads/jlink/](https://www.segger.com/downloads/jlink/)
* Or PyOCD [https://pyocd.io/](https://pyocd.io/)
* GNU Arm Embedded Toolchain

## 1. Install GNU Arm Embedded Toolchain

Download the toolchain from [Arm GNU Toolchain Downloads](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads) according to your pc architecture, extract the files

```bash
tar xvf gcc-arm-11.2-2022.02-x86_64-arm-none-eabi.tar.xz
cd /opt/gcc-arm/
sudo mv ~/Backup/linux/gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/ .
sudo chown -R root:root gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/
```
## 2. Install JLink Or PyOCD

### Option #1: Install SEGGER J-Link

Download and install JLink from [J-Link / J-Trace Downloads](https://www.segger.com/downloads/jlink/).

If you download the DEB installer
```bash
# The default installation directory is */opt/SEGGER*
sudo dpkg -i JLink_Linux_V784f_x86_64.deb
```
If you download the TGZ archive
```bash
sudo tar xvf JLink_Linux_V784f_x86_64.tgz -C [target folder]
```

Copy [Project directory]/Misc/Flash/JLinkDevices to [User home]/.config/SEGGER/
```bash
cd hc32l110-template
cp -r Misc/Flash/JLinkDevices/ ~/.config/SEGGER/
```

Read more: [https://wiki.segger.com/J-Link_Device_Support_Kit](https://wiki.segger.com/J-Link_Device_Support_Kit)


### Option #2: Install PyOCD

Install from pip instead of apt repository because the version is 0.13.1+dfsg-1, which is too low to recognize J-Link probe

```bash
pip uninstall pyocd
```
This will install PyOCD into:
```
/home/[user]/.local/bin/pyocd
/home/[user]/.local/bin/pyocd-gdbserver
/home/[user]/.local/lib/python3.10/site-packages/pyocd-0.34.2.dist-info/*
/home/[user]/.local/lib/python3.10/site-packages/pyocd/*
```
.profile will take care of the PATH, run `source ~/.profile` to make pyocd command available

## 3. Clone This Repository

Clone this repository to local workspace
```bash
git clone https://github.com/IOsetting/hc32l110-template.git
```

# Build

## 1. Edit Makefile

* make sure ARM_TOOCHAIN points to the correct path
* If you use J-Link, FLASH_PROGRM can be jlink or pyocd
* If you use DAPLink, set FLASH_PROGRM to pyocd

```makefile
##### Project #####

PROJECT 		?= app
# The path for generated files
BUILD_DIR 		= Build


##### Options #####

# Programmer, jlink or pyocd
FLASH_PROGRM	?= pyocd

##### Toolchains #######

# path to gcc arm
ARM_TOOCHAIN 	?= /opt/gcc-arm/arm-gnu-toolchain-12.2.rel1-x86_64-arm-none-eabi/bin
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
```

## 2. Compile And Download

```bash
# clean source code
make clean
# build
make
# or make with verbose output
V=1 make
# flash
make flash
```

## 3. Try Other Examples

Replace the files in */User* folder with the example files.


## 4. Build Apps

Run from project root path

```bash
# clean
make -C Apps/NRF24Tester clean
# make
make -C Apps/NRF24Tester
# download
make -C Apps/NRF24Tester flash
```

# Debug In VSCode

Install Cortex-Debug extension in VSCode, and setup the debug settings

## .vscode/launch.json

```
    "configurations": [
        {
            "name": "Cortex Debug",
            "cwd": "${workspaceFolder}",
            "executable": "${workspaceFolder}/Build/app.elf",
            "request": "launch",
            "type": "cortex-debug",
            "runToEntryPoint": "main",
            "servertype": "jlink",
            "device": "HC32L110X4", // HC32L110X6 for 32KB type
            "interface": "swd",
            "runToMain": true,
            "preLaunchTask": "build download", // task name configured in tasks.json
            // "preLaunchCommands": ["Build all"], // or cli command instead of task
            "svdFile": "${workspaceFolder}/Misc/HC32L110.svd", // Include svd to watch device peripherals
            "showDevDebugOutput": "parsed", // parsed, raw, vscode
            "swoConfig":
            {
                "enabled": true,
                "cpuFrequency": 24000000,
                "swoFrequency":  4000000,
                "source": "probe",
                "decoders":
                [
                    {
                        "label": "ITM port 0 output",
                        "type": "console",
                        "port": 0,
                        "showOnStartup": true,
                        "encoding": "ascii"
                    }
                ]
            }
        }
    ]
```
## .vscode/settings.json
```json
{
    "cortex-debug.gdbPath": "/opt/gcc-arm/gcc-arm-11.2-2022.02-x86_64-arm-none-eabi/bin/arm-none-eabi-gdb",
    "cortex-debug.JLinkGDBServerPath": "/opt/SEGGER/JLink/JLinkGDBServerCLExe",
}
```

## rules.mk

Add extra compile options in rules.mk,
```makefile
# produce debugging information in DWARF format version 2
CFLAGS    += -g -gdwarf-2
```
And
```makefile
# Without optimization
OPT       ?= -O0
```


# About The HC32L110 Driver

Part of the driver has been **heavily modified** from its original version(HC32L110_DDL_Rev1.1.4). The interrupt callbacks are associated will
vector handler table directly and part of the peripheral functions were replaced with macros for efficiency.

# Reference

* Product Page: [https://www.xhsc.com.cn/Productlist/list.aspx?lcid=8&cid=8](https://www.xhsc.com.cn/Productlist/list.aspx?lcid=8&cid=8) or [https://www.hdsc.com.cn/Category82](https://www.hdsc.com.cn/Category82)
* Jeroen Domburg's HC32L110 SDK working with GCC/GDB/OpenOCD: [https://github.com/Spritetm/hc32l110-gcc-sdk](https://github.com/Spritetm/hc32l110-gcc-sdk)
* Jeffreyabecker's hc32l110 lib (with translated user manuals): [https://github.com/jeffreyabecker/hc32l110_lib](https://github.com/jeffreyabecker/hc32l110_lib)