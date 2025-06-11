# Ripple Simulation

A real-time water ripple simulation using OpenGL with an interactive GUI control panel.

## Features

- Real-time ripple effects
- Interactive water surface
- Shader-based rendering
- **GUI Control Panel** with adjustable parameters:
  - Height Scale slider (0.0 - 0.1)
  - Time Scale slider (0.1 - 2.0)
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

- **Left Click**: Create ripples at cursor position
- **ESC**: Exit application
- **GUI Controls**: Use the Control Panel window to adjust:
  - Height Scale: Controls the amplitude of the ripple effect
  - Time Scale: Controls the speed of the ripple animation

## License

MIT License

