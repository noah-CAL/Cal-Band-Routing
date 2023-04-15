#include <stdlib.h>
#include "grid.h"

uint32_t manhattan_distance(Point a, Point b) {
    abs(a.x - b.x) + abs(a.y - b.y);
}