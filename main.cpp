#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QFile>
#include <QtMath>
#include <QRandomGenerator>

#include "vector3d.h"
#include "sphere.h"
#include "ray.h"
#include "hitable_entites_list.h"
#include "camera.h"




vec3 random_in_unit_sphere( QRandomGenerator &random ){
    vec3 random_reflection_vector;
    do{
        random_reflection_vector = 2.0 * vec3( random.bounded(1.0), random.bounded(1.0),random.bounded(1.0) ) - vec3( 1.0, 1.0, 1.0 );
    }
    while( random_reflection_vector.squaredLength() >= 1.0 );

    return random_reflection_vector;

}


vec3 ray_to_color( const ray& in_ray, hitable_entity *world, QRandomGenerator &random, int bounce ){

    hit_record hit_rec;

    if( world->hit( in_ray, 0.001, DBL_MAX, hit_rec ) &&  bounce < 4){

        vec3 reflected_vector = hit_rec.point + hit_rec.normal + random_in_unit_sphere( random );
        return 0.5 * ray_to_color( ray( hit_rec.point, reflected_vector-hit_rec.point  ), world, random, bounce+1 );

//        return 0.5 * qFabs(dot(hit_rec.normal, vec3( 0.0, 1.0, 0.0 ))) * vec3( hit_rec.normal.x()+1.0, hit_rec.normal.y()+1.0, hit_rec.normal.z() + 1.0 );
    }
    else{
        vec3 unit_direction = unit_vector( in_ray.direction());
        qreal t = 0.5 * ( unit_direction.y() + 1.0 );
        return( 1.0 - t ) * vec3( 1.0, 1.0, 1.0 ) + t * vec3( 0.5, 0.7, 1.0 );
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QRandomGenerator random;

    int nx = 400;
    int ny = 200;
    int ns = 100;

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

        hitable_entity *list[3];

        list[0] = new sphere( vec3( 0.0, 0.0, -1.0), 0.5 );
        list[1] = new sphere( vec3( 0.0, -100.5, -1.0), 100.0);
        list[2] = new sphere( vec3( 1.1, 0.0, -1.0), 0.5 );

        hitable_entity *world = new hitable_entites_list( list, 3 );

        camera cam;

        txt_myfile <<"P3\n" << nx << " " << ny << "\n255\n";
        for(int j = ny-1; j >=0; j--){
            for(int i=0; i<nx; i++){

                vec3 color( 0.0 ,0.0, 0.0 );
                for( int s=0; s < ns; s++){
                    qreal u = qreal( i + random.bounded(1.0)) / qreal(nx);
                    qreal v = qreal( j + random.bounded(1.0)) / qreal(ny);

                    ray primary_ray = cam.get_ray( u, v );

                    color = color + ray_to_color( primary_ray, world, random, 1 );
                }

                color = color / qreal(ns);

                int ir = int(255.99*color[0]);
                int ig = int(255.99*color[1]);
                int ib = int(255.99*color[2]);

                txt_myfile << ir << " " << ig << " " << ib << "\n";
            }
        }

        myfile.close();
        qDebug() << "Writing finished";
    }

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}
