import QtQuick 2.15

Rectangle {
    width: 360
    height: 360
    color: "lightsteelblue"

    ListModel {
        id: messages

        ListElement {
            peer_nickname: "Nikolas (Nick)"
            avatar_source: "image://photos/1"
            message_text: "Hello, my name is Nick, nice to meet you"
            message_timestamp: "12:51"
        }

        ListElement {
            avatar_nickname: ""
            avatar_source: "image://photos/3"
            message_text: "Hello, my name is Open AI, nice to meet you too"
            message_timestamp: "12:52"
        }
    }

    ListView {
        id: view

        anchors.margins: 10
        anchors.fill: parent
        spacing: 10
        model: messages

        delegate: Rectangle {
            width: view.width
            height: 80
            radius: 10

            Image {
                id: peer_avatar

                width: 50
                height: parent.height

                source: model.avatar_source

                sourceSize.width: width
                sourceSize.height: height
                fillMode: Image.PreserveAspectFit
            }

            Text {
                id: peer_nickname

                anchors.fill: parent
                x: view.x + peer_avatar.width
                horizontalAlignment: Text.AlignTop
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                wrapMode: Text.Wrap
                renderType: Text.NativeRendering
                text: model.peer_nickname
            }

            Text {
                id: message_text

                anchors.fill: parent
                x: view.x + peer_avatar.width
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
                wrapMode: Text.Wrap
                renderType: Text.NativeRendering
                text: model.message_text
            }

            Text {
                id: message_timestamp

                anchors.fill: parent
                x: view.x + peer_avatar.width
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignBottom
                elide: Text.ElideRight
                wrapMode: Text.Wrap
                renderType: Text.NativeRendering
                text: model.message_timestamp
            }
        }
    }
}

