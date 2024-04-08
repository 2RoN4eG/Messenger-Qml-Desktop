import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.0

ListView {
    id: conversation_area_view
    spacing: 0
    model: conversation_provider.size()

    width: parent.width
    height: parent.height

    delegate: Item {
        id: conversation_item
        width: conversation_area_view.width
        height: 200

        Rectangle {
            anchors.fill: parent
            width: parent.width
            color: "white"

            RowLayout {
                anchors.fill: parent
                spacing: 0

                Image {
                    readonly property string latest_peer_avatar_source: preview_provider.latest_peer_avatar(index)
                    readonly property int latest_peer_avatar_width: 50
                    readonly property int latest_peer_avatar_height: 50

                    id: latest_peer_avatar
                    width: latest_peer_avatar_width
                    height: latest_peer_avatar_height

                    source: latest_peer_avatar_source
                    sourceSize.height: Math.min(width, height)
                    sourceSize.width: Math.min(width, height)

                    fillMode: Image.PreserveAspectFit

                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft

                    layer.enabled: true
                    layer.effect: OpacityMask {
                        maskSource: Item {
                            width: latest_peer_avatar.width
                            height: latest_peer_avatar.height

                            Rectangle {
                                anchors.centerIn: parent
                                width: Math.min(latest_peer_avatar.width, latest_peer_avatar.height)
                                height: Math.min(latest_peer_avatar.width, latest_peer_avatar.height)
                                radius: Math.min(width, height)
                            }
                        }
                    }
                }

                ColumnLayout {
                    Layout.alignment: Qt.AlignTop | Qt.AlignLeft

                    Text {
                        id: peer_nickname
                        text: conversation_provider.peer_nickname(index)
                        font.bold: true
                    }

                    Image {
                        readonly property string sent_photo_source: conversation_provider.message_photo(index)

                        id: sent_photo

                        width: 250
                        height: sent_photo_source.length ? 150 : 0

                        source: sent_photo_source
                        sourceSize.width: width
                        sourceSize.height: sent_photo_source.length ? height : 0
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
