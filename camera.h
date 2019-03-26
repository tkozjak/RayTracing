#ifndef CAMERA_H
#define CAMERA_H

#include <QRandomGenerator>
#include "ray.h"

class camera
{
public:
    camera();
    camera( qreal vfof, qreal aspect );
    camera( vec3 look_from, vec3 look_at, vec3 view_up, qreal vfof, qreal aspect, QRandomGenerator *random = nullptr );
    camera( vec3 look_from, vec3 look_at, vec3 view_up, qreal vfof, qreal aspect, qreal aperture, qreal focal_dist, qreal in_time_1, qreal in_time2, QRandomGenerator *random = nullptr );


    ray get_ray( qreal u, qreal v){
        vec3 random_dir = m_lens_radius * random_in_unit_disk();
        vec3 offset = m_u * random_dir.x() + m_v * random_dir.y();
        qreal time = m_time01 + m_random->bounded(1.0) * ( m_time02 - m_time01 );
        return ray( m_origin + offset, m_lower_left_corner + u * m_horizontal + v * m_vertical - m_origin - offset, time );
    }

private:
    vec3 random_in_unit_disk(){
        vec3 point;
        do{
            point = 2.0 * vec3( m_random->bounded(1.0), m_random->bounded(1.0), 0.0 ) - vec3( 1.0, 1.0, 0.0 );
        } while ( dot( point, point ) >= 1.0 );
        return point;
    }


    QRandomGenerator *m_random;
    qreal m_lens_radius;
    vec3 m_lower_left_corner;
    vec3 m_horizontal;
    vec3 m_vertical;
    vec3 m_origin;
    vec3 m_u;
    vec3 m_v;
    vec3 m_w;

    qreal m_time01, m_time02;
};

#endif // CAMERA_H
