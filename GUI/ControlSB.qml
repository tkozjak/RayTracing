import QtQuick 2.13
import QtQuick.Window 2.13

import QtQuick.Controls 2.5
import QtQuick.Layouts 1.13

import QtQuick.Scene3D 2.13
import Qt3D.Core 2.13


Item {
    id: root

    property alias value: size.value
    property alias name: name.text

    property alias from: size.from
    property alias to: size.to
    property alias stepSize: size.stepSize

    function getSize( in_value ){
        size.value = in_value;
    }

    width: 200
    height: childrenRect.height

    Text{
        id: name
        text: "SIZE"
        font.pixelSize: 13
        padding: 5

        Rectangle{
            anchors.fill: parent
            border.color: "cyan"
            color: "transparent"
        }
    }

    SpinBox{
        id: size
        anchors.top: name.bottom
        anchors.topMargin: 0

        implicitWidth: root.width
        height:30

        from:100; to:4000
        stepSize:100

        onValueModified: {
            root.setValue();
        }
    }

    Rectangle{
        anchors.fill: parent
        border.color: "magenta"
        color: "transparent"
    }
}
