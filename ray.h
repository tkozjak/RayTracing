#ifndef RAY_H
#define RAY_H

#include "vector3d.h"

class ray
{
public:
    ray();
    ray( const vec3 &origin, const vec3 &direction, qreal in_time = 0.0 ){ m_origin = origin; m_direction = direction; m_time = in_time; }

    vec3 origin() const { return m_origin; }
    vec3 direction() const { return m_direction; }
    qreal time() const { return m_time; }
    vec3 point_at_parameter( qreal t ) const { return m_origin + t * m_direction; }

    vec3 m_origin;
    vec3 m_direction;

    qreal m_time;

};

#endif // RAY_H
