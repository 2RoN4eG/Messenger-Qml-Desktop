import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Messanger Demo")

    RowLayout {
//        ColumnLayout {
//            id: peer_previews

//            PeerPreview {
//                id: peer_0
//                peer_avatar_source: "image://default/1"
//                width: 300
//                height: 80

//                // Simulation changing avatar for peer
//                Timer {
//                    interval: 5000; running: true; repeat: false
//                    // onTriggered: parent.peer_avatar_source = "image://avatars/1"
//                    onTriggered: parent.peer_avatar_source = "image://photos/4"
//                }
//            }

//            PeerPreview {
//                id: peer_1
//                peer_avatar_source: "image://default/2"
//                width: 300
//                height: 80

//                // Simulation changing avatar for peer
//                Timer {
//                    interval: 7500; running: true; repeat: false
//                    // onTriggered: parent.peer_avatar_source = "image://avatars/2"
//                    onTriggered: parent.peer_avatar_source = "image://photos/5"
//                }
//            }

//            PeerPreview {
//                id: peer_2
//                peer_avatar_source: "image://default/3"
//                width: 350
//                height: 80

//                // Simulation changing avatar for peer
//                Timer {
//                    interval: 10000; running: true; repeat: false
//                    // onTriggered: parent.peer_avatar_source = "image://avatars/3"
//                    onTriggered: parent.peer_avatar_source = "image://photos/6"
//                }
//            }
//        }

        PeerArea {
            visible: true
            width: 400
        }

        ChatArea {
            visible: true
            width: 400
        }

    }
}
