import QtQuick 2.1

Canvas {
    width: 256
    height: 256
    property int spaceX:32
    property int spaceY:32
    property string color: "#000000"
    property int lineWidth: 1
    onPaint:{
        var ctx = getContext("2d");
        ctx.strokeStyle = color;
        ctx.lineWidth = lineWidth;
        for(var x=0; x<=width; x+=spaceX){
            ctx.moveTo(x,0)
            ctx.lineTo(x,height);
        }
        for(var y=0; y<=height; y+=spaceY){
            ctx.moveTo(0,y);
            ctx.lineTo(width,y);
        }
        ctx.stroke();
    }
    onSpaceXChanged: requestPaint()
    onSpaceYChanged: requestPaint()
}
