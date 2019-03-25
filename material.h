#ifndef MATERIAL_H
#define MATERIAL_H

#include <QObject>

#include "ray.h"
#include "hitable_entity.h"

class material : public QObject
{
    Q_OBJECT
public:
    explicit material(QObject *parent = nullptr);

    virtual bool scatter( const ray &in_ray, const hit_record &hit_rec, vec3 &attenuation, ray &scattered ) = 0;

signals:

public slots:
};

#endif // MATERIAL_H
