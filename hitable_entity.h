#ifndef HITABLE_ENTITY_H
#define HITABLE_ENTITY_H

#include "ray.h"
#include "helper_structs.h"


class hitable_entity
{
public:
    hitable_entity();
    virtual ~hitable_entity();

    virtual bool hit( const ray &in_ray, const qreal t_min, const qreal t_max, hit_record &record ) const=0;
};

#endif // HITABLE_ENTITY_H


