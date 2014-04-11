import QtQuick 2.0
import QtQuick.Controls 1.0

Row{
    width: editor.width + button.width + solver.width

    BoardEdit{
        id: editor
    }
    Button{
        id: button
        text: "->\n->\n->"
        height: editor.height
        onClicked: {
            converter.copyBoard();
        }
    }
    BoardSolve{
        id: solver
    }
    Component.onCompleted: solver.setDepth(20)
}
