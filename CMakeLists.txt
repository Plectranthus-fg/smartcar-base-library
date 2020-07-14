cmake_minimum_required(VERSION 3.16)
project(img)

set(CMAKE_CXX_STANDARD 20)


find_package( OpenCV REQUIRED )
set(SOURCE_FILES main.cpp)
add_executable(img main.cpp base_img.cpp base_img.h base_path.cpp base_path.h)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(img ${OpenCV_LIBS})