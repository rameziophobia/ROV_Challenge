import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    id: page
    width: 1280
    height: 670
    property alias timer_label: timer_label
    property alias timer_btn: timer_btn

    title: qsTr("Home")

    Grid {
        id: scripts_grid
        y: 494
        width: 424
        height: 168
        columns: 3
        anchors.leftMargin: 21
        anchors.left: parent.left
        spacing: 10
        padding: 10

        Button {
            id: line_follower_btn
            width: 140
            text: qsTr("Line follower")
        }

        Button {
            id: coin_script_btn
            width: 140
            text: qsTr("Coins")
        }

        Label {
            id: coin_lbl
            text: qsTr("coins")
        }

        Button {
            id: detonate_btn
            width: 140
            text: qsTr("Detonate!")
        }

        Button {
            id: detect_material_btn
            width: 140
            text: qsTr("Detect material")
        }

        Label {
            id: detect_metal_lbl
            text: qsTr("material")
            horizontalAlignment: Text.AlignHCenter
        }

        Button {
            id: open_door_btn
            width: 140
            text: qsTr("Open door")
        }

        Button {
            id: set_cam_angle_btn
            width: 140
            text: qsTr("Set cam angle")
        }

        TextField {
            id: cam_angle_textField
            width: 120
            text: qsTr("0 - 360")
        }
    }

    StackLayout {
        id: timer_stackLayout
        x: 972
        y: 524
        width: 222
        height: 100

        Label {
            id: timer_label
            color: "#262b2a"
            text: qsTr("15:00")
            fontSizeMode: Text.Fit
            font.pointSize: 70
            lineHeight: 1
            MouseArea {
                id: timer_btn
                anchors.fill: parent
            }
        }
    }

    ColumnLayout {
        id: columnLayout1
        x: 878
        y: 248
        width: 366
        height: 234
        spacing: 10

        Label {
            id: sensor_data_label
            text: qsTr("Sensor data:")
            fontSizeMode: Text.VerticalFit
            Layout.preferredWidth: -1
            wrapMode: Text.NoWrap
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            padding: 10
        }

        GridLayout {
            id: gridLayout
            width: 100
            height: 100
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            columns: 2

            Label {
                id: label1
                width: 240
                height: 20
                text: qsTr("Depth:")
                Layout.preferredHeight: 23
                font.pointSize: 13
                horizontalAlignment: Text.AlignHCenter
                lineHeight: 0.7
                font.family: "Times New Roman"
                Layout.fillHeight: false
                Layout.fillWidth: true
            }

            Label {
                id: label2
                width: 240
                height: 20
                text: qsTr("999m")
                Layout.fillWidth: true
                Layout.fillHeight: false
                Layout.preferredHeight: 23
                lineHeight: 0.7
                font.family: "Times New Roman"
                font.pointSize: 13
                horizontalAlignment: Text.AlignHCenter
            }

            Label {
                id: label3
                width: 240
                height: 20
                text: qsTr("Temp1:")
                Layout.fillWidth: true
                Layout.fillHeight: false
                Layout.preferredHeight: 23
                lineHeight: 0.7
                font.family: "Times New Roman"
                font.pointSize: 13
                horizontalAlignment: Text.AlignHCenter
            }

            Label {
                id: label4
                width: 240
                height: 20
                text: qsTr("999C")
                Layout.fillWidth: true
                Layout.fillHeight: false
                Layout.preferredHeight: 23
                lineHeight: 0.7
                font.family: "Times New Roman"
                font.pointSize: 13
                horizontalAlignment: Text.AlignHCenter
            }

            Label {
                id: label5
                width: 240
                height: 20
                text: qsTr("Temp2:")
                Layout.fillWidth: true
                Layout.fillHeight: false
                Layout.preferredHeight: 23
                lineHeight: 0.7
                font.family: "Times New Roman"
                font.pointSize: 13
                horizontalAlignment: Text.AlignHCenter
            }

            Label {
                id: label6
                width: 240
                height: 20
                text: qsTr("999C")
                Layout.fillWidth: true
                Layout.fillHeight: false
                Layout.preferredHeight: 23
                lineHeight: 0.7
                font.family: "Times New Roman"
                font.pointSize: 13
                horizontalAlignment: Text.AlignHCenter
            }

            Label {
                id: label7
                width: 240
                height: 20
                text: qsTr("Temp3:")
                Layout.fillWidth: true
                Layout.fillHeight: false
                Layout.preferredHeight: 23
                lineHeight: 0.7
                font.family: "Times New Roman"
                font.pointSize: 13
                horizontalAlignment: Text.AlignHCenter
            }

            Label {
                id: label8
                width: 240
                height: 20
                text: qsTr("999C")
                Layout.fillWidth: true
                Layout.fillHeight: false
                Layout.preferredHeight: 23
                lineHeight: 0.7
                font.family: "Times New Roman"
                font.pointSize: 13
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

    Rectangle {
        id: rectangle
        x: 21
        y: 14
        width: 832
        height: 468
        color: "#fdd0d0"
    }

    Rectangle {
        id: rectangle1
        x: 864
        y: 14
        width: 400
        height: 225
        color: "#fdd0d0"
    }

    RowLayout {
        id: rowLayout
        x: 469
        y: 502
        width: 343
        height: 144

        GridLayout {
            id: gridLayout2
            width: 100
            height: 100
            Button {
                id: button12
                width: 70
                text: qsTr("box1")
            }

            Button {
                id: button13
                width: 70
                text: qsTr("box2")
            }

            Button {
                id: button14
                width: 70
                text: qsTr("box3")
            }
            columns: 1
        }

        ColumnLayout {
            id: columnLayout3
            width: 100
            height: 100
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop

            RoundButton {
                id: roundButton2
                text: "compare"
            }

            TextArea {
                id: textArea2
                color: "#204a87"
                text: qsTr("Box info:")
                wrapMode: Text.WordWrap
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                textFormat: Text.AutoText
                horizontalAlignment: Text.AlignLeft
            }
        }
    }
}




/*##^## Designer {
    D{i:2;anchors_height:168;anchors_width:337;anchors_x:67;anchors_y:703}D{i:29;anchors_y:404}
}
 ##^##*/
