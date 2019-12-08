#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QWindow>
#include <QDebug>
#include <QThread>

#include "scenemodel.h"

#include "main_scene.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

//    QRandomGenerator random;

    for( qreal i = -3; i<=3; i++ ){
        qreal num = ( 5 - 5 ) / i;
        qDebug() << num;
    }

    qDebug() << "IDEAL CPUs: " << QThread::idealThreadCount();


    qmlRegisterType<SceneModel>( "Scene", 1, 0, "SceneModel");
    qmlRegisterUncreatableType<main_scene>( "Scene", 1, 0, "MainScene",
                                            QStringLiteral("sss"));

    main_scene my_scene;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty( "_my_scene", &my_scene );
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    //get root item (window)
    QList<QObject*> root_objects = engine.rootObjects();
    QWindow *ui_window = qobject_cast<QWindow*>(root_objects.at(0));
    qDebug() << ui_window->objectName();

    QObject::connect( &my_scene, SIGNAL(renderComplete()), ui_window, SLOT(slot_renderCompleted()) );


    return app.exec();
}
