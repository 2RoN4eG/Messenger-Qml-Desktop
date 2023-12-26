import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Peer Preview")


    Row {
        id: row1
        width: 400

        Column {
            id: peer_previews
            width: 250
            height: 480

            PeerPreview {
                id: peer_0
                avatarSource: "image://default/1"

                // Simulation changing avatar for peer
                Timer {
                    interval: 5000; running: true; repeat: false
                    // onTriggered: parent.avatarSource = "image://avatars/1"
                    onTriggered: parent.avatarSource = "image://photos/4"
                }
            }

            PeerPreview {
                id: peer_1
                avatarSource: "image://default/2"

                // Simulation changing avatar for peer
                Timer {
                    interval: 7500; running: true; repeat: false
                    // onTriggered: parent.avatarSource = "image://avatars/2"
                    onTriggered: parent.avatarSource = "image://photos/5"
                }
            }

            PeerPreview {
                id: peer_2
                avatarSource: "image://default/3"

                // Simulation changing avatar for peer
                Timer {
                    interval: 10000; running: true; repeat: false
                    // onTriggered: parent.avatarSource = "image://avatars/3"
                    onTriggered: parent.avatarSource = "image://photos/6"
                }
            }
        }
    }
}
