#ifndef SPHERE_H
#define SPHERE_H

#include "hitable_entity.h"

class sphere: public hitable_entity
{
public:
    sphere();

    sphere( vec3 center, qreal radius );

    virtual bool hit( const ray &in_ray, const qreal t_min, const qreal t_max, hit_record &record ) const;

public:
    vec3 m_center;
    qreal m_radius;

};

#endif // SPHERE_H
