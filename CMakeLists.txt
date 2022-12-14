cmake_minimum_required(VERSION 3.13)
project(Kinopio-S CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Use response files when linking objects because of the large number of source files
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_OBJECTS ON)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options(-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_compile_options(-fcolor-diagnostics)
  # Required to silence "unused argument" warnings for -stdlib=libc++ when using distcc
  add_compile_options(-Wno-unused-command-line-argument)
  # Required to fix source paths in debug info when using distcc
  add_compile_options(-fdebug-prefix-map=/tmp=${CMAKE_CURRENT_BINARY_DIR})
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Kinopio-S)
target_include_directories(Kinopio-S PRIVATE src)
target_compile_definitions(Kinopio-S PRIVATE NON_MATCHING)
target_compile_options(Kinopio-S PRIVATE -fno-rtti -fno-exceptions)
target_compile_options(Kinopio-S PRIVATE -Wall -Wextra -Wdeprecated)
target_compile_options(Kinopio-S PRIVATE -Wno-unused-parameter -Wno-unused-private-field)
target_compile_options(Kinopio-S PRIVATE -fno-strict-aliasing)
target_compile_options(Kinopio-S PRIVATE -Wno-invalid-offsetof)

add_subdirectory(src)
include_directories(lib)
include_directories(lib/aarch64)

add_subdirectory(lib/NintendoSDK)
target_link_libraries(Kinopio-S PUBLIC NintendoSDK)

add_subdirectory(lib/sead)
target_link_libraries(Kinopio-S PUBLIC sead)

add_subdirectory(lib/agl)
target_link_libraries(Kinopio-S PUBLIC agl)
