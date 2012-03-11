// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 300
    height: 400

    ListView {
        id: list_view1
        x: 0
        y: 65
        width: 300
        height: 235
        delegate: Item {
            x: 5
            height: 40
            Row {
                id: row1
                spacing: 10
                Rectangle {
                    width: 40
                    height: 40
                    color: colorCode
                }

                Text {
                    text: name
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                }
            }
        }
        model: ListModel {
            ListElement {
                name: "Grey"
                colorCode: "grey"
            }

            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }
        }

        Row {
            id: row2
            x: 0
            y: 234
            width: 300
            height: 101

            BorderImage {
                id: border_image1
                x: 5
                y: 1
                width: 100
                height: 100
                source: "qrc:/qtquickplugin/images/template_image.png"
            }

            BorderImage {
                id: border_image2
                x: 119
                y: 1
                width: 100
                height: 100
                source: "qrc:/qtquickplugin/images/template_image.png"
            }

            BorderImage {
                id: border_image3
                x: 211
                y: 1
                width: 100
                height: 100
                source: "qrc:/qtquickplugin/images/template_image.png"
            }
        }
    }
    states: [
        State {
            name: "State1"
        }
    ]
}
