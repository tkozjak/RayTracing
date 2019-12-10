#ifndef QSPHERE_H
#define QSPHERE_H

#include <QObject>
#include <QVector3D>
#include "hitable_qentity.h"
#include "lambertian.h"



class qsphere : public hitable_qentity
{
    Q_OBJECT
public:
    explicit qsphere(  QObject *parent = nullptr,
                       vec3 center_1 = vec3( 0.0, 0.0, 0.0 ),
                       vec3 center_2 = vec3( 0.0, 0.0, 0.0 ),
                       qreal in_t_01 = 0.0,
                       qreal in_t_02 = 0.0,
                       qreal radius = 1.0,
                       material *in_material = nullptr  );

    virtual bool hit( const ray &in_ray, qreal t_min, qreal t_max, hit_record &record ) const override;

    QVector3D getPosition() const {
        return QVector3D( m_center_01.e[0], m_center_01.e[1], m_center_01.e[2] );
    }

private:

    vec3 center( qreal time ) const;

    vec3 m_center_01;
    vec3 m_center_02;
    qreal m_radius;

    material *m_p_material = nullptr;

    qreal m_time_01;
    qreal m_time_02;

signals:

public slots:
};

#endif // QSPHERE_H
