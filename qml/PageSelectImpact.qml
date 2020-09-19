import QtQuick 2.12

Rectangle {
    id:root
    //when width -> height
    readonly property bool widthIsGreater: width > height

    color: "#AAAAAAAA"

    MouseArea{
        id: mAreaOutside
        anchors.fill: parent
        onClicked: console.log("clicked")
    }

    Image {
        id: targetImage
        //When  with is greater position on the left side and use height as Max
        //When height is greater position on top and use width as max

        source: "qrc:/images/PistolTarget25m.jpg"
        antialiasing: true
        mipmap: true
        fillMode: Image.PreserveAspectCrop
        horizontalAlignment: Image.AlignHCenter
        verticalAlignment: Image.AlignVCenter

        readonly property int itemWidth: widthIsGreater ? root.height : root.width
        readonly property int centerPos: width /2
        width: itemWidth
        height: itemWidth
        anchors.centerIn: parent
        anchors.margins: 0

        Item {
            id: overLayPoint
            anchors{
                right: parent.right
                top: parent.top
            }

            height: parent.height / 10
            width: parent.width / 5

            Text {
                id: idPoint
                anchors{
                    left: parent.left
                    top: parent.top
                    bottom: undefined
                    right: parent.right
                }

                height: contentHeight * 1.1

                property double points: 0
                text: qsTr("Point :%1").arg(points)
            }
        }

        Image{
            id:impactImage
            width: height
            height: parent.height /10

            source: "qrc:/images/crosshairs.png"

            property bool initialPress: false

            x: initialPress ? mAreaSelectImpact.mouseX-width / 2 : -width
            y: initialPress ? mAreaSelectImpact.mouseY-height / 2 : -height

            onXChanged: centerToPoint()
            onYChanged: centerToPoint()

            function partial10Points() {
                //radius10Points = 100 %
                if(radius < radius10Points) {
                    var rad = radius10Points * radius10Points;
                    var xSq = (impactImage.centerPosX - targetImage.centerPos) * (impactImage.centerPosX - targetImage.centerPos)
                    var ySq = (impactImage.centerPosY - targetImage.centerPos) * (impactImage.centerPosY - targetImage.centerPos)
                    return  1 - (xSq + ySq) / rad;
                }
                return 0
            }

            function isInsideCircle(radius){
                //(x - center_x)^2 + (y - center_y)^2 < radius^2
                var xSq = (impactImage.centerPosX - targetImage.centerPos) * (impactImage.centerPosX - targetImage.centerPos)
                var ySq = (impactImage.centerPosY - targetImage.centerPos) * (impactImage.centerPosY - targetImage.centerPos)
                var rSq = radius * radius;
                return  (xSq + ySq <= rSq)
            }

            function centerToPoint (){
                for(var i = 1; i < 11; i ++){
                    if(isInsideCircle(radius10Points * i)) {
                        idPoint.points = (11 - i)
                        if(i === 1)
                            idPoint.points = idPoint.points + partial10Points()
                        return
                    }
                }
                idPoint.points = 0
            }

            //original heigh 1135, raidus 10 = 108  -> 10800 / 1135
            readonly property int centerPos: width /2
            readonly property int centerPosX:x + centerPos
            readonly property int centerPosY: y + centerPos

            readonly property double factor: 55/*110*/ / 1135
            readonly property int radius10Points: parent.height * factor
        }

        MouseArea{
            id: mAreaSelectImpact
            anchors.fill: parent
            onPressed: impactImage.initialPress = true
            onReleased: impactImage.centerToPoint()
        }
    }
}
