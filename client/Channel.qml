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


        Label {
            id: channel
            background: Rectangle
            {
                width:30
                height:20

                border.color: "#dddddd"
                color: "black"
            }

            objectName: "channel"
            color: "#ffffff"
            text: qsTr("    0")
        }

        Button {
            signal click(int channel)

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: parent.click(main.channel)
            }

            background: Rectangle {
                border.color: "#007306"
                color:  mouseArea.containsMouse ? "#555555" : "#333333"
            }


            objectName: "start"
            id: start
            implicitWidth: 100
            height: 40
            visible: true
            text: qsTr("<font color='#fefefe'> Start </font>")
            smooth: true
            clip: false
            display: AbstractButton.TextBesideIcon
            checkable: false
            highlighted: true
            flat: true
        }

        Button {
            signal click(int channel)

            MouseArea {
                id: mouseArea2
                anchors.fill: parent
                hoverEnabled: true
                onClicked: parent.click(main.channel)
            }

            background: Rectangle {
                border.color: "#949c00"
                color:  mouseArea2.containsMouse ? "#555555" : "#333333"
            }

            objectName: "stop"
            id: stop
            implicitWidth: 75
            height: 29
            text: qsTr("<font color='#fefefe'> Stop </font>")
            highlighted: true
            flat: true
        }


        Button {
            signal click(int channel,int range)

            MouseArea {
                id: mouseArea3
                anchors.fill: parent
                hoverEnabled: true
                onClicked: parent.click(main.channel,input.text)
            }

            background: Rectangle {
                border.color: "#68007d"
                color:  mouseArea3.containsMouse ? "#555555" : "#333333"
            }

            objectName: "set_range"
            id: set_range
            implicitWidth: 100
            height: 40
            text: qsTr("<font color='#fefefe'> Set Range </font>")
            highlighted: true
            flat: true
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

            MouseArea {
                id: mouseArea4
                anchors.fill: parent
                hoverEnabled: true
                onClicked: parent.click(main.channel)
            }

            background: Rectangle {
                border.color: "#9c0270"
                color:  mouseArea4.containsMouse ? "#555555" : "#333333"
            }


            objectName: "get_result"
            id: get_result
            implicitWidth: 100
            height: 40
            text: qsTr("<font color='#fefefe'> Get result </font>")
            highlighted: true
            flat: true
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
