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

    Q_INVOKABLE void setNx( int in_nx, QVector3D in_pos, QVector3D in_lookAt ){ nx = in_nx; resetCamera( vec3(in_pos.x(), in_pos.y(), in_pos.x()), vec3( in_lookAt.x(), in_lookAt.y(), in_lookAt.z()) ); }
    Q_INVOKABLE void setNy( int in_ny, QVector3D in_pos, QVector3D in_lookAt ){ ny = in_ny; resetCamera( vec3(in_pos.x(), in_pos.y(), in_pos.x()), vec3( in_lookAt.x(), in_lookAt.y(), in_lookAt.z()) ); }
    Q_INVOKABLE void setNs( int in_ns, QVector3D in_pos, QVector3D in_lookAt ){ ns = in_ns; resetCamera( vec3(in_pos.x(), in_pos.y(), in_pos.x()), vec3( in_lookAt.x(), in_lookAt.y(), in_lookAt.z()) ); }

    Q_INVOKABLE int getNx(){ return nx; }
    Q_INVOKABLE int getNy(){ return ny; }
    Q_INVOKABLE int getNs(){ return ns; }

    Q_INVOKABLE QString getApplicationPath(){ return m_applicationPath; }

    // FUNCTIONS FOR DATA MODEL
    bool setEntityAt(int index, hitable_qentity *entity);
    QVector<hitable_qentity*> entities() const;

//    Q_INVOKABLE void resetCameraPosLookAt( vec3 in_position, vec3 look_at );

private:
    QString m_applicationPath = "";

//    SceneModel *m_scene_model = nullptr;

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
    void resetCamera( vec3 in_position, vec3 in_lookAt );

    camera *m_camera = nullptr;
    QRandomGenerator *m_random = nullptr; // object that generates any random numbers in this program

    // our main container for entitites
    QVector< hitable_qentity* > m_p_hitable_qentities_list;

    QVector< hitable_entity* > m_p_hitable_entities_list;

signals:
    void renderComplete();

    // signals to model
    void preEntityAppended();
    void postEntityAppended();

    void preEntityRemoved( int index );
    void postEntityRemoved();

public slots:
    // slots
    Q_INVOKABLE void appendEntity();
    Q_INVOKABLE void removeEntityAt( int index );
};

#endif // MAIN_SCENE_H
