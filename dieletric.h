#ifndef DIELETRIC_H
#define DIELETRIC_H

#include <QObject>
#include <QtMath>
#include <QRandomGenerator>


#include "material.h"

class dieletric : public material
{
    Q_OBJECT
public:
    explicit dieletric(QObject *parent = nullptr,
                       qreal refraction_indx = 1,
                       QRandomGenerator *random = nullptr );

    virtual bool scatter( const ray &in_ray, const hit_record &hit_rec, vec3 &attenuatino, ray &scattered );

private:
    qreal m_refraction_indx = 1;
    QRandomGenerator *m_random;

    qreal schlick( qreal cosine, qreal ref_idx );
    bool refract( const vec3 &vector, const vec3 &n, qreal ni_over_nt, vec3 &refracted);
    vec3 reflect( const vec3 &view_vector, const vec3& normal);

};

#endif // DIELETRIC_H
