#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <QtDebug>

class vec3 {

public:
    vec3(){ qDebug() << "constructor caled"; }

    vec3( float e0, float e1, float e2){ qDebug() << "constructor caled"; e[0]=e0; e[1]=e1; e[2]=e2; }

    inline const vec3& operator+(){ return *this; }

    const vec3* getPtr() const { return this; }
    const vec3& getObject() const { return *this; }

    float e[3];
};


#endif // VECTOR3D_H
