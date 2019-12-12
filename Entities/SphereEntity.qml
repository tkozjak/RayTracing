import Qt3D.Core 2.13
import Qt3D.Render 2.13
import Qt3D.Extras 2.13

//import QtQuick 2.2 as QQ2

Entity{

    property alias position : transform.translation
//    property alias position_t : position_animated
    property alias radius : sphere.radius
    property alias color : material.diffuse
//    property alias animation_time: animation_time

//    property var position_animated: Qt.vector3d( 0.0, 0.0, 0.0 )
//    property var animation_time: 0.0

    PhongMaterial{
        id: material
        diffuse: "gray"
        ambient: "darkgray"
    }

    Transform {
        id: transform
        translation: Qt.vector3d(0.0, 0.0, 0.0)
        rotation: fromAxisAndAngle(Qt.vector3d(1, 0, 0), 0)
    }

    SphereMesh {
        id: sphere
        radius: 1
        rings: 32
        slices: 32
    }

    Entity {
        id: sphere_entity
        components: [ sphere, material, transform ]
    }

}
