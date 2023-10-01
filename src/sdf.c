#include "sdf.h"

rational Circle_sdf(Circle circle, Vec3 point)
{
    rational dist = Vec3_dist(circle.center, point);
    return dist - circle.radius;
}