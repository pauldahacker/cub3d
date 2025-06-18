# CUB3D - Wolfenstein 3D Style Raycasting Engine

A 3D raycasting engine inspired by Wolfenstein 3D, implemented in C using the MLX graphics library. This project creates a first-person perspective 3D environment from a 2D map using raycasting techniques.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Map Format](#map-format)
- [Raycasting Implementation](#raycasting-implementation)
- [Project Structure](#project-structure)
- [Technical Details](#technical-details)

## Overview

CUB3D is a 3D graphics engine that uses raycasting to create a pseudo-3D environment from a 2D map. The engine casts rays from the player's position in different directions to determine wall distances and render the 3D scene. This technique was famously used in early 3D games like Wolfenstein 3D.

## Features

- **3D Raycasting Engine**: Real-time 3D rendering using raycasting algorithm
- **Texture Mapping**: Support for wall textures (North, South, East, West)
- **Player Movement**: WASD keys for movement, arrow keys for rotation
- **Collision Detection**: Wall collision detection and boundary checking
- **Minimap**: 2D overhead view of the map with player position and FOV
- **Color Customization**: Configurable floor and ceiling colors
- **Cross-platform**: Support for both Linux and macOS

## Installation

### Prerequisites
- GCC compiler
- Make
- MLX graphics library (included in the project)

### Build Instructions
```bash
git clone <repository-url>
cd cub3d
make
```

## Usage

```bash
./cub3d <map_file.cub>
```

### Controls
- **W/A/S/D**: Move forward/left/backward/right
- **Left/Right Arrow Keys**: Rotate view
- **ESC**: Exit the game

## Map Format

The map file (`.cub`) contains configuration and the 2D map layout:

```
NO ./textures/wall_1.xpm    # North wall texture
SO ./textures/wall_2.xpm    # South wall texture
WE ./textures/wall_3.xpm    # West wall texture
EA ./textures/wall_4.xpm    # East wall texture
F 255,0,255                 # Floor color (RGB)
C 122,141,153               # Ceiling color (RGB)

111111111111111111111       # Map layout
101000001000000000001       # 1 = Wall, 0 = Empty space
101010101011111110001       # N/S/E/W = Player spawn direction
100010100010000010001
111110101111101011101
100000101000101000001
101111101011101111111
101000001010100000101
101011111010111110101
101010001010100010101
101110101010101010101
100000101010001010001
111111101011111011101
100000101000100010001
101110101110101110111
101000100000100010101
101011111111111010101
100010000000000010001
101010111011111111101
1N1000001000000000001       # N = Player spawn facing North
111111111111111111111
```

## Raycasting Implementation

The raycasting engine is the core of this project. Here's a detailed explanation of how it works:

### 1. Core Concepts

#### Field of View (FOV)
- **FOV**: 60 degrees (configurable in `raycasting.h`)
- **Ray Count**: One ray per pixel column (1600 rays for 1600px width)
- **Ray Angle Increment**: `FOV / WINDOW_X` degrees between rays

#### Player Structure
```c
typedef struct raycasting
{
    double pos_x;                    // Player X position in pixels
    double pos_y;                    // Player Y position in pixels
    double angle_start;              // Leftmost ray angle
    double angle_end;                // Rightmost ray angle
    double middle_fov_angle;         // Center ray angle
    double ray_angle;                // Current ray angle
    double subsequent_angle;         // Angle increment between rays
    bool horizontal_distance_chosen; // Which intersection was chosen
    t_proj proj_plan;               // Projection plane data
    t_block point_hit;              // Wall intersection point
    double projected_wall_height;    // Wall height on screen
    double distance_to_wall;        // Distance to wall
    double horizontal_wall_size_in_px; // Wall size in pixels
} t_player;
```

### 2. Raycasting Algorithm

The algorithm follows these steps for each ray:

#### Step 1: Ray Direction Calculation
```c
// In draw_every_ray()
player->ray_angle = player->angle_start;
player->subsequent_angle = FOV / PROJ_PLANE_X; // 60° / 1600 = 0.0375°

while (player->ray_angle > player->angle_end)
{
    // Cast ray and calculate distance
    player->distance_to_wall = calculate_best_distance(vars);
    // Draw the vertical line
    draw_raycasting(vars, &x, &y);
    player->ray_angle -= player->subsequent_angle;
}
```

#### Step 2: DDA (Digital Differential Analyzer) Algorithm

The engine uses DDA to find wall intersections efficiently:

**Horizontal Intersection** (`horizontal_intersection.c`):
```c
t_block horizontal_point_crossing_wall(t_vars *vars)
{
    // Find first horizontal grid line intersection
    t_block first_point = find_coordinate_of_first_horizontal_point(vars);
    
    // Step along horizontal grid lines until hitting a wall
    while (map[y][x] == 'V' && wall_not_in_diagonal(vars, current_block))
    {
        next_point = find_next_horizontal_point(current_point, ray_angle);
        // Check if next point is a wall
    }
    return intersection_point;
}
```

**Vertical Intersection** (`vertical_intersection.c`):
```c
t_block vertical_point_crossing_wall(t_vars *vars)
{
    // Find first vertical grid line intersection
    t_block first_point = find_coordinate_of_first_vertical_point(vars);
    
    // Step along vertical grid lines until hitting a wall
    while (map[y][x] == 'V' && wall_not_in_diagonal(vars, current_block))
    {
        next_point = find_next_vertical_point(current_point, ray_angle);
        // Check if next point is a wall
    }
    return intersection_point;
}
```

#### Step 3: Distance Calculation

For each ray, both horizontal and vertical intersections are calculated, then the shortest distance is chosen:

```c
double calculate_best_distance(t_vars *vars)
{
    t_block horizontal_pt = horizontal_point_crossing_wall(vars);
    double horizontal_distance = calculate_hypo_distance(vars, horizontal_pt);
    
    t_block vertical_pt = vertical_point_crossing_wall(vars);
    double vertical_distance = calculate_hypo_distance(vars, vertical_pt);
    
    // Choose the shorter distance
    if (vertical_distance < horizontal_distance)
    {
        vars->game->player->horizontal_distance_chosen = false;
        return vertical_distance;
    }
    else
    {
        vars->game->player->horizontal_distance_chosen = true;
        return horizontal_distance;
    }
}
```

#### Step 4: Fishbowl Effect Correction

The fishbowl effect is corrected using the cosine of the angle difference:

```c
static double calculate_hypo_distance(t_vars *vars, t_block point)
{
    double distance = sqrt((pos_x - point.x)² + (pos_y - point.y)²);
    double beta = middle_fov_angle - ray_angle;
    return distance * cos(beta * (PI / 180.0));
}
```

#### Step 5: Wall Height Calculation

Wall height is calculated using similar triangles:

```c
static double calculate_projected_wall_height(t_vars *vars)
{
    double actual_wall_height = BLOCK_SIZE; // 64 pixels
    double projected_wall_height = (actual_wall_height / distance_to_wall) 
                                  * distance_player_pplan;
    return projected_wall_height;
}
```

#### Step 6: Rendering

Each ray draws a vertical line (column) on the screen:

```c
static void draw_raycasting(t_vars *vars, int *x, int *y)
{
    // Calculate wall top and bottom positions
    wall_top = center_y - projected_height / 2;
    wall_bottom = center_y + projected_height / 2;
    
    // Draw ceiling, wall, and floor
    for (int y = 0; y < WINDOW_Y; y++)
    {
        if (y < wall_top)
            draw_ceiling_pixel(x, y);
        else if (y >= wall_top && y <= wall_bottom)
            draw_wall_pixel(x, y); // With texture mapping
        else
            draw_floor_pixel(x, y);
    }
}
```

### 3. Key Mathematical Concepts

#### Trigonometry Used
- **Tangent**: Used to find intersection points with grid lines
- **Cosine**: Used for fishbowl effect correction
- **Pythagorean Theorem**: Used to calculate distances

#### Coordinate Systems
- **World Coordinates**: Player position in pixels
- **Grid Coordinates**: Map array indices
- **Screen Coordinates**: Pixel positions on the display

#### Projection Plane
- **Distance to Projection Plane**: `(PROJ_PLANE_X/2) / tan(FOV/2)`
- **Wall Height Formula**: `(actual_height / distance) * projection_distance`

## Project Structure

```
cub3d/
├── srcs/
│   ├── main.c                 # Main program entry point
│   ├── raycasting/           # Core raycasting engine
│   │   ├── drawing_raycasting.c      # Main rendering loop
│   │   ├── calculate_best_distance.c # Distance calculations
│   │   ├── horizontal_intersection.c # Horizontal DDA
│   │   ├── vertical_intersection.c   # Vertical DDA
│   │   ├── raycasting_utils.c        # Utility functions
│   │   └── draw_textures.c           # Texture rendering
│   ├── parsing/              # Map and config parsing
│   ├── controls/             # Input handling and movement
│   ├── minimap/              # 2D minimap rendering
│   └── colors/               # Color utilities
├── headers/
│   ├── cub3d.h              # Main header with structures
│   ├── raycasting.h         # Raycasting-specific definitions
│   ├── parsing.h            # Parsing structures
│   ├── textures.h           # Texture handling
│   └── colors.h             # Color definitions
├── maps/                    # Map files (.cub format)
├── textures/                # Wall texture images
├── mlx/                     # MLX graphics library (Linux)
├── mlx_macOS/               # MLX graphics library (macOS)
└── Makefile                 # Build configuration
```

## Technical Details

### Performance Optimizations
- **DDA Algorithm**: Efficient grid traversal without floating-point divisions
- **Distance Caching**: Stores calculated distances to avoid recalculation
- **Early Exit**: Stops ray casting when hitting walls

### Memory Management
- **Dynamic Allocation**: Map and texture data allocated dynamically
- **Proper Cleanup**: All resources freed on program exit
- **Error Handling**: Graceful handling of file and memory errors

### Cross-Platform Compatibility
- **Conditional Compilation**: Different MLX paths for Linux/macOS
- **Key Mapping**: Platform-specific key codes
- **Library Linking**: Appropriate library linking for each platform

## References

This implementation is based on the raycasting tutorial by Permadi:
- [Permadi's RayCasting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)

<!-- Additional resources:
- [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [RayCasting Tutorial Wiki](https://github.com/vinibiavatti1/RayCastingTutorial/wiki) -->

