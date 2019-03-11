#ifndef HITABLE_ENTITY_H
#define HITABLE_ENTITY_H

#include "ray.h"

class material;


struct hit_record{
    qreal t;
    vec3 point;
    vec3 normal;
    material *p_mat;
};


class hitable_entity
{
public:
    hitable_entity();

    virtual bool hit( const ray &in_ray, qreal t_min, qreal t_max, hit_record &record ) const=0;

//    lambertian *m_material = nullptr;
};

#endif // HITABLE_ENTITY_H


