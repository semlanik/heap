import QtQuick 2.0
import QtWayland.Compositor 1.0
Rectangle {
    color: "blue"
    Rectangle {
        anchors.fill: parent
        objectName: "output"
        color:"red"
        clip: true
    }
}
