import QtQuick 2.0
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.0

Rectangle {
    width: 640
    height: 50
    visible: true
    color: "#060101"

    RowLayout {
        id: rowLayout
        anchors.fill: parent
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        spacing: 35
        layoutDirection: Qt.LeftToRight
        antialiasing: false

        Label {
            id: label
            color: "#d8d8d8"
            text: qsTr("   Channel")
        }

        Label {
            id: label1
            color: "#cccccc"
            text: qsTr("Start/Stop working")
        }

        Label {
            id: label3
            color: "#dcdcdc"
            text: qsTr("Set range (0-3)")
        }

        Item {
            id: item1
            width: 180
            height: 50
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Label {
            id: label5
            color: "#cecece"
            text: qsTr("Status")
            leftPadding: 0
            topInset: 0
        }

        Label {
            id: label6
            color: "#cbcbcb"
            text: qsTr("Last Result")
            topPadding: 0
        }

    }


}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}D{i:1}
}
##^##*/
