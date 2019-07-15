import QtQuick 2.13
import QtQuick.Window 2.13

import QtQuick.Controls 2.5
import QtQuick.Layouts 1.13

import QtQuick.Scene3D 2.13
import Qt3D.Core 2.13

import "GUI"

Window {
    id: root_window

    objectName: "Root Window";

    visible: true
    width: 1200
    height: 600

    title: qsTr("Ray Tracing in a Week")

    function slot_renderCompleted(){
        console.log( "render completed");

        rendered_image.source =  "";
//        rendered_image.source = "file:///C:/PROJECTS/Qt/build-RayTracing-Desktop_Qt_5_13_0_MSVC2017_64bit-Debug/example.ppm"
        rendered_image.source = "file:///C:/Users/Show/Documents/Qt/build-RayTracing-Desktop_Qt_5_13_0_MSVC2015_64bit3-Debug/example.ppm"
        rendered_image.visible = true;

        button_timer.start();
    }

    ColumnLayout{
        id: controls_columns
        spacing: 5

        x:20; y:20

        ControlSB{
            id: size_x_SB

            name: "SIZE X"

            function setValue(){ _my_scene.setNx( value ); }
            Component.onCompleted: { getSize( _my_scene.getNx() ); }
        }

        ControlSB{
            id: size_y_SB

            name: "SIZE Y"

            function setValue(){ _my_scene.setNy( value ); }
            Component.onCompleted: { getSize( _my_scene.getNy() ); }
        }

        ControlSB{
            id: num_s_SB

            name: "SAMPLES"
            from: 1
            to: 100
            stepSize: 1

            function setValue(){ _my_scene.setNs( value ); }
            Component.onCompleted: { getSize( _my_scene.getNs() ); }
        }

        Button{
            id: render_button
            text: "RENDER"
            height: 30
            implicitWidth: size_x_SB.width

            Timer {
                id: render_timer
                interval: 1000;
                running: false;
                repeat: false
                onTriggered: _my_scene.draw_scene();
            }

            Timer {
                id: button_timer
                interval: 1000;
                running: false;
                repeat: false
                onTriggered: render_button.enabled = true;
            }

            onClicked: {
                console.log( "button clicked");
                render_button.enabled = false;
                render_timer.start();
            }
        }
    }

    Rectangle{
        anchors.fill: controls_columns
        border.color: "red"
        color: "transparent"
    }

    Scene3D{
        id: scene_3d_frame
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.left: controls_columns.right
        anchors.leftMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        aspects: ["input", "logic"]

        cameraAspectRatioMode: Scene3D.AutomaticAspectRatio

        MainScene3D{
            id: scene_3d
        }
    }

    Rectangle{
        anchors.fill: scene_3d_frame
        color: "transparent"
        border.color: "red"
    }

    Window{
        id: render_window
        visible: true
        width: image_rectangle.width
        height: image_rectangle.height

        title: qsTr("Render result")

        Rectangle{
            id: image_rectangle
            color: "transparent"
            border.color: "red"
            width: size_x_SB.value
            height: size_y_SB.value
        }

        Image{
            id: rendered_image
            visible: false
            width: image_rectangle.width
            height: image_rectangle.height
            smooth: false
            asynchronous: false
            cache: false

            function resetImage(){
                console.log( "image reset");
                visible = false;
            }
        }
    }
}
