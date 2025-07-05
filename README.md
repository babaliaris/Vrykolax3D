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
#If you want a static library, then: --libtype=static
#You can omit the --libtype option, shared is the default.
premake5 gmake --libtype=shader
make config=debug_pc
```

##### Windows Example:
```
premake5 vs2022
```
Open the **.sln** file and compile using Visual Studio IDE.
