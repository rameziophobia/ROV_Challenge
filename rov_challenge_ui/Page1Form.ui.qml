import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    id: page
    width: 1280
    height: 670

    title: qsTr("Page 1")

    Label {
        width: 320
        height: 0
        text: qsTr("Key bindings")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pointSize: 40
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.right: parent.right
    }
}
