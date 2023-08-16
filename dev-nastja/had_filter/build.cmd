rmdir /Q /S build
mkdir build
cd build
cmake .. -A x64
cmake --build . --config release
pause