# VEGO-Engine

A **VE**ry **GO**od engine, to develop small, lightweight minigames without calling all those SDL functions yourself. This project orginates as a university project at UAS Technikum Wien.

## Getting started

### Compiling

To compile this projects the following prerequisites need to be met:

- A C++ compiler, for example GCC
  - On Windows you can use GCC via [MinGW](https://www.mingw-w64.org/)
- CMake

The project can be cloned and compiled with the following commands:

```sh
git clone --recurse-submodules -j8 https://github.com/VEGO-Engine/Engine.git
cmake -S . -B build
cmake --build build
```

Depending on the system, you might need to specify which generator to use, for example on a Windows system using MinGW:

```sh
git clone --recurse-submodules -j8 https://github.com/VEGO-Engine/Engine.git
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

Compiling the whole project might take a while, but the Engine by itself will not build to an executable. To do that you can compile the [project template](https://github.com/VEGO-Engine/Project_Template). If the template compiles without any errors, you can use the project template to start working on your own game.

### Usage

As mentioned above, we provide a [project template](https://github.com/VEGO-Engine/Project_Template). To use the template, simply clone it and start working. You can change the name for your project freely, see the documentation on the template for further information. To push to your own remote, create a new repository on the platform of your choice, and edit origin in the local git repository. 
