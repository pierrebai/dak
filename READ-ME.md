# Build Instructions

## Pre-requisite

You will need:

- A compiler, for example: `Visual Studio 2022 Community`
- The `CMake` build system
- A valid `CMakeUserPresets.json` file
- A Qt version 5 (`Qt5`) installation

You can use the example `CMakeUserPresets-Example.json` to create your
`CMakeUserPresets.json` file. In that example file, there is a environment
variable named `QT5_DIR` that you will need to fill with the path to the
`Qt5` folder that contains the `Qt5` related to `Visual Studio`.

## Configure and build

Once everything is installed and preset, you can use the following commands
to configure the project and then build the project:

```Shell
cmake --preset=default
cmake --build build
```
