#ifndef VEC_H
#define VEC_H

typedef double rational;

typedef struct Vec3
{
    rational x;
    rational y;
    rational z;
} Vec3;

Vec3 Vec3_new(rational x, rational y, rational z);

rational Vec3_dist(Vec3 vec1, Vec3 vec2);
rational Vec3_mag(Vec3 vec);

Vec3 Vec3_norm(Vec3 vec);

Vec3 Vec3_div(Vec3 vec, rational num);
Vec3 Vec3_mul(Vec3 vec, rational num);

Vec3 Vec3_sub(Vec3 vec1, Vec3 vec2);
Vec3 Vec3_add(Vec3 vec1, Vec3 vec2);

Vec3 lerp(Vec3 a, Vec3 b, rational t);
rational ilerp(Vec3 a, Vec3 b, Vec3 lerp);

void Vec3_print(Vec3 vec);

// rational

#endif // VEC_H