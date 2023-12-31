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
