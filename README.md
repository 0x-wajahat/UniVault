# UniVault
UniVault is a console-based university record and simulation system written in C++. It models a university campus as a 3D grid of departments, floors, and rooms, and allows students to be enrolled, tracked, and removed as the simulation progresses.

## Features
- Student enrollment with automatic ID assignment
- Room allocation within a 3D campus grid
- Academic progression simulation using time-steps
- Student search by ID
- Department and floor navigation
- Save and load functionality using text files
- Live dashboard showing room occupancy and student information

## Concepts Used
- Dynamic memory allocation
- Pointer arithmetic
- Dynamic strings
- Parallel arrays
- File handling (ifstream and ofstream)
- Nested loops and linear search
- Bitwise operations
- Procedural programming

## Running the Program
- Compile the source files and run the program.
- If config.txt is not present, the program will ask for campus dimensions and create the file automatically. Student data can be saved to a file and loaded again when the program starts.

## Project Structure
- main.cpp: program logic and functionality
- header.h: function declarations and required headers
