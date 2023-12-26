import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.0

ListView {
    // property var conversation_provider: conversation_provider

    id: chat_area
    spacing: 0
    model: conversation_provider.size()

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

                    property string photo_source: conversation_provider.latest_avatar_id(index)

                    source: photo_source
                    sourceSize.height: height
                    sourceSize.width: width
                    visible: photo_source.length ? true : false

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
                        text: conversation_provider.message_peer_nickname(index)
                        font.bold: true
                    }

                    Image {
                        property string photo_source: conversation_provider.message_photo(index)

                        id: sent_photo
                        width: 250
                        height: photo_source.length ? 150 : 0
                        source: conversation_provider.message_photo(index)
                        sourceSize.width: width
                        sourceSize.height: photo_source.length ? height : 0
                    }

                    Text {
                        id: message_text
                        text: conversation_provider.message_text(index)
                        wrapMode: Text.Wrap
                    }
                }

                Text {
                    id: message_timestamp
                    text: conversation_provider.message_timestamp(index)

                    Layout.alignment: Qt.AlignTop | Qt.AlignRight
                }
            }
        }
    }
}
