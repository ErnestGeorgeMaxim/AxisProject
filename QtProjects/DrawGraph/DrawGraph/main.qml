import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: "DrawGraph"
    Text {
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.bold: true
        font.pointSize: 42
        text: "Hello World!"
    }
     
    Button {
        visible: true
        width: 100
        height: 200
        Text {
            anchors.fill: parent
            horizontalAligment: Text.AlignHTop
            verticallAligment: Text.AlignVRight
            font.bold: true
            font.pointSize: 42
            text: "Create Node"
    }
}

