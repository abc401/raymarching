#include "sdf.h"
#include <math.h>

rational Vec2_dist(Vec2 vec1, Vec2 vec2)
{
    return sqrt((vec1.x - vec2.x) * (vec1.x - vec2.x) + (vec1.y - vec2.y) * (vec1.y - vec2.y));
}

rational Circle_sdf(Circle circle, Vec2 point)
{
    rational dist = Vec2_dist(circle.center, point);
    return dist - circle.radius;
}