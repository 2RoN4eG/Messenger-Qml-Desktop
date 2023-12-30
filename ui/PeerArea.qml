import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ListView {
    id: peers
    spacing: 0
    model: 20  // Replace with your message model or use a ListModel

    width: 300
    height: 800

    property string peer: "2048"
    property string peer_nickname: "Nick O'Conor"
    property string peer_last_message: "Hello, it's my last message to you ...\n second line"
    property string peer_last_message_timestamp: "12:51"
    property int peer_message_amount: 12

    property string peer_avatar_source: "image://avatars/1"
    property int font_size: 12

    delegate: Component {
        id: peer_component

        Item {
            id: peer_item
            width: 300
            height: 60

            Rectangle {
                anchors.fill: parent
                color: "white"

                RowLayout {
                    spacing: 0

                    Rectangle {
                        width: peer_item.height
                        height: peer_item.height
                        radius: width / 2
                        clip: true
                        Layout.alignment: Qt.AlignTop

                        Image {
                            anchors.fill: parent

                            source: peer_avatar_source
                            sourceSize.height: parent.height
                            sourceSize.width: parent.width

                            fillMode: Image.PreserveAspectFit
                        }
                    }

                    ColumnLayout {
                        id: info_preview

                        Text {
                            id: nickname
                            height: 25
                            text: qsTr("Nick O'Conor")
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
                            id: last_message_timestamp
                            text: "12:51"
                            font.pixelSize: font_size
                            horizontalAlignment: Text.AlignRight

                            Layout.alignment: Qt.AlignTop | Qt.AlignRight
                        }

                        Text {
                            id: message_amount
                            text: qsTr("3")
                            font.pixelSize: font_size
                            horizontalAlignment: Text.AlignRight

                            Layout.alignment: Qt.AlignBottom | Qt.AlignRight
                        }
                    }
                }
            }
        }
    }
}
