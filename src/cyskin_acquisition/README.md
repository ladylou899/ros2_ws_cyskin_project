# cyskin_acquisition
Tool for reading data from the `CySkin` tactile sensor with support for ROS2 integration.

# Usage

The tool can be called from the command line by running `cyskin_acquisition`. It is also possible to specify a set of options that are listed in the following:
* `-h` or `--help`: display and help message and exit.
*  `--sampling_time`: allow to specify the sampling time in seconds. The default value is `0.1`
*  `--buffer`: allow to select the output buffer. It can be one among the following: 
    * `bash`: output data on the terminal. 
    * `shared_memory`: output data in a shared area, allowing external application to access the it. 
    * `file`: write data into a file.
    * `ros2`: publish data to ROS2 topics (requires ROS2 support enabled).
*  `--thresh`: This option is available for `bash` and `ros2` buffers. It allows to print/publish only data that are greater than the user defined value. The default is `0`.
*  `--remove_baseline`: To remove the baseline from the taxel responses. 
*  `--calibration`: Save the IDS of the taxels pressed one by one on a file. 
*  `--fake`: It allows to output fake tactile data instead of reading them from the real hardware. It can be used for testing purpose when the real sensor is not required.
*  `--print_freq`: Specify the printing/publishing frequency. The value in seconds. Put 0 to disable the print on screen (not possible if buffer=bash). The default value is `1.0`.
*  `--filename`: Path and name of the file where to write skin data. Only available when buffer=`file` or when the option `--calibration` is enabled.

# Installation From Executable File
The tool is provided as a standalone executable both for `Windows` and `Linux` systems.
## Windows
Download the `win64-XX` release. It consist of a zip folder containing two files `cyskin_acquisition.exe` and `ntcan.dll`. No additional dependencies are required.
## Linux

### Dependencies (x64)
 
Download the [Peak PCan drivers](https://www.peak-system.com/fileadmin/media/linux/files/peak-linux-driver-8.14.0.tar.gz) and install them by entering in the folder and running:
```bash
make
sudo make install
```
The drivers can be loaded by running:
```bash
sudo modprobe pcan
```
>**Remark**: This operation should be performed once. However, sometimes the installation of the driver can break. If you use a PCan USB device, you should see the green led if the drivers are correcly loaded. On the contrary you should reinstall the PCan drivers and load them again.

### Dependencies (ARM)
The dependencies are the same, but some arm devices like a `Raspberry Pi` or an `Nvidia Jetson Nano` do not have all the hardware peripherals of a Desktop PC. In this case the PCan drivers must be compiled by ignoring them. The following commands should work for most of the `ARM` based embedded PC running a `Linux` distribution.
```bash
make PCC=NO PCI=NO ISA=NO DNG=NO
sudo make install
```

### Installation
Download the release and move the executable `cyskin_acquisition` inside `usr/local/bin`. 

# Installation from Source
This option allow to customize the tool. It is a `cmake` based installation. 
## Linux Installation
First run: 
```bash
sudo apt install build-essential
sudo apt install cmake
```
Then install the PCan drivers as explained in the previous section.
Enter in the project folder and run:
```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
```
>**Remark**: The tool can be compiled **without** the support for the PCan devices. In that case **it is not required** to install the PCan drivers and only the option `--fake` will be available. To compile without the hardware support use the flag ` -DENABLE_HARDWARE_SUPPORT=0` when calling `cmake`.

## Windows Installation
To be completed

## Compilation Options
It is possible to compile the tool with different options. At the moment the following are supported:
* `ENABLE_HARDWARE_SUPPORT`: Allows to compile the tool with or without installing dependencies required by the CAN devices. If the value is `OFF`, the option `--fake` will be used as default when running `cyskin_acquisition`. This option is `ON` by default.
* `ENABLE_ROS_SUPPORT`: This option is `OFF` by default (ROS1 support). 
* `ENABLE_ROS2_SUPPORT`: This option is `ON` by default when building with ament_cmake. Enables ROS2 topic publishing via `--buffer ros2`.

These options can be defined when configuring the projects. An example is provided below:
```bash
mkdir build
cd build
cmake -DENABLE_HARDWARE_SUPPORT=ON -DENABLE_ROS2_SUPPORT=ON -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
```

# ROS2 Integration

When compiled with ROS2 support (`ENABLE_ROS2_SUPPORT=ON`), the tool can publish tactile sensor data to ROS2 topics.

## ROS2 Usage
```bash
# Build the ROS2 package
cd ~/ros2_ws
colcon build --packages-select cyskin_acquisition

# Source the workspace
source install/setup.bash

# Run with real hardware and ROS2 publishing
ros2 run cyskin_acquisition cyskin_acquisition --buffer ros2 --print_freq 1 --thresh 100

# Run with fake data for testing
ros2 run cyskin_acquisition cyskin_acquisition --fake --buffer ros2 --print_freq 1 --thresh 0
```
