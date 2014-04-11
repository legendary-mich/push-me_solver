.pragma library

function Model() {
    this.cellSize = 32;
    this.cWidth = 9;
    this.cHeight = 9;
    this.finalField = Qt.rect(0,0,this.cellSize,this.cellSize);
    this.finalBlock = Qt.rect(this.cellSize,this.cellSize,this.cellSize,this.cellSize);
    this.currentBlock = Qt.rect(0,0,0,0);
    this.GetBlocks = [
             Qt.rect(this.cellSize*2,this.cellSize*2,this.cellSize*2,this.cellSize),
             Qt.rect(this.cellSize*2,this.cellSize*4,this.cellSize,this.cellSize*2)];

    this.solveEnabled = false;
    this.undoEnabled = false;
    this.forwardEnabled = false;
    this.depth = 10;
}
Model.prototype = {
    mousePressed: function(x, y, modifier){},
    mouseReleased: function(){},
    mouseMoved: function(x, y){},
    newBoard: function(){},
    loadBoard: function(fullPath){},
    saveBoard: function(fullPath){},
    solve: function(){},
    undo: function(){},
    forward: function(){}
}
