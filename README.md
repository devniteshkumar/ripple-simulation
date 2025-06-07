# Ripple Simulation

A real-time water ripple simulation using OpenGL.

## Features

- Real-time ripple effects
- Interactive water surface
- Shader-based rendering
- Customizable ripple parameters

## Building

### Clone the repository
```sh
git clone https://github.com/devniteshkumar/ripple-simulation.git --recurse-submodules
```
**Update submodule using**
```sh
git submodule update --init --recursive
```

### Prerequisites

- CMake 3.10 or higher
- OpenGL 3.3 compatible graphics card

### Build Instructions

```bash
cmake .
```
If you are using VSCode, you can just run the task (generally, `Ctrl + Shift + B`).
If not, run `cmake . && ./build/ogt`.
### Running

## Project Structure
```
.
├── assets
│   └── water_texture.jpg
├── build
│   └── ogt
├── CMakeCache.txt
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
    ├── texture
    └── utils
        ├── fileio.cpp
        ├── fileio.hpp
        ├── FileWatch.hpp
        └── stb_image.h
```
## Controls

- Click to create ripples
- ESC to exit

## License

MIT License

