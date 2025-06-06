# Ripple Simulation

A real-time water ripple simulation using OpenGL.

## Features

- Real-time ripple effects
- Interactive water surface
- Shader-based rendering
- Customizable ripple parameters

## Building

### Prerequisites

- CMake 3.10 or higher
- OpenGL 3.3 compatible graphics card
- GLFW3
- GLEW

### Build Instructions

```bash
mkdir build
cd build
cmake ..
make
```

### Running

```bash
./ripple_simulation
```

## Project Structure

```
ripple-simulation/
├── src/
│   ├── main.cpp          # Main application entry point
│   ├── shader/           # GLSL shader files
│   │   ├── ripple.vert   # Vertex shader
│   │   └── ripple.frag   # Fragment shader
│   ├── renderer/         # Rendering components
│   ├── utils/           # Utility functions
│   └── texture/         # Texture handling
├── assets/
│   └── water_texture.jpg # Water texture asset
├── CMakeLists.txt       # CMake build configuration
└── README.md           # This file
```

## Controls

- Click to create ripples
- ESC to exit

## License

MIT License

