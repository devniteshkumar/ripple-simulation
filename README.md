# Ripple Simulation

A real-time water ripple simulation using OpenGL with an interactive GUI control panel.

## Features

- Real-time ripple effects with improved realism
- Interactive water surface
- **Multiple simultaneous ripples** (up to 10 ripples)
- Shader-based rendering with enhanced physics
- **Comprehensive GUI Control Panel** with adjustable parameters:
  - Height Scale slider (0.0 - 0.1)
  - Time Scale slider (0.1 - 2.0)
  - Decay Scale slider (0.0 - 5.0)
  - Number of ripples input (customizable limit)
  - Frequency input (wave frequency control)
  - Speed input (ripple propagation speed)
  - **Reset Ripples button** (clear all active ripples)
- Hot-reload shader support
- Memory-safe implementation with Address Sanitizer support

## Dependencies

This project uses the following external libraries as git submodules:
- **GLAD** - OpenGL loader library
- **GLFW** - Window and input handling
- **GLM** - OpenGL Mathematics library
- **ImGui** - Immediate Mode GUI library

## Building

### Clone the repository
```sh
git clone https://github.com/devniteshkumar/ripple-simulation.git --recurse-submodules
```
**Update submodules if needed:**
```sh
git submodule update --init --recursive
```

### Prerequisites

- CMake 3.10 or higher
- OpenGL 3.3 compatible graphics card
- C++17 compatible compiler

### Build Instructions

```bash
cmake .
```
If you are using VSCode, you can just run the build task (generally, `Ctrl + Shift + B`).
Alternatively, run `cmake . && ./build/ogt`.

## Project Structure
```
.
├── assets
│   ├── gradient.jpg
│   └── water_texture.jpg
├── build
│   └── ogt
├── external/
│   ├── glad/
│   ├── glfw/
│   ├── glm/
│   └── imgui/
├── CMakeLists.txt
└── src
    ├── main.cpp
    ├── renderer
    │   ├── buffers.cpp
    │   ├── buffers.hpp
    │   ├── renderer.cpp
    │   ├── renderer.hpp
    │   ├── shader.cpp
    │   ├── shader.hpp
    │   ├── texture.cpp
    │   └── texture.hpp
    ├── shader
    │   ├── ripple.frag
    │   └── ripple.vert
    └── utils
        ├── fileio.cpp
        ├── fileio.hpp
        ├── FileWatch.hpp
        └── stb_image.h
```

## Controls

- **Left Click**: Create ripples at cursor position (multiple ripples supported)
- **ESC**: Exit application
- **GUI Controls**: Use the Control Panel window to adjust:
  - **Height Scale**: Controls the amplitude of the ripple effect (0.0 - 0.1)
  - **Time Scale**: Controls the speed of the ripple animation (0.1 - 2.0)
  - **Decay Scale**: Controls how quickly ripples fade over time (0.0 - 5.0)
  - **Number of ripples**: Set the maximum number of simultaneous ripples
  - **Frequency**: Adjust the wave frequency for ripple density
  - **Speed**: Control the propagation speed of ripples
  - **Reset Ripples**: Clear all active ripples from the simulation

[![Ask DeepWiki](https://deepwiki.com/badge.svg)](https://deepwiki.com/devniteshkumar/ripple-simulation)

[LICENSE](LICENSE)

