import QtQuick 2.12
import QtQuick.Controls 2.12

import "General"

Item {
    id: root

    property int itemHeight: height / 6
    readonly property string title: qsTr("Settings")

    Component.onCompleted: {
        console.log("Completed", Setting.distanceList, Setting.selectedDistance)

        selectDistance.setIndexByText(Setting.selectedDistance)

        selectWeapon.setIndexByText(Setting.selectedWeapon)

        selectDiscipline.setIndexByText(Setting.selectedDiscipline)

        selectCurrentUser.setIndexByText(Setting.currentUser)
    }

    Flickable{
        anchors.fill: parent


        Column{
            anchors{
                left: parent.left
                top: parent.top
                bottom: parent.bottom
            }

            ComboboxUnit {
                id: selectCurrentUser

                width: root.width
                height: itemHeight

                model: Backend.modelCurrentUser
                onEditFinished:{
                    Backend.addNewUser(text)
                    Setting.currentUser = text
                }
                onSelectionChanged: Setting.currentUser = text
            }

            ComboboxUnit {
                id: selectDistance

                width: root.width
                height: itemHeight

                text: qsTr("Distance")

                model: Setting.distanceList
                onEditFinished:{
                    if(model.indexOf(text) != -1)
                        return
                    var m = model;
                    m.push(text)
                    Setting.distanceList = m
                    Setting.selectedDistance = text
                    setIndexByModelText(Setting.distanceList, text)
                }

                onSelectionChanged: Setting.selectedDistance = text
            }

            ComboboxUnit {
                id: selectWeapon

                width: root.width
                height: itemHeight

                text: qsTr("Weapon")

                model: Setting.weaponList
                onEditFinished:{
                    if(model.indexOf(text) != -1)
                        return
                    var m = model;
                    m.push(text)
                    Setting.weaponList = m
                    Setting.selectedWeapon = text
                    setIndexByModelText(Setting.weaponList,text)
                }

                onSelectionChanged: Setting.selectedDistance = text
            }

            ComboboxUnit {
                id:selectDiscipline
                width: root.width
                height: itemHeight

                text: qsTr("Discipline")

                model: Setting.disciplineList
                onEditFinished: {
                    if(model.indexOf(text) != -1)
                        return
                    var m = model
                    m.push(text);

                    Setting.disciplineList = m
                    Setting.selectedDiscipline = text
                    setIndexByModelText(Setting.disciplineList,text)
                }

                onSelectionChanged: Setting.selectedDiscipline = text
            }
        }
    }

}
