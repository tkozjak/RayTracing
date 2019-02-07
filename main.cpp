#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

#include "vector3d.h"

#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    // add this

    // more


    int nx = 200;
    int ny = 100;

    std::ofstream myfile;
    myfile.open ("example.ppm");
    myfile <<"P3\n" << nx << " " << ny << "\n255\n";
    for(int j = ny-1; j >=0; j--){
        for(int i=0; i<nx; i++){
            float r = float(i)/float(nx);
            float g = float(j)/float(ny);
            float b = 0.2;

            int ir = int(255.99*r);
            int ig = int(255.99*g);
            int ib = int(255.99*b);

            myfile << ir << " " << ig << " " << ib << "\n";
        }
    }
    myfile.close();

    return app.exec();
}
