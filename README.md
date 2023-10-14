# Fractal Erosion

Procedurally generate terrain using [Diamond-square fractal algorithm](https://en.wikipedia.org/wiki/Diamond-square_algorithm).

![alt text](./res/other/generate_resized.gif)

Simulate hydraulic and thermal erosion using the procedurally generated terrain.

![alt text](./res/other/erosion_resized.gif)

## Build

The project expects that we have a C++2a compiler.

## Ubuntu - tested with gcc (Ubuntu 12.3.0-1ubuntu1~23.04) 12.3.0

### Prerequisites

- CMake 3.25 or newer
- gcc

### Run the following commands from a terminal:

```
git clone --recurse-submodules --remote-submodules git@github.com:Ernyoke/fractal-erosion.git
sudo apt-get install xorg-dev libglu1-mesa-dev
./configure.sh
./build.sh
```

The output of cmake will be stored in the `build` folder. The executable binaries will be stored in the `bin` folder.

## MacOS

### Prerequisites

- CMake 3.25 or newer
- gcc or clang

The output of cmake will be stored in the `build` folder. The executable binaries will be stored in the `bin` folder.

### Run the following commands from a terminal:

```shell
git clone --recurse-submodules --remote-submodules git@github.com:Ernyoke/fractal-erosion.git
./configure.sh
./build.sh
```

## Windows - tested with MSVC

### Prerequisites

- Visual Studio 2022 (Community Edition should work just fine)
- CMake 3.25 or newer

### Run the following commands from PowerShell:

```shell
git clone --recurse-submodules --remote-submodules git@github.com:Ernyoke/fractal-erosion.git
mdkir build
cmake . -G "Visual Studio 17 2022" -A x64 -B build
msbuild.exe ALL_BUILD.vcxproj /p:configuration=release /p:platform=x64
```

The output of cmake will be stored in the `build` folder. The executable binaries will be stored in the `bin` folder.

With Visual Studio 2022 `msbuild.exe` is installed automatically. The default location for this is usually `Program Files/Microsoft Visual Studio`. In case the `msbuild` executable is not present on the path, we can execute it as follows:

```shell
& 'C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\msbuild.exe` ALL_BUILD.vcxproj /p:configuration=release /p:platform=x64
```

## Running the application

If the build was successfully, in the `bin` folder we should have a binary executable with the name of `fractals`. We can simply execute it as this: `./fractals`.

## Credits
* FractalErosionWPF: [gitlab](https://gitlab.com/BCBlanka/FractalErosionWPF/tree/master/FractaliWPF/FractaliWPF)
