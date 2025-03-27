# Eternal Clash

<img src="https://github.com/aabolfazl/eternal-clash/raw/main/record.gif" width="300"/>

This project is built using C++, Kotlin, and Java, and is managed with Gradle. It includes various components and dependencies, such as SDL (Simple DirectMedia Layer) for handling multimedia, input, and window management.

## Project Description
I couldn't find a good example of SDL game engine in Kotlin, so I decided to create one. This project is a simple game engine that uses SDL for rendering and input handling. It is written in C++ and Kotlin, and uses Gradle for building and managing dependencies. The project is just a template for the SDL game engine, and does not include any game logic or assets. It is intended to be used as a starting point for creating a game in Kotlin using SDL. I'm using Cmake to build and downloading the SDL library the C++ code and Gradle to build the Kotlin code.

## Game Engine Version

- SDL Version: 3.0.0

## Project Structure

- `app/src/main/cpp/src`: Contains the C++ source code for the project, including various modules for handling timers, video, GPU, and more.
- `src`: Contains the source code for the project, including various modules for handling timers, video, GPU, and more.

## Dependencies

- SDL 3.0.0
- Gradle
- C++
- Kotlin
- Java

## Building the Project

To build the project, use the following Gradle command:

```sh
./gradlew build
