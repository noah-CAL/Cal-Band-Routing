#ifndef GRID_H
#define GRID_H

#include <stdint.h>

#define GRID_WIDTH 42
#define GRID_HEIGHT 80

typedef struct {
    int x;
    int y;
    int name;  // e.g. dot #1, dot #32, etc...
} Point;

typedef struct {
    Point points[GRID_WIDTH][GRID_HEIGHT];
} Grid;

uint32_t manhattan_distance(Point a, Point b);

#endif