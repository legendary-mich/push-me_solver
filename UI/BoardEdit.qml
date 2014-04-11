import QtQuick 2.0
import QtQuick.Controls 1.0

Column {
    function getModel(){
        return board.model;
    }
    function loadBoard(){board.model.loadBoard("");}
    BoardBase{
        id: board
        model: boardEdit
        function newBoard(){model.newBoard();}
        function saveBoard(fullPath){model.saveBoard(fullPath);}
        GridLayer{
            anchors.fill: parent
            spaceX: parent.cellSize
            spaceY: parent.cellSize
        }
    }
    Row{
        x: board.x
        width: board.width
        Button{
            text: "New"
            width: parent.width ///2
            onClicked: board.newBoard();
        }
    }
    Text{
        text: "Hold SHIFT to control the RED BLOCK"
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
