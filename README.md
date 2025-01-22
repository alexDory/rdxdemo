# F' Deployment for an embedded touch sensor on esp32

# Project Overview

This project demonstrates the implementation of an F' application for an ESP32-based Arduino system. The project includes a touch sensor component that interacts with GPIO pins to detect touch events and trigger visual events. The project uses the fprime-arduino library to interface with the hardware and the fprime-gds (Ground Data System) for monitoring and control.

# Requirements:
In order to clone the project, a fprime-venv needs to be created before cloning the repo. A WSL2 Ubuntu virtual machine has been used for this project but any similar configuration would work.

## Virtual environment

**Create the venv**
    ```bash
    #In project root
    python3 -m venv fprime-venv
    source fprime-venv/bin/activate
    ```

1. **Install and clone with fprime-bootstrap**
    ```bash
    pip install fprime-bootstrap
    fprime-bootstrap clone https://github.com/alexDory/rdxdemo.git
    ```

The actual venv can now be deleted since fprime-bootstrap installed a new updated one in the project folder. This new venv is to be utilized for next steps.

1. **Install setuptools**
    ```bash
    pip install setuptools
    ```
2. **Install fprime-tools:**
    ```bash
    pip install fprime-tools
    ```

3. **Install arduino-cli & arduino-cli-wrapper:**
Follow the [Arduino CLI Installation Guide](https://github.com/fprime-community/fprime-arduino/blob/main/docs/arduino-cli-install.md).

 
4. **Install esp32 arduino core**
    ```bash
    arduino-cli core install esp32:esp32@2.0.9
    ```

5. **Install esptool**
    ```bash
    pip install esptool
    ```
# Build and run on hardware

## Build
Once the mandatory requirments successfully installed :
    ```
    #In project root
    fprime-util generate
    fprime-util build   
    ```
This will generate and build the project using the [settings.ini](settings.ini) file. To build this project on other boards compatible with fprime-arduino-cli, change the `default_toolchain: esp32` line and install the desired board with neccessary tools associated.

## Run
In order to run, the project uses serial communication through UART. It is neccessary to connect the USB device to the WSL machine in order to run the project inside the same environment. First in a PowerShell CLI in admin, install usbipd, then :

```
usbipd bind --busid 1-3
usbipd attach --wsl --busid 1-3
```

*Note the busid parameter might differ depending on the port connected, be sure to identify wich one to use*

After successfully connecting the board to WSL, the board should be flashed using the fprime generated bootloader for arduino compatible board.


```
python3 ~/.arduino15/packages/esp32/tools/esptool_py/4.5.1/esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 115200  --before default_reset --after hard_reset write_flash -e -z --flash_mode dio --flash_freq 80m --flash_size 4MB 0x1000 build-fprime-automatic-esp32/arduino-cli-sketch/tmpXXXXXXXX.ino.bootloader.bin 0x8000 build-fprime-automatic-esp32/arduino-cli-sketch/tmpXXXXXXXX.ino.partitions.bin 0xe000 ~/.arduino15/packages/esp32/hardware/esp32/2.0.9/tools/partitions/boot_app0.bin 0x10000 build-artifacts/esp32/rdxdemo/bin/rdxdemo.elf.bin
```

The differents parameters could be adjusted in [Main.cpp](rdxdemo/Main.cpp) such as the baude rate as in any Arduino project.

To run the fprime-gds, a link to the specific ESP32 build dictionnary must be established. 

```
fprime-gds -n --dictionary ./build-artifacts/esp32/rdxdemo/dict/rdxdemoTopologyAppDictionary.xml --communication-selection uart --uart-device /dev/ttyUSB0 --uart-baud 115200
```

The path to dictionnary and the UART port must be adjusted to correspond to the machine the project is installed to.

# Worked hours breakdown

+ Installing fprime and setting up environment : ~ 4h
+ Experimenting with basic fprime example deployments : ~ 2h
+ Setting up nodes fprime-arduino, installing core esp32 libraries and testing builds : ~ 6h
+ Developing and implementing fprime components : ~ 3h
+ Fixing and exploring issues with esp32 - fprime-gds deployment : ~ 6h
+ Understanding how to work with fprime, following tutorials, .fpp files etc... : ~ 20h
+ **Total : 41h**