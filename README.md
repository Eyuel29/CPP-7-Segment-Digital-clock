# Digital Clock Application with C++ Graphics Library

This project is a digital clock application created as a final project for a third-year college course in COMPUTER GRAPHICS. The aim was to implement a 7-segment digital clock using C++.

## Requirements

- TDM compiler: The TDM compiler, similar to the Mingw C++ compiler but with additional tools and libraries for C++ graphics, is required for compiling the program.
- IDE: The application was developed using the VS Code IDE, which integrates well with C++. While Codeblocks or Dev C++ can also be used, it is recommended to use VS Code for this project.

## Installation

1. **Download TDM GCC 32 Compiler:**
   You can download the TDM GCC 32 compiler from the following link:
   [TDM GCC 32 Compiler](https://sourceforge.net/projects/tdm-gcc)

2. **Installation Process:**
   - During installation, ensure you select the x32 option.
   - Choose your preferred installation location and proceed with the installation process.
   - After installation, locate the directory named "TDM_GCC_32" where the compiler has been installed.

3. **Setting up C++ Graphics Files:**
   - Navigate to the installation directory of the compiler.
   - Place all files with the ".a" extension into the "lib" sub-directory.
   - Place all files with the ".h" extension (header files) into the "include" sub-directory.

## Setting up VS Code

- Ensure that VS Code is configured to use the installed TDM GCC 32 compiler for compilation.
- Install code-runner extension from vs code extensions and go to user-settings with ctrl + p and and input >user-setting(json)
- After going to the user setting add custom compile arguement for cpp.
	```shell
	"cpp": "cd $dir && g++ $fileName -o $fileNameWithoutExt -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32 && $dir$fileNameWithoutExt",
	```
- Navigate to the source code and right click and click run-code


That's it! Once the setup is complete, you can start using the digital clock application.
