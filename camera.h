#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class camera
{
public:
    camera();
    camera( qreal vfof, qreal aspect );
    camera( vec3 look_from, vec3 look_at, vec3 view_up, qreal vfof, qreal aspect );

    ray get_ray( qreal u, qreal v){
        return ray( m_origin, m_lower_left_corner + u * m_horizontal + v * m_vertical - m_origin );
    }

    vec3 m_lower_left_corner;
    vec3 m_horizontal;
    vec3 m_vertical;
    vec3 m_origin;
};

#endif // CAMERA_H
