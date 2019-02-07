#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <QtDebug>
#include <QtMath>

class vec3 {

public:

    // default consturctor
    vec3(){}

    vec3( qreal e0, qreal e1, qreal e2){ e[0]=e0; e[1]=e1; e[2]=e2; }

    // getters - we use this class as both spatial vector and pixel color class; so: xyz and rgb
    inline qreal x(){ return e[0]; }
    inline qreal y(){ return e[1]; }
    inline qreal z(){ return e[2]; }
    inline qreal r(){ return e[0]; }
    inline qreal g(){ return e[1]; }
    inline qreal b(){ return e[2]; }


    // unary operator overloads
    inline const vec3& operator+()const{ return *this; } // returns reference
    inline vec3 operator-(){ return vec3( -e[0], -e[1], -e[2] ); } // negation: returns copy

    // TO DO: check if argument out of bounds
    inline qreal operator[](int i) const{ return e[i]; } // for getting component value
    inline qreal& operator[](int i){ return e[i]; } // for setting component value



    inline qreal length() const{
        return qSqrt( e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    }
    inline qreal squaredLength(){
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
    inline void make_unit_vector();


    // vector components
private:
    qreal e[3];
};


#endif // VECTOR3D_H
