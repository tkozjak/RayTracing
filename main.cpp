#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

#include "vector3d.h"

#include <iostream>
#include <fstream>
#include <vector>

void forEach( std::vector<int>& values, int(*my_func)(int) ){

    for( int value : values){
        int return_value = my_func(value);
        qDebug() << "Return value: " << return_value;
    }
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

    std::ofstream myfile;
    myfile.open ("example.ppm");
    myfile <<"P3\n" << nx << " " << ny << "\n255\n";
    for(int j = ny-1; j >=0; j--){
        for(int i=0; i<nx; i++){
            qreal r = qreal(i)/qreal(nx);
            qreal g = qreal(j)/qreal(ny);
            qreal b = 0.2;

            int ir = int(255.99*r);
            int ig = int(255.99*g);
            int ib = int(255.99*b);

            myfile << ir << " " << ig << " " << ib << "\n";
        }
    }
    myfile.close();

    return app.exec();
}
