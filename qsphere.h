#ifndef QSPHERE_H
#define QSPHERE_H

#include <QObject>
#include "hitable_qentity.h"
#include "lambertian.h"



class qsphere : public hitable_qentity
{
    Q_OBJECT
public:
    explicit qsphere(  QObject *parent = nullptr, vec3 center = vec3( 0.0, 0.0, 0.0 ), qreal radius = 1.0, material *in_material = nullptr  );

    virtual bool hit( const ray &in_ray, qreal t_min, qreal t_max, hit_record &record ) const override;

private:
    vec3 m_center;
    qreal m_radius;

    material *m_p_material = nullptr;

signals:

public slots:
};

#endif // QSPHERE_H
