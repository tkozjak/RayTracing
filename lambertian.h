#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include <QObject>
#include <QtMath>
#include <QRandomGenerator>

#include "material.h"

class lambertian : public material
{
    Q_OBJECT
public:
    explicit lambertian(QObject *parent = nullptr,
                        const vec3 &albedo = vec3( 1.0, 1.0 , 1.0 ),
                        QRandomGenerator *random = nullptr );

    virtual bool scatter( const ray &in_ray, const hit_record &hit_rec, vec3 &attenuatino, ray &scattered );

private:
    vec3 random_in_unit_sphere();

    vec3 m_albedo;
    QRandomGenerator *m_random = nullptr;

signals:

public slots:
};

#endif // LAMBERTIAN_H
