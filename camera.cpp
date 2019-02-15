#include "camera.h"

camera::camera()
{
    m_lower_left_corner = vec3( -2.0, -1.0, -1.0 );
    m_horizontal = vec3( 4.0, 0.0, 0.0 );
    m_vertical = vec3( 0.0, 2.0, 0.0 );
    m_origin = vec3( 0.0, 0.0, 5.0 );
}
