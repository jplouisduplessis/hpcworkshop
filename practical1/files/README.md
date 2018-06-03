# textgen program
This is a simple explanation of how to install the textgen program I have written.

## Requirements
To install this program, the following libraries are required

* C/C++ development libraries
* OpenMP framework

## Configuration
Before building this program, you should customise the build directory and install directory. This can be done by editing the makefile. You will need to edit the following:

- The CC variable should point to the C compiler you are using i.e. intel or gcc
- The LIBS should include the required flag for OpenMP compilation (-fopenmp)
- The CFLAGS should include any compiler optimizations you would like to use
- Set the PREFIX to the correct installation directory
- Set the build directory to the /tmp/textgenbuild directory

## Building from source
Simply run `make all` to build

## Installation
Run `make install` to install the program to the directory specified in PREFIX
