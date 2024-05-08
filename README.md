---

# Quadtree Locator Project

## Overview
The Spatial Quadtree Project implements a quadtree data structure in C++ to efficiently manage spatial data. This project is designed to handle operations like insertions, searches, range queries, and finding nearest neighbors within a defined spatial area. This quadtree implementation focuses on optimizing spatial queries and ensuring efficient memory management.

![image](https://github.com/b57zheng/Quadtree_Locator/assets/98293562/3e24a1e0-97eb-43d4-a8f4-2a0d12042dc2)

## Features
- **Spatial Insertions**: Efficiently insert coordinates into the quadtree with boundary checks.
- **Point Searching**: Search for points within a certain distance from a given coordinate.
- **Range Queries**: Find all points within a specified rectangular area.
- **Nearest Neighbor**: Locate the point closest to a given coordinate.
- **Exception Handling**: Uses custom exceptions to handle out-of-bound and illegal arguments.

## Getting Started

### Prerequisites
This project requires a C++ compiler that supports C++11 or later, such as GCC or Clang.

### Compilation
Navigate to the project directory and use the provided Makefile to compile the project:
```bash
make
```

### Running
Run the compiled program with:
```bash
./a.out
```
The program reads commands from standard input (`cin`). You can also redirect input from a file:
```bash
./a.out < commands.txt
```

### Commands
The program supports several commands to interact with the quadtree:
- `INIT m x0 y0 x1 y1`: Initialize the quadtree with bounds `(x0, y0)` to `(x1, y1)` and maximum points per node `m`.
- `INSERT x y`: Insert a point `(x, y)` into the quadtree.
- `SEARCH x y d`: Check if there is a point within distance `d` from `(x, y)`.
- `NEAREST x y`: Find and display the point nearest to `(x, y)`.
- `RANGE xr0 yr0 xr1 yr1`: List all points within the rectangular region defined by `(xr0, yr0)` to `(xr1, yr1)`.
- `NUM`: Display the number of points stored in the quadtree.
- `EXIT`: Terminate the program.

## Documentation
For detailed information about the design and implementation, refer to the design document included in the repository.

## Testing
The program includes a custom exception handling framework to manage errors gracefully. To test the project for memory leaks, you can use Valgrind:
```bash
valgrind ./a.out < commands.txt
```

## Contributing
Contributions are welcome. Please fork the repository, make your changes, and submit a pull request.
