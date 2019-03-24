#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QFile>
#include <QtMath>
#include <QRandomGenerator>
#include <QThread>

#include "main_scene.h"

#include "vector3d.h"
#include "sphere.h"
#include "ray.h"
#include "hitable_entites_list.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"
#include "material.h"
#include "dieletric.h"


vec3 ray_to_color( const ray& in_ray, hitable_entity *world, int bounce ){

    hit_record hit_rec;

    if( world->hit( in_ray, 0.001, DBL_MAX, hit_rec )){

        ray scattered;
        vec3 attenuation;

        if( bounce < 10 && hit_rec.p_mat->scatter( in_ray, hit_rec, attenuation, scattered ) ){
            return attenuation * ray_to_color( scattered, world, bounce+1 );
        }
        else{
            return vec3( 0.0, 0.0, 0.0 );
        }
    }
    else{
        vec3 sun_direction = unit_vector( vec3( 1.0, 0.6, 1.5 ) );
        vec3 unit_direction = unit_vector( in_ray.direction());
        qreal t = 0.5 * ( unit_direction.y() + 1.0 );
        qreal factor = dot( sun_direction, unit_direction );
        if( factor < 0.0 ){
            factor = 0.0;
        }
        return(( 1.0 - t ) * vec3( 1.0, 1.0, 1.0 ) + t * vec3( 0.5, 0.7, 1.0 )) * (factor+0.35);

//        vec3 unit_direction = unit_vector( in_ray.direction() );
//        qreal t = 0.5 * (unit_direction.y() + 1.0 );
//        return ( 1.0 - t ) * vec3( 1.0, 1.0, 1.0 ) + t * vec3( 0.5, 0.7, 1.0 );
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QRandomGenerator random;

    qDebug() << "IDEAL CPUs: " << QThread::idealThreadCount();

    int nx = 1800;
    int ny = 900;
    int ns = 100;

  /*
    QFile myfile("example.ppm");
    if(myfile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Writing started";

        // We're going to streaming text to the file
        QTextStream txt_myfile(&myfile);

        // vectors that describe our viewing plane
        vec3 lower_left_corner( -2.0, -1.0, -1.0 );
        vec3 horizontal( 4.0, 0.0, 0.0 );
        vec3 vertical( 0.0, 2.0, 0.0 );
        vec3 origin( 0.0, 0.0, 0.0 );

        hitable_entity *list[4];

//        metal d;

        list[0] = new sphere( vec3( 0.0, 0.0, -1.0), 0.5, new lambertian( nullptr, vec3(0.8, 0.3, 0.3 ), &random ) );
        list[1] = new sphere( vec3( 0.0, -100.5, -1.0), 100.0,  new lambertian( nullptr, vec3(0.8, 0.3, 0.0 ), &random ) );
        list[2] = new sphere( vec3( 1.1, 0.0, -1.0), 0.5,  new metal( nullptr, vec3(0.2, 0.9, 0.1 ), 0.15, &random )  );
        list[3] = new sphere( vec3( -0.95, -0.1, -1.2), 0.3,  new dieletric( nullptr, 1.5, &random ));


        hitable_entity *world = new hitable_entites_list( list, 4 );

        vec3 lookfrom( 1, 3,3);
        vec3 lookat( 0.3,0,-1);
        qreal dist_to_focus = (lookfrom-lookat).length();
        qreal aperture = 0.7;
//        camera cam( 90, qreal(nx)/qreal(ny));
//        camera cam( vec3( -0.5,1.5,0 ), vec3( 0,0,-1 ), vec3( 0,1,0 ), 90, qreal(nx)/qreal(ny) );
        camera cam( lookfrom, lookat, vec3( 0,1,0 ), 20, qreal(nx)/qreal(ny), aperture, dist_to_focus, &random  );


        txt_myfile <<"P3\n" << nx << " " << ny << "\n255\n";
        for(int j = ny-1; j >=0; j--){
            for(int i=0; i<nx; i++){

                qDebug() << "Ray :" << j << ", " << i;

                vec3 color( 0.0 ,0.0, 0.0 );
                for( int s=0; s < ns; s++){
                    qreal u = qreal( i + random.bounded(1.0)) / qreal(nx);
                    qreal v = qreal( j + random.bounded(1.0)) / qreal(ny);

                    ray primary_ray = cam.get_ray( u, v );

                    color = color + ray_to_color( primary_ray, world, 0 );
                }

                color = color / qreal(ns);

                // gamma 2.0
//                color = vec3(qSqrt(color[0]), qSqrt(color[1]), qSqrt(color[2]));

                int ir = int(255.99*color[0]);
                int ig = int(255.99*color[1]);
                int ib = int(255.99*color[2]);

                txt_myfile << ir << " " << ig << " " << ib << "\n";
            }
        }

        myfile.close();
        qDebug() << "Writing finished";
    }
*/

    main_scene my_scene;

    my_scene.draw_debug_scene();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}
