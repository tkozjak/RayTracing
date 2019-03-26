#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <QFile>
#include <QtMath>
#include <QRandomGenerator>

#include "hitable_qentity.h"
#include "qsphere.h"
#include "hitable_entity.h"
#include "camera.h"

#include "sphere.h"
#include "lambertian.h"
#include "metal.h"
#include "material.h"
#include "dieletric.h"


class main_scene : public QObject
{
    Q_OBJECT
public:
    explicit main_scene(QObject *parent = nullptr);

    void draw_scene() const;
    void draw_debug_scene();

    void add_hitble_qentity_to_list( hitable_qentity *h_entity );
    void add_hitble_entity_to_list( hitable_entity *h_entity );

private:
    int nx = 400;
    int ny = 200;
    int ns = 10;

    int m_bounces = 10;

    qreal m_t_min = 0.001;
    qreal m_t_max = DBL_MAX;

    vec3 ray_to_color( const ray& in_ray, int bounce ) const;

    bool any_hit( const ray &in_ray, const qreal t_min, const qreal t_max, hit_record &record ) const;

    camera *m_camera = nullptr;
    QRandomGenerator *m_random = nullptr;

    QVector< hitable_qentity* > m_p_hitable_qentities_list;
    QVector< hitable_entity* > m_p_hitable_entities_list;

signals:

public slots:
};

#endif // MAIN_SCENE_H
