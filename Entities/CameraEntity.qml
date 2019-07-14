import Qt3D.Core 2.13
import Qt3D.Render 2.13
import Qt3D.Extras 2.13

import QtQuick 2.13 as QQ2

Entity{

    property real aspectRatio: 2.0
    property real vFOV: 20
    property real hFOV: 40
    property var cameraPostion: Qt.vector3d( 1, 0.5, 5 )
    property var cameraLookAt: Qt.vector3d( 0.3, 0, -1 )

    QQ2.Component.onCompleted: {
        var cameraDirection = cameraLookAt.minus(cameraPostion);
        var normalizedCamDirection = cameraDirection.normalized();
        var cameraRightNormalizedVector = normalizedCamDirection.crossProduct( Qt.vector3d(0.0, 1.0, 0.0) );
        cameraRightNormalizedVector = cameraRightNormalizedVector.normalized();

        var cameraUpNormalizedVector = cameraRightNormalizedVector.crossProduct( normalizedCamDirection );
        cameraUpNormalizedVector = cameraUpNormalizedVector.normalized();

        console.log( normalizedCamDirection );
        console.log( cameraRightNormalizedVector );
        console.log( cameraUpNormalizedVector );

        cameraDirection_n = normalizedCamDirection;
        cameraRight_n = cameraRightNormalizedVector;
        cameraUp_n = cameraUpNormalizedVector;
    }

    property var cameraDirection_n : Qt.vector3d( 1, 0.5, 5 )
    property var cameraRight_n : Qt.vector3d( 1, 0.5, 5 )
    property var cameraUp_n : Qt.vector3d( 1, 0.5, 5 )

    Buffer{
        id: vertex_buffer
        type: Buffer.VertexBuffer
        data: {
            var buffer = new Float32Array(3*2);

            buffer[0] = 0;
            buffer[1] = 0;
            buffer[2] = 0;

            buffer[3] = cameraDirection_n.x;
            buffer[4] = cameraDirection_n.y;
            buffer[5] = cameraDirection_n.z;

            return buffer;
        }
    }

    GeometryRenderer{
        id: geometry_renderer
        instanceCount: 1
        indexOffset: 0
        firstInstance: 0

        primitiveType: GeometryRenderer.LineStrip

        geometry: Geometry{
            boundingVolumePositionAttribute: vertex_position
            Attribute{
                id: vertex_position
                attributeType: Attribute.VertexAttribute
                vertexBaseType: Attribute.Float

                vertexSize: 3
                byteOffset: 0
                byteStride: 3*4
                count: 2
                name: "vertexPosition"
                buffer: vertex_buffer
            }
        }
    }

    Transform {
        id: transform_1
        translation: Qt.vector3d( 0.0, 0.0, 0.0 )
        scale3D: Qt.vector3d( 10.0, 10.0, 10.0 )
        rotation: fromAxisAndAngle( Qt.vector3d(0, 1, 0), 0.0 )
    }

    Transform {
        id: transform_2
        translation: Qt.vector3d( 0.0, 0.0, 0.0 )
        scale3D: Qt.vector3d( 10.0, 10.0, 10.0 )
        rotation: fromAxisAndAngle( cameraUp_n, hFOV/2.0 )
    }

    Transform {
        id: transform_3
        translation: Qt.vector3d( 0.0, 0.0, 0.0 )
        scale3D: Qt.vector3d( 10.0, 10.0, 10.0 )
        rotation: fromAxisAndAngle( cameraUp_n, -hFOV/2.0 )
    }

    Transform {
        id: transform_4_1
        translation: Qt.vector3d( 0.0, 0.0, 0.0 )
        scale3D: Qt.vector3d( 10.0, 10.0, 10.0 )
        rotation: fromAxesAndAngles( cameraRight_n, vFOV/2.0, cameraUp_n, hFOV/2.0 )
    }

    Transform {
        id: transform_4_2
        translation: Qt.vector3d( 0.0, 0.0, 0.0 )
        scale3D: Qt.vector3d( 10.0, 10.0, 10.0 )
        rotation: fromAxesAndAngles( cameraRight_n, -vFOV/2.0, cameraUp_n, hFOV/2.0 )
    }

    Transform {
        id: transform_5_1
        translation: Qt.vector3d( 0.0, 0.0, 0.0 )
        scale3D: Qt.vector3d( 10.0, 10.0, 10.0 )
        rotation: fromAxesAndAngles( cameraRight_n, vFOV/2.0, cameraUp_n, -hFOV/2.0 )
    }

    Transform {
        id: transform_5_2
        translation: Qt.vector3d( 0.0, 0.0, 0.0 )
        scale3D: Qt.vector3d( 10.0, 10.0, 10.0 )
        rotation: fromAxesAndAngles( cameraRight_n, -vFOV/2.0, cameraUp_n, -hFOV/2.0 )
    }



    Material{
        id: custom_material
        parameters: []

        effect: Effect{
            parameters: []
            techniques: [
                Technique{
                    // GraphicsApiFilter

                    parameters: []
                    filterKeys: []

                    renderPasses: [
                        RenderPass{
                            id: render_pass_01
                            filterKeys: []
                            renderStates: []
                            parameters: []
                            shaderProgram: ShaderProgram{
                                vertexShaderCode: loadSource("qrc:/Shaders/cameralines.vert")
                                fragmentShaderCode: loadSource("qrc:/Shaders/cameralines.frag")
                            }
                        }
                    ]
                }
            ]
        }
    }

    Transform {
        id: main_transform
        property real y_anim: 0.0
        translation: cameraPostion
        scale3D: Qt.vector3d( 1.0, 1.0, 1.0 )
//        rotation: fromAxesAndAngles( Qt.vector3d(1, 0, 0), -vFOV/2.0, Qt.vector3d(0, 1, 0), -vFOV/2.0 )
    }

    QQ2.NumberAnimation {
        target: main_transform
        property: "y_anim"
        duration: 10000
        from: 0
        to: 0

        loops: QQ2.Animation.Infinite
        running: true
    }

    Entity{
        components: [geometry_renderer, main_transform, custom_material ]
    }



    Entity{
        id:composite

        components: [main_transform ]

            Entity{
                id: custom_entity_1
                components: [ geometry_renderer, transform_1, custom_material ]
            }

            Entity{
                id: custom_entity_2
                components: [ geometry_renderer, transform_2, custom_material ]
            }

            Entity{
                id: custom_entity_3
                components: [ geometry_renderer, transform_3, custom_material ]
            }

            Entity{
                id: custom_entity_4_1
                components: [ geometry_renderer, transform_4_1, custom_material ]
            }

            Entity{
                id: custom_entity_4_2
                components: [ geometry_renderer, transform_4_2, custom_material ]
            }

            Entity{
                id: custom_entity_5_1
                components: [ geometry_renderer, transform_5_1, custom_material ]
            }

            Entity{
                id: custom_entity_5_2
                components: [ geometry_renderer, transform_5_2, custom_material ]
            }

    }

}

