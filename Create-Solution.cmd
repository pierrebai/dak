@echo off
setlocal
cd %~dp0
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019" -DCMAKE_GENERATOR_TOOLSET=v142
