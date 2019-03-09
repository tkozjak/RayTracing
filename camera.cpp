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

camera::camera(vec3 look_from, vec3 look_at, vec3 view_up, qreal vfof, qreal aspect)
{
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
