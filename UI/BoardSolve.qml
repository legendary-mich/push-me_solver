import QtQuick 2.0
import QtQuick.Controls 1.0

Row{
    function setDepth(value){
        slider.value = value;
    }

Column {
    function getModel(b){
        return bp.model;
    }
        BoardBase{
            id: bp
            model: boardSolve
            function solve(){
                model.solve();
            }
            function undo(){
                model.undo();
            }
            function forward(){
                model.forward();
            }
//            Text{
//                anchors.centerIn: parent
//                text: bp.model.message
//            }
        }

    Button{
        text: "Solve"
        width: bp.width
        enabled: bp.model.solveEnabled
        onClicked: bp.solve();
    }
    Row{
        Button{
            text: "Undo"
            width: bp.width/2
            enabled: bp.model.undoEnabled
            onClicked: bp.undo();
        }
        Button{
            text: "Forward"
            width: bp.width/2
            enabled: bp.model.forwardEnabled
            onClicked: bp.forward();
        }
    }
}
    Column{
        width: 50
        height: bp.height
        Text{
            id: depth
            anchors.horizontalCenter: parent.horizontalCenter
            text: "depth " + slider.value
        }
        Slider {
            id: slider
            anchors.horizontalCenter: parent.horizontalCenter
            height: parent.height - depth.height
            orientation: 0
            tickmarksEnabled: true
            stepSize: 1
            minimumValue: 1
            maximumValue: 50
            value: bp.model.depth
            onValueChanged: if(bp.model)bp.model.depth = value;
        }

    }
}
