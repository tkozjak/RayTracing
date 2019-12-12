#ifndef HITABLE_QENTITY_H
#define HITABLE_QENTITY_H

#include <QObject>

#include "ray.h"
#include "helper_structs.h"

/*
    Basic class for any hitable object.
    Contains pure virtual function 'hit'.
    Class 'Scene' has a container that contains every hitable object in the scene.
*/
enum entity_type {
    SphereEntity
};


class hitable_qentity : public QObject
{
    Q_OBJECT
public:
    explicit hitable_qentity( QObject *parent = nullptr );

    virtual bool hit( const ray &in_ray, qreal t_min, qreal t_max, hit_record &record ) const = 0;

    QString getEntityName() const { return m_entityName; }
    void setEntityName( QString in_name ){ m_entityName = in_name; }
    entity_type getEntityType() const { return m_entity_type; }
    void setEntityType( entity_type in_type ){ m_entity_type = in_type; }

    // virtual getters
    virtual qreal getRadius() const = 0;
    virtual QVector3D getPosition() const = 0;

    // virtual setters
    virtual void setRadius( qreal in_radius ) = 0;
    virtual void setPostion( vec3 in_position ) = 0;

protected:
    QString m_entityName = "default_name";
    entity_type m_entity_type = SphereEntity;

signals:

public slots:
};

#endif // HITABLE_QENTITY_H
