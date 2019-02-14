#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QFile>

#include "vector3d.h"
#include "ray.h"

//
bool hit_sphere( const vec3 &sphere_center, const qreal sphere_radius, const ray &input_ray){
    vec3 o_to_c = input_ray.origin() - sphere_center;

    qreal a = dot( input_ray.direction(), input_ray.direction());
    qreal b = 2.0 * dot( o_to_c, input_ray.direction() );
    qreal c = dot( o_to_c, o_to_c ) - sphere_radius*sphere_radius;
    qreal discriminant = b*b - 4*a*c;
    return( discriminant > 0.0 );
}


vec3 ray_to_color( const ray& in_ray ){
    if( hit_sphere( vec3( 0.0, 0.0, -1.0), 0.5, in_ray ))
        return vec3( 1.0, 0.0, 0.0 );
    vec3 unit_direction = unit_vector( in_ray.direction());
    qreal t = 0.5 * ( unit_direction.y() + 1.0 );
    return( 1.0 - t ) * vec3( 1.0, 1.0, 1.0 ) + t * vec3( 0.5, 0.7, 1.0 );
}



int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;



    int nx = 200;
    int ny = 100;

    QFile myfile("example.ppm");
    if(myfile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // We're going to streaming text to the file
        QTextStream txt_myfile(&myfile);

        // vectors that describe our viewing plane
        vec3 lower_left_corner( -2.0, -1.0, -1.0 );
        vec3 horizontal( 4.0, 0.0, 0.0 );
        vec3 vertical( 0.0, 2.0, 0.0 );
        vec3 origin( 0.0, 0.0, 0.0 );

        txt_myfile <<"P3\n" << nx << " " << ny << "\n255\n";
        for(int j = ny-1; j >=0; j--){
            for(int i=0; i<nx; i++){

                qreal u = qreal(i) / qreal(nx);
                qreal v = qreal(j) / qreal(ny);

                ray primary_ray( origin, lower_left_corner + u*horizontal +v*vertical);
                vec3 color = ray_to_color(primary_ray);

                int ir = int(255.99*color[0]);
                int ig = int(255.99*color[1]);
                int ib = int(255.99*color[2]);

                txt_myfile << ir << " " << ig << " " << ib << "\n";
            }
        }

        vec3 first( 1.0, 0.0, 0.0);
        vec3 second( 0.0, 0.0, 1.0);

        qDebug() << cross( first, second ) + cross( first, second );

        myfile.close();
        qDebug() << "Writing finished";
    }

    return app.exec();
}
