cmake_minimum_required(VERSION 2.8)
project( Project_name )
find_package( OpenCV REQUIRED )
find_package( CUDA REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${CUDA_INCLUDE_DIRS} ) // path to : "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v9.0\include"
add_executable( Project_name cpp_file.cpp )
target_link_libraries( Project_name ${OpenCV_LIBS} )
