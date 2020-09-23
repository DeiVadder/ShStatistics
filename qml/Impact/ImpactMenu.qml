import QtQuick 2.12

//Menu for Impact selection

/*
    * Quick selection -> Add Impact to DB
    * Expand Menu
    * //Eventually Camera symbol for Impact detection via camer
*/
/*Expanded Menu,
    * select like Settings page but read only
    * View of previous Impacts
*/
Rectangle {
    id: root

    color: "#80FFFFFF"

    border.color: "black"
    border.width:  1

    readonly property  int imageMargins: root.width / 10

    Rectangle{
        anchors{
            left: parent.left
            top: parent.top
            right: parent.horizontalCenter
            bottom: parent.bottom
            margins: parent.border.width
        }
        color: saveArea.pressed ? "lightgrey" : "transparent"
        Image {
            id: iconSave
            anchors.fill: parent
            anchors.margins: imageMargins
            fillMode: Image.PreserveAspectFit
            source: "qrc:/images/Buttons/SaveIcon.png"

        }
        MouseArea{
            id:saveArea
            anchors.fill: parent
            onClicked: {
                console.log("SaveClicked")
            }
        }

    }

    Rectangle{
        anchors{
            right: parent.right
            top: parent.top
            left: parent.horizontalCenter
            bottom: parent.bottom
            margins: parent.border.width
        }
        color: menuArea.pressed ? "lightgrey" : "transparent"

        Image {
            id: iconMenu
            anchors.fill:parent
            anchors.margins: imageMargins
            fillMode: Image.PreserveAspectFit
            source: "qrc:/images/Buttons/MenuIcon.png"

        }
        MouseArea{
            id:menuArea
            anchors.fill: parent
            onClicked: {
                console.log("MenuClicked")
            }
        }
    }

}
