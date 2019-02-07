import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Image{
        anchors.fill: parent
        source: "file:///C:/PROJECTS/Qt/build-RayTracing-Desktop_Qt_5_11_1_MSVC2017_64bit-Debug/example.ppm"
    }
}
