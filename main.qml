import QtQuick 2.13
import QtQuick.Window 2.13

import QtQuick.Controls 2.5
import QtQuick.Layouts 1.13

import QtQuick.Scene3D 2.13
import Qt3D.Core 2.13

import "GUI"

import Scene 1.0

Window {
    id: root_window

    objectName: "Root Window";

    visible: true
    width: 1200
    height: 600

    title: qsTr("Ray Tracing in a Week")

    function slot_renderCompleted(){
        console.log( "render completed");

        var applicationPath = _my_scene.getApplicationPath();

        console.log( applicationPath );

        rendered_image.source =  "";
        rendered_image.source = "file:///" + applicationPath + "/example.ppm";
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


            function setValue(){

                var posVec = scene_3d.cam_pos
                var lookAtVec = scene_3d.cam_lookAt

                _my_scene.setNx( value, posVec, lookAtVec );
            }
            Component.onCompleted: { getSize( _my_scene.getNx() ); }
        }

        ControlSB{
            id: size_y_SB

            name: "SIZE Y"

            function setValue(){

                var posVec = scene_3d.cam_pos
                var lookAtVec = scene_3d.cam_lookAt

                _my_scene.setNy( value, posVec, lookAtVec );
            }
            Component.onCompleted: { getSize( _my_scene.getNy() ); }
        }

        ControlSB{
            id: num_s_SB

            name: "SAMPLES"
            from: 1
            to: 100
            stepSize: 1

            function setValue(){

                var posVec = scene_3d.cam_pos
                var lookAtVec = scene_3d.cam_lookAt

                _my_scene.setNs( value, posVec, lookAtVec );
            }
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

    // LIST
    ColumnLayout{
        anchors.top : controls_columns.bottom
        anchors.topMargin: 10
        anchors.left : controls_columns.left

        Frame{
            id: list_frame
            implicitWidth: controls_columns.width

            ListView{
                id: list_view

                implicitWidth: parent.width
                implicitHeight: 250

                clip: true

                model: SceneModel{
                    id: scene_model
                    scene: _my_scene

                    onRowsInserted: {
                        console.log("Row inserted!")
//                        console.log(scene_model.rowCount());
                    }

                    onModelReset: {
                        console.log("model reset")
                    }
                }

                delegate: RowLayout{
                    width: parent.width

                    Text{
                        text: model.name
                    }

                    Text{
                        text: model.type
                    }

                    TextField{
                        text: model.radius
                        onEditingFinished: {
                            switch(index+1){
                            case 1:
                                scene_3d.s_1_m = text;
                                break;
                            case 2:
                                scene_3d.s_2_m = text;
                                break;
                            case 3:
                                scene_3d.s_3_m = text;
                                break;
                            case 4:
                                scene_3d.s_4_m = text;
                                break;
                            }
                            console.log( "index: " + index );
                            model.radius = text;
                        }
                    }

//                    Text{
//                        text: model.position.x + "; " + model.position.y + "; " + model.position.z
//                    }
                }

                // TEMP: setup our 3D scene by going through items in our model
                Component.onCompleted: {
                    for( var i=1; i<list_view.model.rowCount()+1; i++){

                        var name_role = 257;
                        var type_role = 258;
                        var position_role = 259;
                        var radius_role = 260;

                        var pos_vector = Qt.vector3d(0.0, 0.0, 0.0);
                        pos_vector = list_view.model.returnDataAt( i-1, position_role );
                        var radius
                        radius = list_view.model.returnDataAt( i-1, radius_role );

                        // initial spheres
                        switch(i){
                        case 1:
                            scene_3d.s_1_pos = pos_vector;
                            scene_3d.s_1_m = radius;
                            break;
                        case 2:
                            scene_3d.s_2_pos = pos_vector;
                            scene_3d.s_2_m = radius;
                            break;
                        case 3:
                            scene_3d.s_3_pos = pos_vector;
                            scene_3d.s_3_m = radius;
                            break;
                        case 4:
                            scene_3d.s_4_pos = pos_vector;
                            scene_3d.s_4_m = radius;
                            break;
                        }
                    }
                }
            }
        }

        Button{
            text: qsTr("append")
            onClicked: _my_scene.appendEntity();
        }
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
