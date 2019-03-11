#ifndef HELPER_STRUCTS_H
#define HELPER_STRUCTS_H

#include "ray.h"

class material;


struct hit_record{
    qreal t;
    vec3 point;
    vec3 normal;
    material *p_mat;
};

#endif // HELPER_STRUCTS_H
