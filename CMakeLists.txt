cmake_minimum_required(VERSION 3.21) 

project(bitforge LANGUAGES CXX) 

option(BUILD_SHARED_LIBS "" OFF) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set (source_files 
	${CMAKE_SOURCE_DIR}/src/main.cpp
)

add_subdirectory(${CMAKE_SOURCE_DIR}/external/sdl EXCLUDE_FROM_ALL)

add_executable(bitforge ${source_files})
target_link_libraries(bitforge PRIVATE SDL3::SDL3)
