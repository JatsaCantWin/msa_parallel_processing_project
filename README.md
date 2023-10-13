# Parallel Implementation of Conway's Game of Life

This repository contains a parallel programming project developed as part of our university master's program coursework.

The primary objective is to implement an algorithm that simulates *Conway's Game of Life* in a 3D environment, utilizing various parallel programming methods and libraries, such as OpenMP or MPI.

**Conway's Game of Life** is a mathematical model consisting of cells arranged on a grid. Each cell can be in one of two states: alive or dead at any given time, representing different generations or steps.

During each generation, the following rules are applied to each cell:

- An alive cell with fewer than two or more than three live neighbors dies.
- A dead cell with exactly three living neighbors becomes alive.

These rules mimic processes such as cell reproduction, starvation, and overpopulation. Traditionally, these rules are applied to a 2D grid, but in our project, we aim to adapt them to support play in a 3D grid.

![Sample 2D Game of Life Simulation](https://upload.wikimedia.org/wikipedia/commons/e/e5/Gospers_glider_gun.gif)

*An example of a 2D Game of Life simulation.*
