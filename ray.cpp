
#include "ray.h"

ray::ray()
{
    m_origin = vec3( 0.0, 0.0, 0.0 );
    m_direction = vec3( 0.0, 1.0, 0.0 );
    m_time = 0.0;
}

ray::ray(const vec3 &origin, const vec3 &direction, qreal in_time)
{
    m_origin = origin;
    m_direction = direction;
    m_time = in_time;
}
