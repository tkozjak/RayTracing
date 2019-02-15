import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    visible: true
    width: 600
    height: 300
    title: qsTr("Ray Tracing in a Weekend")

    Image{
        anchors.fill: parent
        smooth: false
        source: "file:///C:/PROJECTS/Qt/build-RayTracing-Desktop_Qt_5_11_1_MSVC2017_64bit-Debug/example.ppm"
    }
}
