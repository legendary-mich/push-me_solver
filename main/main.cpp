#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

//#include "ViewModel/vmboardbase.h"
#include "ViewModel/vmboardedit.h"
#include "ViewModel/vmboardsolve.h"
#include "ViewModel/vmboardconverter.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QtQuick2ApplicationViewer viewer;

    //VMBoardBase boardBase;
    VMBoardEdit boardEdit;
    VMBoardSolve boardSolve;
    VMBoardConverter boardConverter;
    boardConverter.fromBoard = &boardEdit;
    boardConverter.toBoard = &boardSolve;
    //viewer.rootContext()->setContextProperty("boardBase", &boardBase);
    viewer.rootContext()->setContextProperty("boardEdit", &boardEdit);
    viewer.rootContext()->setContextProperty("boardSolve", &boardSolve);
    viewer.rootContext()->setContextProperty("converter", &boardConverter);

    viewer.setMainQmlFile(QStringLiteral("qml/UI/Main.qml"));
    viewer.setTitle("\"Push Me\" Solver");
    viewer.showExpanded();

    return app.exec();
}
