import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.0

Item {
    id: debug_area

    width: parent.width
    height: parent.height

    ColumnLayout {
        RowLayout {
            Text {
                id: choose_peer
                text: qsTr("Choose peer")
            }

            ComboBox {
                id: peer_ids
                model: ["2048", "2049", "2050"]
            }
        }

        RowLayout {
            Text {
                text: qsTr("Chat update time")
            }

            TextField {
                id: timePicker

                verticalAlignment: TextInput.AlignVCenter
                horizontalAlignment: TextInput.AlignHCenter

                text: "00:00:01"
                inputMask: "00:00:00;_"

                inputMethodHints: Qt.ImhDigitsOnly
            }
        }
    }
}
