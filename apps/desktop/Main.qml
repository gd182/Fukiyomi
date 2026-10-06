import QtQuick

Window {
    required property ReaderController controller
    
    width: 800
    height: 1000
    visible: true
    title: "Fukiyomi"

    Image {
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        source: "image://pages/" + controller.currentIndex
        cache: false
    }

    Rectangle {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 50
        color: "#80000000"
        Text {
            color: "white"
            anchors.centerIn: parent
            text: (controller.currentIndex + 1) + " / " + controller.pageCount
        }
    }

    Item {
        anchors.fill: parent
        focus: true
        Keys.onLeftPressed: controller.previous()
        Keys.onRightPressed: controller.next()
    }
}