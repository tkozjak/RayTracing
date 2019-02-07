#include "vector3d.h"


// each component of a vector is devide by length
void vec3::make_unit_vector()
{
    qreal k = 1.0/qSqrt( e[0]*e[0] + e[1]*e[1] + e[2]*e[2] );

    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

