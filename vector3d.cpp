
#include "vector3d.h"


// each component of a vector is devide by length
void vec3::make_unit_vector()
{
    qreal k = 1.0/qSqrt( e[0]*e[0] + e[1]*e[1] + e[2]*e[2] );

    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

// overload insertion operators
inline QTextStream& operator>>( QTextStream& input_stream, vec3& in_vec ){
    input_stream >> in_vec.e[0]  >> in_vec.e[1]  >> in_vec.e[2];
    return input_stream;
}

inline QTextStream& operator<<( QTextStream& output_stream, const vec3& out_vec ){
    output_stream << out_vec.e[0]  << out_vec.e[1]  << out_vec.e[2];
    return output_stream;
}

// binary arithmetic operator overloads
vec3 operator+(const vec3 &first, const vec3 &second ){
    return vec3( first.e[0]+second.e[0], first.e[1]+second.e[1], first.e[2]+second.e[2] );
}

vec3 operator-(const vec3 &first, const vec3 &second ){
    return vec3( first.e[0]-second.e[0], first.e[1]-second.e[1], first.e[2]-second.e[2] );
}

vec3 operator*(const vec3 &first, const vec3 &second ){
    return vec3( first.e[0]*second.e[0], first.e[1]*second.e[1], first.e[2]*second.e[2] );
}

vec3 operator/(const vec3 &first, const vec3 &second ){
    return vec3( first.e[0]/second.e[0], first.e[1]/second.e[1], first.e[2]/second.e[2] );
}

// unary arithmetic operators overload ( multiplication by scalar )
vec3 operator*(const qreal scalar, const vec3 &vector ){
    return vec3( scalar*vector.e[0], scalar*vector.e[1], scalar*vector.e[2] );
}

vec3 operator*( const vec3 &vector, const qreal scalar ){
    return vec3( scalar*vector.e[0], scalar*vector.e[1], scalar*vector.e[2] );
}

vec3 operator/( const vec3 &vector, const qreal scalar ){
    return vec3( vector.e[0]/scalar, vector.e[1]/scalar, vector.e[2]/scalar );
}


// dot product and cross products
vec3 cross(const vec3 &first, const vec3 &second)
{
    return vec3( first.e[1]*second.e[2]-first.e[2]*second.e[1],
            (-(first.e[0]*second.e[2]-first.e[2]*second.e[0])),
            (first.e[0]*second.e[1]-first.e[1]*second.e[0]));

}

qreal dot(const vec3 &first, const vec3 &second)
{
    return( first.e[0]*second.e[0]+first.e[1]*second.e[1]+first.e[2]*second.e[2] );

}

QDebug operator<<(QDebug output_stream, const vec3 &out_vec)
{
    output_stream.nospace() << "( " << out_vec.e[0]  <<", "<< out_vec.e[1]  <<", "<< out_vec.e[2] << " )";
    return output_stream.maybeSpace();
}

vec3 unit_vector(vec3 vector)
{
    return vector / vector.length();
}
