import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Qml Messanger Demo")

    SplitView {
        anchors.fill: parent

        Item {
            SplitView.minimumWidth: 200
            SplitView.preferredWidth: 300

            PeerArea {
                visible: true
                width: parent.width
                height: parent.height
                // onClicked: root.StackView.view.push("ConversationPage.qml", { inConversationWith: modelData })
            }
        }

        StackView {
            SplitView.preferredWidth: 600

            ChatArea {
                visible: true
                width: parent.width
                height: parent.height
            }
        }

        Item {
            SplitView.preferredWidth: 300

            DebugArea {
                visible: true
                width: parent.width
                height: parent.height
            }
        }
    }
}
