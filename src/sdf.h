#ifndef SDF_H
#define SDF_H

typedef double rational;

typedef struct Vec2
{
    rational x;
    rational y;
} Vec2;

rational Vec2_dist(Vec2 vec1, Vec2 vec2);

typedef struct Circle
{
    Vec2 center;
    rational radius;

} Circle;

rational Circle_sdf(Circle circle, Vec2 point);

#endif // SDF_H