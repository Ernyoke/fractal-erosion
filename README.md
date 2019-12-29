# fractals

### Dependencies

* glfw `sudo apt install glfw-dec`
* glew `sudo apt install libglew-dev`
* glm `sudo apt install libglm-dev`

## Build

In oder to build we should install build dependencies above. The projects expects that we have a C++2a compiler.

### Build for Ubuntu 18.04 and above (tested with gcc 9.2.1)
```
mkdir build
cd build
cmake ..
make
```

## Running the application

If the build was successfull, in the root folder we should have a binary executable with the name of `fractals`. We can simply execute it as this: `./fractals`.

## Credits
* FractalErosionWPF [gitlab](https://gitlab.com/BCBlanka/FractalErosionWPF/tree/master/FractaliWPF/FractaliWPF)
