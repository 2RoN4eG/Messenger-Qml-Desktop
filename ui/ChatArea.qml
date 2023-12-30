import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ListView {
    id: chatListView
    spacing: 10
    model: 10 // Replace with your message model or use a ListModel

    width: 600
    height: 800

    delegate: Component {
        id: chat_component

        Item {
            width: 600
            height: 200

            Rectangle {
                anchors.fill: parent
                color: "white"

                RowLayout {
                    anchors.fill: parent
                    spacing: 10

                    Rectangle {
                        width: 60
                        height: 60
                        radius: width / 2
                        clip: true
                        Layout.alignment: Qt.AlignTop

                        Image {
                            anchors.fill: parent

                            source: "image://avatars/1"
                            sourceSize.height: parent.height
                            sourceSize.width: parent.width

                            fillMode: Image.PreserveAspectFit
                        }
                    }

                    ColumnLayout {
                        spacing: 5

                        Text {
                            id: peer_nickname
                            text: "John Doe"
                            font.bold: true
                        }

                        Text {
                            id: peer_message
                            text: "This is a sample message." // Replace with actual message text
                            wrapMode: Text.Wrap
                        }

                        Image {
                            id: sentPhoto
                            width: 150
                            height: 100
                            source: "image://photos/3"
                            sourceSize.width: width
                            sourceSize.height: height
                        }
                    }

                    Text {
                        id: message_timestamp
                        text: "10:00 AM" // Replace with actual timestamp
                        Layout.alignment: Qt.AlignTop | Qt.AlignRight
                    }
                }
            }
        }
    }

    //    ListModel {
    //        id: messages_model

    //        ListElement {
    //            peer_nickname: "Nikolas (Nick)"
    //            peer_avatar_source: "image://photos/1"
    //            message_photo_source: ""
    //            message_text: "Hello, my name is Nick, nice to meet you"
    //            message_timestamp: "12:51"
    //        }

    //        ListElement {
    //            peer_nickname: ""
    //            peer_avatar_source: "image://photos/3"
    //            message_photo_source: ""
    //            message_text: "Hello, my name is Open AI, nice to meet you too"
    //            message_timestamp: "12:52"
    //        }

    //        ListElement {
    //            peer_nickname: "Nikolas (Nick)"
    //            peer_avatar_source: "image://photos/1"
    //            message_photo_source: "image://photos/6"
    //            message_text: "Sending photo to you ..."
    //            message_timestamp: "12:52"
    //        }
    //    }
}
