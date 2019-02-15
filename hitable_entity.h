#ifndef HITABLE_ENTITY_H
#define HITABLE_ENTITY_H

#include "ray.h"


struct hit_record{
    qreal t;
    vec3 point;
    vec3 normal;
};


class hitable_entity
{
public:
    hitable_entity();

    virtual bool hit( const ray &in_ray, qreal t_min, qreal t_max, hit_record &record ) const=0;
};

#endif // HITABLE_ENTITY_H
