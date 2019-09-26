import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    width: 600
    height: 400

    title: qsTr("Page 2")

    Label {
        text: qsTr("You are on Page 2.")
        anchors.verticalCenterOffset: 57
        anchors.horizontalCenterOffset: -164
        anchors.centerIn: parent
    }

    ColumnLayout {
        id: columnLayout2
        x: 74
        y: 25
        width: 330
        height: 160
        transformOrigin: Item.Center
        Row {
            id: box_script_row1
            width: 330
            height: 70
            spacing: 10
            padding: 10
            Button {
                id: button9
                width: 70
                text: qsTr("box1")
            }

            Button {
                id: button10
                width: 70
                text: qsTr("box2")
            }

            Button {
                id: button11
                width: 70
                text: qsTr("box3")
            }

            RoundButton {
                id: roundButton1
                text: "compare"
            }
        }

        TextArea {
            id: textArea1
            color: "#204a87"
            text: qsTr("Box info:")
            wrapMode: Text.WordWrap
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            textFormat: Text.AutoText
            horizontalAlignment: Text.AlignLeft
        }
    }

    ColumnLayout {
        id: columnLayout
        x: 263
        y: 143
        width: 330
        height: 160
        transformOrigin: Item.Center
        z: 1
        TextArea {
            id: textArea
            color: "#204a87"
            text: qsTr("Box info:")
            wrapMode: Text.WordWrap
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            textFormat: Text.AutoText
            horizontalAlignment: Text.AlignLeft
        }

        GridLayout {
            id: gridLayout1
            width: 100
            height: 100
            Button {
                id: button6
                width: 70
                text: qsTr("box1")
            }

            Button {
                id: button7
                width: 70
                text: qsTr("box2")
            }

            Button {
                id: button8
                width: 70
                text: qsTr("box3")
            }

            RoundButton {
                id: roundButton
                text: "compare"
            }
            columns: 1
        }
    }
}
