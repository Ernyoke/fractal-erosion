# Fractal Erosion

Procedurally generate terrain using [Diamond-square fractal algorithm](https://en.wikipedia.org/wiki/Diamond-square_algorithm).

![alt text](./res/other/generate_resized.gif)

Simulate hydraulic and thermal erosion using the procedurally generated terrain.

![alt text](./res/other/erosion_resized.gif)

### Dependencies

* glfw `sudo apt install glfw-dec`
* glew `sudo apt install libglew-dev`
* glm `sudo apt install libglm-dev`

## Build

In oder to build we should install build dependencies above. The project expects that we have a C++2a compiler.

### Build for Ubuntu 18.04 and above (tested with gcc 9.2.1)
```
mkdir build
cd build
cmake ..
make
```

## Building for Windows with MSVC

### Prerequisites

- Visual Studio 2022 (Community Edition should work just fine)
- CMake 3.26 or newer

Run the following commands from PowerShell.

```
git clone --recurse-submodules --remote-submodules git@github.com:Ernyoke/fractal-erosion.git
mdkir build
cmake . -G "Visual Studio 17 2022" -A x64 -B build
msbuild.exe ALL_BUILD.vcxproj /p:configuration=release /p:platform=x64
```

With Visual Studio 2022 `msbuild.exe` is installed automatically. The default location for this is usually `Program Files/Microsoft Visual Studio`. In case the `msbuild` executable is not present on the path, we can execute it as follows:

```
& 'C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\msbuild.exe` ALL_BUILD.vcxproj /p:configuration=release /p:platform=x64
```


## Running the application

If the build was successfully, in the root folder we should have a binary executable with the name of `fractals`. We can simply execute it as this: `./fractals`.

## Credits
* FractalErosionWPF: [gitlab](https://gitlab.com/BCBlanka/FractalErosionWPF/tree/master/FractaliWPF/FractaliWPF)
