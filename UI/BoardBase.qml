import QtQuick 2.0
import "model.js" as DummyModel

Canvas {
    property int cellSize:32

    property string bgrColorOuter: "#0066aa"
    property string bgrColorInner: "#0088ff"
    property string fCellColor: "#000000"
    property string fBlockColor: "#ff0000"
    property string regBlockColor: "#00ff00"
    property string selectedStrokeColor: "#ffff00"

    property var model

    property int cWidth: model? model.cWidth: 9
    property int cHeight: model? model.cHeight: 9
    width: cellSize * cWidth
    height: cellSize * cHeight

    property rect fField: model.finalField
    property rect fBlock: model.finalBlock
    property var blocks: model.GetBlocks
    property rect currentBlock: model.currentBlock

    //Component.onCompleted: if(model){model.cellSize = cellSize;}
    onCellSizeChanged: model.cellSize = cellSize
    onFFieldChanged: requestPaint()
    onFBlockChanged: requestPaint()
    onBlocksChanged: requestPaint()
    onCurrentBlockChanged: requestPaint()

    Component.onCompleted:  {if(!model)model = new DummyModel.Model(); model.cellSize = cellSize;}
    onModelChanged: if(!model) model = new DummyModel.Model();

    onPaint:{
        var ctx = getContext("2d");
//background
        ctx.fillStyle = bgrColorOuter;
        ctx.rect(0,0,width,height);
        ctx.fill();
        ctx.beginPath();
        ctx.fillStyle = bgrColorInner;
        ctx.rect(cellSize, cellSize, width - cellSize*2, height - cellSize*2);
        ctx.fill();
//stroke
        ctx.strokeStyle = "#000000";
        ctx.lineWidth = 6;
//fField
        ctx.beginPath();
        ctx.fillStyle=fCellColor;
        ctx.rect(fField.x, fField.y, fField.width, fField.height);
        ctx.fill();
//fBlock
        ctx.beginPath();
        ctx.fillStyle = fBlockColor;
        ctx.rect(fBlock.x, fBlock.y, fBlock.width, fBlock.height);
        ctx.fill(); ctx.stroke();
//regularBlocks
        ctx.beginPath();
        ctx.fillStyle = regBlockColor;
        for(var i=0; i<blocks.length; ++i)
            ctx.rect(blocks[i].x, blocks[i].y, blocks[i].width, blocks[i].height);
        ctx.fill(); ctx.stroke();
//currentBlock
        ctx.beginPath()
        ctx.strokeStyle = selectedStrokeColor;
        if(currentBlock)
            ctx.rect(currentBlock.x, currentBlock.y, currentBlock.width, currentBlock.height);
        ctx.stroke();
//ctx.save();
//ctx.restore();
    }
    function ctins(rect, x, y){
        return x>=rect.x && x<rect.x+rect.width && y>=rect.y && y<rect.y+rect.height;
    }
    function loadBoard(fullPath){
        model.loadBoard(fullPath);
    }
    MouseArea{
        anchors.fill: parent
        onPressed: model.mousePressed(mouseX, mouseY, mouse.modifiers == Qt.ShiftModifier)
        onReleased: model.mouseReleased()
        onPositionChanged: model.mouseMoved(mouseX, mouseY)
    }
}

