import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.0
import Bindings 1.0

ListView {
    property int font_size: 12

    id: peer_area
    spacing: 0
    model: peer_info_context.count()

    width: 300
    height: 800

    delegate: Item {
        id: peer_item
        width: 300
        height: 60

        Rectangle {
            anchors.fill: parent
            color: "white"

            RowLayout {
                spacing: 0

                Image {
                    id: peer_avatar
                    width: peer_item.height
                    height: peer_item.height

                    source: peer_info_context.avatar_id(index)
                    sourceSize.height: Math.min(width, height)
                    sourceSize.width: Math.min(width, height)

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
                    id: info_preview

                    Text {
                        height: 25
                        text: peer_info_context.nickname(index)
                        font.pixelSize: font_size
                        font.bold: true

                        Layout.alignment: Qt.AlignTop
                    }

                    Text {
                        id: message
                        text: qsTr("Hello, I would like to say you ...")
                        font.pixelSize: font_size

                        Layout.alignment: Qt.AlignTop
                    }
                }

                ColumnLayout {
                    id: extra_info_preview
                    width: 25

                    Text {
                        id: peer_last_message_timestamp
                        text: peer_info_context.last_message_timestamp(index)
                        font.pixelSize: font_size
                        horizontalAlignment: Text.AlignRight

                        Layout.alignment: Qt.AlignTop | Qt.AlignRight
                    }

                    Rectangle {
                        radius: 30
                        width: 30
                        height: 20
                        color: "black"

                        Text {
                            width: parent.width
                            height: parent.height

                            text: peer_info_context.messages_to_read(index)
                            color: "white"
                            font.pixelSize: font_size
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    }
                }
            }
        }
    }
}
