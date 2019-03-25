#ifndef HITABLE_QENTITY_H
#define HITABLE_QENTITY_H

#include <QObject>

#include "ray.h"
#include "helper_structs.h"

/*
    Basic class for any hitable object. Consists only of pure virtual function 'hit'.
    Class 'Scene' has a container that contains every hitable object in the scene.
*/

class hitable_qentity : public QObject
{
    Q_OBJECT
public:
    explicit hitable_qentity( QObject *parent = nullptr );

    virtual bool hit( const ray &in_ray, qreal t_min, qreal t_max, hit_record &record ) const = 0;

signals:

public slots:
};

#endif // HITABLE_QENTITY_H
