import Qt3D.Core 2.13
import Qt3D.Render 2.13
import Qt3D.Input 2.13
import Qt3D.Extras 2.13

import QtQuick 2.2 as QQ2

import "Entities"

Entity{
    id: root

    Camera{
        id: perspective_camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 70
        nearPlane: 0.1
        farPlane: 1000.0

        position: Qt.vector3d( 1.0, 0.5, 5.0 )
        upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
        viewCenter: Qt.vector3d( 0.3, 0.0, -1.0 )


    }

    OrbitCameraController{
        camera: perspective_camera
    }

    components: [
        RenderSettings{
            activeFrameGraph: RenderSurfaceSelector{



                Viewport{

                    ClearBuffers{
                        buffers: ClearBuffers.AllBuffers
                        clearColor: "azure"

                        CameraSelector{
                            id: camera_selector
                            camera: perspective_camera
                        }
                    }
                }
            }
        },
        InputSettings{}
    ]


    DirectionalLight{
        worldDirection: Qt.vector3d( 0.0, -1.0, 0.0 )
    }

    PhongMaterial{
        id: material_1
        diffuse: "gray"
        ambient: "darkgray"
    }

    Transform {
        id: transform_1
        translation: Qt.vector3d(1.5, 0.0, -1.0)
        rotation: fromAxisAndAngle(Qt.vector3d(1, 0, 0), 0)
    }

    Transform {
        id: transform_2
        translation: Qt.vector3d(0.0, -100.5, -1.0)
        rotation: fromAxisAndAngle(Qt.vector3d(1, 0, 0), 0)
    }

    Transform {
        id: transform_3
        translation: Qt.vector3d(1.1, 0.0, -1.0)
        rotation: fromAxisAndAngle(Qt.vector3d(1, 0, 0), 0)
    }

    Transform {
        id: transform_4
        translation: Qt.vector3d(-0.95, -0.1, -1.2)
        rotation: fromAxisAndAngle(Qt.vector3d(1, 0, 0), 0)
    }

    SphereMesh {
        id: sphere_1
        radius: 0.5
        rings: 32
        slices: 32
    }

    SphereMesh {
        id: sphere_2
        radius: 100
        rings: 32
        slices: 32
    }

    SphereMesh {
        id: sphere_3
        radius: 0.5
        rings: 32
        slices: 32
    }

    SphereMesh {
        id: sphere_4
        radius: 0.3
        rings: 32
        slices: 32
    }

    Entity {
        id: sphere_entity_1
        components: [ sphere_1, material_1, transform_1 ]
    }

    Entity {
        id: sphere_entity_2
        components: [ sphere_2, material_1, transform_2 ]
    }

    Entity {
        id: sphere_entity_3
        components: [ sphere_3, material_1, transform_3 ]
    }

    Entity {
        id: sphere_entity_4
        components: [ sphere_4, material_1, transform_4 ]
    }

    CameraEntity{

    }
}
