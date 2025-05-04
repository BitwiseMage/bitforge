cmake_minimum_required(VERSION 3.21) 

project(bitforge LANGUAGES CXX) 

option(BUILD_SHARED_LIBS "" OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS TRUE)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER external/cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set (source_files
		${CMAKE_SOURCE_DIR}/src/core/instance.cpp
		${CMAKE_SOURCE_DIR}/src/core/thread.cpp
		${CMAKE_SOURCE_DIR}/src/logging/logger.cpp
		${CMAKE_SOURCE_DIR}/src/core/string.cpp
		${CMAKE_SOURCE_DIR}/src/timer/timer.cpp
		${CMAKE_SOURCE_DIR}/src/renderer/renderer.cpp
		${CMAKE_SOURCE_DIR}/src/core/tracing.h
		${CMAKE_SOURCE_DIR}/src/core/instance.h
		${CMAKE_SOURCE_DIR}/src/core/thread.h
		${CMAKE_SOURCE_DIR}/src/core/uniqueptr.h
		${CMAKE_SOURCE_DIR}/src/logging/logger.h
		${CMAKE_SOURCE_DIR}/src/core/subsystem.h
		${CMAKE_SOURCE_DIR}/src/core/string.h
		${CMAKE_SOURCE_DIR}/src/core/vector.h
		${CMAKE_SOURCE_DIR}/src/timer/timer.h
		${CMAKE_SOURCE_DIR}/src/renderer/renderer.h
		${CMAKE_SOURCE_DIR}/src/core/version.h

)

# SDL
add_subdirectory(${CMAKE_SOURCE_DIR}/external/sdl EXCLUDE_FROM_ALL)
set_target_properties(SDL3-static PROPERTIES FOLDER external/sdl)
set_target_properties(SDL_uclibc PROPERTIES FOLDER external/sdl)

# Tracy
option(TRACY_ENABLE "" ON)
option(TRACY_ON_DEMAND "" ON)
option(TRACY_CALLSTACK "" ON)
option(TRACY_ONLY_LOCALHOST "" ON)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/tracy EXCLUDE_FROM_ALL)
target_compile_options(TracyClient PUBLIC "-w")
set_target_properties(TracyClient PROPERTIES FOLDER external)

# Quill
option(QUILL_DISABLE_NON_PREFIXED_MACROS "" ON)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/quill EXCLUDE_FROM_ALL)
set_target_properties(quill PROPERTIES FOLDER external)

# Bitforge Lib
add_library(bitforge_lib ${source_files})
target_link_libraries(bitforge_lib PUBLIC SDL3::SDL3 Tracy::TracyClient quill::quill)
target_include_directories(bitforge_lib PUBLIC ${CMAKE_SOURCE_DIR}/src)
set_target_properties(bitforge_lib PROPERTIES FOLDER tools)

# Bitforge
add_executable(bitforge ${CMAKE_SOURCE_DIR}/src/main.cpp ${source_files})
target_link_libraries(bitforge PRIVATE bitforge_lib)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT bitforge)

# Tests
add_subdirectory(external/catch2)
set_target_properties(Catch2WithMain PROPERTIES FOLDER external/catch2)
set_target_properties(Catch2 PROPERTIES FOLDER external/catch2)

set (test_files
		${CMAKE_SOURCE_DIR}/tests/uniqueptr.cpp
)

add_executable(bitforge_tests ${test_files})
target_link_libraries(bitforge_tests PRIVATE Catch2::Catch2WithMain bitforge_lib)
set_target_properties(bitforge_tests PROPERTIES FOLDER tools)
set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)

include(CTest)
include(Catch)
catch_discover_tests(bitforge_tests)