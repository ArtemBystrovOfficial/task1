import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.0

Rectangle {


    id: main
    //implicitWidth: 640
    width: 640
    height: 50
    //minimumHeight: 50
    //maximumHeight: 50
    visible: true
    color: "#1c1c1c"

    property int channel: 0;

    RowLayout {
        id: rowLayout
        anchors.fill: parent
        spacing: 20

        Button {
            signal click(int channel)
            onClicked: click(main.channel)

            objectName: "start"
            id: start
            implicitWidth: 75
            height: 29
            visible: true
            text: qsTr("Start")
            smooth: true
            clip: false
            display: AbstractButton.TextBesideIcon
            checkable: false
            highlighted: false
            flat: false
        }

        Button {
            signal click(int channel)
            onClicked: click(main.channel)

            objectName: "stop"
            id: stop
            implicitWidth: 75
            height: 29
            text: qsTr("Stop")
        }

        Button {
            signal click(int channel,int range)
            onClicked: click(main.channel,input.text)

            objectName: "set_range"
            id: set_range
            implicitWidth: 75
            height: 29
            text: qsTr("Set Range")
        }

        Label {

            id: label
            color: "#ffffff"
            text: qsTr("↔")
            font.pointSize: 20
        }


        Rectangle{

                width: 80
                height: 28
                border.color: "#ffffff"
                color: "#1c1c1c"
                TextInput {
                    id: input
                    color: "#ffffff"; text: "0"; selectionColor: "green"
                    font.pixelSize: 16; font.bold: true
                    width: parent.width-16
                    maximumLength: 16
                    anchors.centerIn: parent
                    focus: true
                }
             }


        Button {
            signal click(int channel)
            onClicked: click(main.channel)

            objectName: "get_result"
            id: get_result
            implicitWidth: 75
            height: 29
            text: qsTr("Get result")
        }

        Label {

            objectName: "status"
            id: status
            //implicitWidth: 110
            width: 50
            height: 30
            color: "#efefef"
            text: qsTr("Status")
        }

        Label {

            objectName: "result"
            id: result
            //implicitWidth: 50
            width: 40
            height: 20
            color: "#ffffff"
            text: qsTr("0    ")
        }

    }
}
