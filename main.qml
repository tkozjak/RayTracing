import QtQuick 2.11
import QtQuick.Window 2.11

Window {
    visible: true
    width: 640
    height: 400
    title: qsTr("Ray Tracing in a Weekend")

    Image{
        anchors.fill: parent
        smooth: false
        source: "file:///C:/Users/Show/Documents/Qt/build-RayTracing-Desktop_Qt_5_11_1_MSVC2015_64bit2-Debug/example.ppm"
    }
}
