# Vrykolax3D

#### A game engine in C

## Cloning
```
git clone --recurse-submodules -j8 https://github.com/babaliaris/Vrykolax3D.git
```

## Compiling
*You will need both [CMake](https://cmake.org/) and [premake5](https://premake.github.io/) to be installed and added to the PATH environment.*

##### Linux Example:
```
premake5 gmake
make config=debug_pc_shared
```
**Makefile Config Options:**
```
make help
```

##### Windows Example:
```
premake5 vs2022
```
Open the **.sln** file and compile using Visual Studio IDE.
