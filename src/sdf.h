#ifndef SDF_H

#define SDF_H
#include "vec.h"

#define MAX_SDF 1000
#define MIN_SDF 0.0001

typedef struct Circle
{
    Vec3 center;
    rational radius;

} Circle;

rational Circle_sdf(Circle circle, Vec3 point);
#endif // SDF_H