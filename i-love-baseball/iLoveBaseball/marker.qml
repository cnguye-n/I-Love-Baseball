import QtQuick 2.0
import QtLocation 5.3
import QtQuick.Controls 2.0

MapQuickItem {

    id: marker
    anchorPoint.x: marker.width / 4
    anchorPoint.y: marker.height
    property string labelText
    sourceItem: Item
    {

        Image {
            id: icon
            source: "qrc:///images/map-marker-icon.png"
            sourceSize.width: 22
            sourceSize.height: 22
        }

        Rectangle
        {
            id: tag
            anchors.centerIn: label
            width: label.width + 4
            height: label.height + 2
            color: "black"
        }

        Label
        {
            id: label
            anchors.centerIn: parent
            anchors.horizontalCenterOffset: 20
            anchors.verticalCenterOffset: -12
            font.pixelSize: 11
            text: labelText
            color: "white"
        }
    }


}
