import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt5Compat.GraphicalEffects

ListView {
    id: chat_area
    spacing: 0
    model: 10

    width: parent.width
    height: parent.height

    delegate: Item {
        width: chat_area.width
        height: 200

        Rectangle {
            anchors.fill: parent
            width: parent.width
            color: "white"

            RowLayout {
                anchors.fill: parent
                spacing: 0

                Image {
                    id: peer_avatar


                    source: "image://avatars/" + (index + 1)
                    sourceSize.height: height
                    sourceSize.width: width

                    fillMode: Image.PreserveAspectFit
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft

                    layer.enabled: true
                    layer.effect: OpacityMask {
                        maskSource: Item {
                            width: peer_avatar.width
                            height: peer_avatar.height

                            Rectangle {
                                anchors.centerIn: parent
                                width: Math.min(peer_avatar.width, peer_avatar.height)
                                height: Math.min(peer_avatar.width, peer_avatar.height)
                                radius: Math.min(width, height)
                            }
                        }
                    }
                }

                ColumnLayout {
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft

                    Text {
                        id: peer_nickname
                        text: "John Doe"
                        font.bold: true
                    }

                    Image {
                        id: sent_photo
                        width: 250
                        height: 150
                        source: "image://photos/3"
                        sourceSize.width: width
                        sourceSize.height: height
                    }

                    Text {
                        id: message_text
                        text: "This is a sample message." // Replace with actual message text
                        wrapMode: Text.Wrap
                    }
                }

                Text {
                    id: message_timestamp
                    text: "23:41" // Replace with actual timestamp

                    Layout.alignment: Qt.AlignTop | Qt.AlignRight
                }
            }
        }
    }
}
