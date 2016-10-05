import QtQuick 2.0

Item {
ListView {
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    width: 500
    model:_universalModel
    delegate:Text {
            height: 80
            width: 500
            wrapMode: Text.WordWrap
            text: "I'm item: " + model.name + "\nmy param1: " + model.param1 + "\nmy param2: " + model.param2
        }
}
}
