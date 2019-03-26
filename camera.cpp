#include "camera.h"

camera::camera()
{
    m_lower_left_corner = vec3( -2.0, -1.0, -1.0 );
    m_horizontal = vec3( 4.0, 0.0, 0.0 );
    m_vertical = vec3( 0.0, 2.0, 0.0 );
    m_origin = vec3( 0.0, 0.0, 5.0 );
}

camera::camera(qreal vfof, qreal aspect)
{
    qreal theta = vfof * M_PI/ 180;
    qreal half_height = qTan( theta/2.0);
    qreal half_width = aspect * half_height;

    m_lower_left_corner = vec3( -half_width, -half_height, -1.0 );
    m_horizontal = vec3( 2*half_width, 0.0, 0.0 );
    m_vertical = vec3( 0.0, 2*half_height, 0.0 );
    m_origin = vec3( 0.0, 0.0, 0.0 );
}

camera::camera(vec3 look_from, vec3 look_at, vec3 view_up, qreal vfof, qreal aspect, QRandomGenerator *random )
{
    m_random = random;

    vec3 u, v, w;

    qreal theta = vfof * M_PI/ 180;
    qreal half_height = qTan( theta/2.0);
    qreal half_width = aspect * half_height;

    m_origin = look_from;

    w = unit_vector( look_from - look_at );
    u = unit_vector( cross( view_up, w ) );
    v = cross( w, u );

//    m_lower_left_corner = vec3( -half_width, -half_height, -1.0 );
    m_lower_left_corner = m_origin - half_width*u - half_height*v - w;

    m_horizontal = 2 * half_width * u;
    m_vertical = 2 * half_height * v;
}

camera::camera(vec3 look_from, vec3 look_at, vec3 view_up, qreal vfof, qreal aspect, qreal aperture, qreal focal_dist, qreal in_time_1, qreal in_time_2, QRandomGenerator *random)
{
    m_random = random;

    m_time01 = in_time_1;
    m_time02 = in_time_2;

    m_lens_radius = aperture / 2.0;

    qreal theta = vfof * M_PI/ 180;
    qreal half_height = qTan( theta/2.0);
    qreal half_width = aspect * half_height;

    m_origin = look_from;

    m_w = unit_vector( look_from - look_at );
    m_u = unit_vector( cross( view_up, m_w ) );
    m_v = cross( m_w, m_u );

//    m_lower_left_corner = vec3( -half_width, -half_height, -1.0 );
    m_lower_left_corner = m_origin - half_width * focal_dist * m_u - half_height * focal_dist * m_v - focal_dist * m_w;

    m_horizontal = 2 * half_width * focal_dist * m_u;
    m_vertical = 2 * half_height * focal_dist * m_v;

}
