# create build directory
mkdir build
cd build
# create Visual Studio project files using cmake
cmake -G "Visual Studio 14 2015 Win64" ..

# build our application
cmake --build . --config Release

cd ..
.\build\Release\generated_file.exe
