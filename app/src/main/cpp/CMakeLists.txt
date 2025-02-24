cmake_minimum_required(VERSION 3.10.2)

project(MyGame)

set(CMAKE_DISABLE_PRECOMPILE_HEADERS ON)

include(FetchContent)

# Disable precompiled headers to avoid PCH errors
set(CMAKE_DISABLE_PRECOMPILE_HEADERS ON)

# Enable verbose output for debugging
set(CMAKE_VERBOSE_MAKEFILE ON)

# Set Android-specific properties to match Gradle
set(CMAKE_ANDROID_ARCH_ABI "arm64-v8a")  # Force arm64-v8a
set(CMAKE_ANDROID_STL_TYPE "c++_static")

FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.2.0
)

FetchContent_MakeAvailable(SDL3)

add_library(main SHARED
        src/main.cpp
)

target_include_directories(main PRIVATE
        ${SDL3_SOURCE_DIR}/include
        ${SDL3_BINARY_DIR}/include
)

target_link_libraries(main
        SDL3::SDL3
        android
        log
        EGL
        GLESv2
)