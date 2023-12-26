import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.14

// Rectangle.Row.Image.source

Rectangle {
    property string avatarSource: "image://avatars/1"
    property string peer: "2048"

    width: 400
    height: 100

    Row {
        id: row
        width: parent.width
        height: parent.height

        Image {
            id: avatar_preview
            width: 100
            height: parent.height
            source: avatarSource
            sourceSize.width: 100
            sourceSize.height: 100
            fillMode: Image.PreserveAspectFit
        }

        Column {
            id: info_preview
            width: 250
            height: parent.height

            Text {
                id: nickname
                width: parent.width
                height: 25
                text: qsTr("Nick O'Conor")
                font.pixelSize: 12
                font.bold: true
            }

            Text {
                id: message
                width: parent.width
                text: qsTr("Hello, I would like to say you ...")
                font.pixelSize: 12
            }
        }

        Column {
            id: extra_info_preview
            x: 350
            width: 50
            height: parent.height

            Text {
                id: last_message_timestamp
                width: parent.width
                text: "12:51"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignRight
            }

            Text {
                id: message_amount
                width: parent.width
                text: qsTr("3")
                font.pixelSize: 12
                horizontalAlignment: Text.AlignRight
            }
        }
    }
}
