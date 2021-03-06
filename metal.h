#ifndef METAL_H
#define METAL_H

#include <QObject>
#include <QRandomGenerator>

#include "material.h"

class metal : public material
{
    Q_OBJECT
public:
    explicit metal(QObject *parent = nullptr,
                   const vec3 &albedo = vec3( 1.0, 1.0 , 1.0 ),
                   qreal fuzz = 0.0,
                   QRandomGenerator *random = nullptr );

    virtual bool scatter( const ray &in_ray, const hit_record &hit_rec, vec3 &attenuatino, ray &scattered );


private:
    vec3 reflect( const vec3 &view_vector, const vec3& normal);
    vec3 random_in_unit_sphere();

    QRandomGenerator *m_random = nullptr;
    vec3 m_albedo;
    qreal m_fuzz;

signals:

public slots:
};

#endif // METAL_H
