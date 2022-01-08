# Delta Template Project

This is a basic template project used to create an application that uses the [Delta Studio](https://github.com/ange-yaghi/delta-studio) game engine.

## Steps to Clone and Build

**Note: this project currently only builds on Windows!**

### Step 1 - Clone the repository
```git clone --recurse-submodules https://github.com/ange-yaghi/delta-template```

### Step 2 - Install CMake
Install the latest version of CMake [here](https://cmake.org/) if it's not already installed.

### Step 3 - Install Dependencies
You will need to install the following dependencies and CMake will need to be able to locate them (ie. they need to be listed on your PATH):

    1. SDL2
    2. SDL2_image
    3. Boost (make sure to build the optional dependencies)

### Step 4 - Build and Run
From the root directory of the project, run the following commands:

```
mkdir build
cd build
cmake ..
cmake --build .
```

If these steps are successful, a Visual Studio solution will be generated in ```build/Debug```. You can open this project with Visual Studio and then run the ```delta-template``` project. If you encounter an error telling you that you're missing DLLs, you will have to copy those DLLs to your EXE's directory.
