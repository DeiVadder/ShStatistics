import QtQuick 2.12
import QtQuick.Controls 2.12

Item{
    id: root

    property alias text: description.text
    property alias model: cBox.model
    property alias currentIndex: cBox.currentIndex
    property alias currentText: cBox.currentText
    property alias editable: cBox.editable
    signal editFinished(var text)
    signal selectionChanged(var text)

    function setIndexByText(text) {
        var index = cBox.model.indexOf(text)
        if(index >= 0)
            cBox.currentIndex = index
        else
            cBox.currentIndex = 0
        cBox.initialized = true
    }
    function setIndexByModelText(model, text) {
        var index = model.indexOf(text)
        console.log(model, text, index)
        console.log(cBox.model)
        if(index >= 0)
            setCurrentINdexDelayed.currentIndex = index
        else
            setCurrentINdexDelayed.currentIndex = 0
        cBox.initialized = true
        setCurrentINdexDelayed.start()
    }

    Timer {
        id:setCurrentINdexDelayed
        interval: 10
        repeat: false
        running: false
        property int currentIndex: 0
        onTriggered: cBox.currentIndex = currentIndex
    }

    Text {
        id:description
        anchors{
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }
        width:  parent.width / 3
        
        text: qsTr("Current User:")
        padding: 20
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }
    
    Rectangle{
        id: frameCombobox
        anchors{
            left: description.right
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            margins: 20
        }
        border.color: "lightgrey"
        border.width: 1
        ComboBox {
            id:cBox
            anchors.fill: parent
            editable: true
            model: ["a", "b", "c"]

            leftPadding: 5

            property bool initialized: false
            onCurrentIndexChanged:{
                if(currentIndex >= 0 && initialized)
                    root.selectionChanged(model[currentIndex])
            }

            contentItem: TextInput{
                readOnly: !cBox.editable
                text: cBox.displayText

                font: cBox.font

                onActiveFocusChanged: if(activeFocus) selectAll()

                horizontalAlignment: TextInput.AlignLeft
                verticalAlignment: TextInput.AlignVCenter
                padding: cBox.padding

                onAccepted: {
                    console.log("TextInput", currentText, ":", displayText)
                    root.editFinished(displayText)
                    root.forceActiveFocus()
                }
            }
        }
    }
}
