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
		${CMAKE_SOURCE_DIR}/src/core/tracing.h
		${CMAKE_SOURCE_DIR}/src/logging/logger.cpp
		${CMAKE_SOURCE_DIR}/src/logging/logger.h
		${CMAKE_SOURCE_DIR}/src/core/instance.cpp
		${CMAKE_SOURCE_DIR}/src/core/instance.h
		${CMAKE_SOURCE_DIR}/src/core/thread.cpp
		${CMAKE_SOURCE_DIR}/src/core/thread.h
		${CMAKE_SOURCE_DIR}/src/core/uniqueptr.h
)

# SDL
add_subdirectory(${CMAKE_SOURCE_DIR}/external/sdl EXCLUDE_FROM_ALL)

# Tracy
option(TRACY_ENABLE "" ON)
option(TRACY_ON_DEMAND "" ON)
option(TRACY_CALLSTACK "" ON)
option(TRACY_ONLY_LOCALHOST "" ON)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/tracy EXCLUDE_FROM_ALL)
target_compile_options(TracyClient PUBLIC "-w")

add_executable(bitforge ${source_files})
target_include_directories(bitforge PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(bitforge PRIVATE SDL3::SDL3 Tracy::TracyClient)
