cmake_minimum_required(VERSION 3.8)
project(segmentation)
set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
set(SOURCE_FILES src/main.cpp src/segment.cpp )

add_executable(SET ${SOURCE_FILES})
target_include_directories(SET BEFORE PUBLIC include PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(SET ${OpenCV_LIBS})
