import QtQuick 2.9
import QtQuick.Controls 2.2
import RovTimer 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 1280
    height: 720
    title: qsTr("Stack")
    property alias my_text:my_text

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Page 1")
                width: parent.width
                onClicked: {
                    stackView.push("Page1Form.ui.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Page 2")
                width: parent.width
                onClicked: {
                    stackView.push("Page2Form.ui.qml")
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: "HomeForm.ui.qml"
        anchors.fill: parent



        HomeForm{
            id: homeForm
            timer_btn.onClicked: rov_timer.start()
            Text {
                id: my_text
                text: rov_timer.timer_text
                font.pointSize: 80
            }
            timer_label{
                text: rov_timer.timer_text
                }
        }
    }
    RovTimer {
        id: rov_timer
        interval: 1000
    }



}
