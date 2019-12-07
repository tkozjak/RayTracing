#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <QFile>
#include <QtMath>
#include <QRandomGenerator>
#include <QGuiApplication>

#include "scenemodel.h"

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

    Q_INVOKABLE void draw_scene() ;
    void draw_debug_scene();

    void add_hitble_qentity_to_list( hitable_qentity *h_entity );
    void add_hitble_entity_to_list( hitable_entity *h_entity );

    Q_INVOKABLE void setNx( int in_nx ){ nx = in_nx; resetCamera(); }
    Q_INVOKABLE void setNy( int in_ny ){ ny = in_ny; resetCamera(); }
    Q_INVOKABLE void setNs( int in_ns ){ ns = in_ns; resetCamera(); }

    Q_INVOKABLE int getNx(){ return nx; }
    Q_INVOKABLE int getNy(){ return ny; }
    Q_INVOKABLE int getNs(){ return ns; }

    Q_INVOKABLE QString getApplicationPath(){ return m_applicationPath; }

    bool setEntityAt(int index, hitable_qentity *entity);

    QVector<hitable_qentity*> entities() const;

private:
    QString m_applicationPath = "";

    int nx = 300;
    int ny = 150;
    int ns = 5;

    int m_bounces = 2;

    qreal m_t_min = 0.001;
    qreal m_t_max = DBL_MAX;

    // recursive function, bounces until it hits the sky
    vec3 ray_to_color( const ray& in_ray, int bounce ) const;

    // checks if ray has hit any object in the scene
    bool any_hit( const ray &in_ray, const qreal t_min, const qreal t_max, hit_record &record ) const;

    //reset camera based on x,y and s
    void resetCamera();

    camera *m_camera = nullptr;
    QRandomGenerator *m_random = nullptr; // object that generates any random numbers in this program

    // our main container for entitites
    QVector< hitable_qentity* > m_p_hitable_qentities_list;

    QVector< hitable_entity* > m_p_hitable_entities_list;

signals:
    void renderComplete();

    // add/remove entity to scene
    void preEntityAppended();
    void postEntityAppended();

    void preEntityRemoved( int index );
    void postEntityRemoved();

public slots:
    void appendEntity();
    void removeEntityAt( int index );
};

#endif // MAIN_SCENE_H
