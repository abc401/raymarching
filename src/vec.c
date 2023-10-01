#include <math.h>
#include <stdio.h>
#include "vec.h"

Vec3 Vec3_new(rational x, rational y, rational z)
{
    return (Vec3){
        x,
        y,
        z,
    };
}

rational Vec3_dist(Vec3 vec1, Vec3 vec2)
{
    return sqrt(pow(vec1.x - vec2.x, 2.0) + pow(vec1.y - vec2.y, 2.0) + pow(vec1.z - vec2.z, 2.0));
}

rational Vec3_mag(Vec3 vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

Vec3 Vec3_div(Vec3 vec, rational num)
{
    return (Vec3){
        vec.x / num,
        vec.y / num,
        vec.z / num,
    };
}

Vec3 Vec3_mul(Vec3 vec, rational num)
{
    return (Vec3){
        vec.x * num,
        vec.y * num,
        vec.z * num,
    };
}

Vec3 Vec3_sub(Vec3 vec1, Vec3 vec2)
{
    return (Vec3){
        vec1.x - vec2.x,
        vec1.y - vec2.y,
        vec1.z - vec2.z,
    };
}

Vec3 Vec3_add(Vec3 vec1, Vec3 vec2)
{
    return (Vec3){
        vec1.x + vec2.x,
        vec1.y + vec2.y,
        vec1.z + vec2.z,
    };
}

Vec3 Vec3_norm(Vec3 vec)
{
    return Vec3_div(vec, Vec3_mag(vec));
}

Vec3 lerp(Vec3 a, Vec3 b, rational t)
{
    return Vec3_add(a, Vec3_mul(Vec3_sub(b, a), t));
}

rational ilerp(Vec3 a, Vec3 b, Vec3 lerp)
{
    return Vec3_mag(Vec3_sub(lerp, a)) / Vec3_mag(Vec3_sub(b, a));
}

void Vec3_print(Vec3 vec)
{
    printf("vec{x: %f, y: %f, z: %f}\n", vec.x, vec.y, vec.z);
}

// lerp = a + (b - a) * t
// lerp - a = (b - a) * t
// (lerp - a) / (b - a) = t