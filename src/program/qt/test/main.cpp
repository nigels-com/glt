#include "main.h"

#include "GlutMasterWidget.h"

#include "neverlandviewer.h"

#include <glutm/glut.h>

#include <QApplication>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent)
:   _glutMasterWidget(new GlutMasterWidget())
{
    setupUi(this);
    setStatusBar(NULL);
//    _stack->addWidget(_glutWidget);
//    _glutWidget->show();
    setCentralWidget(_glutMasterWidget);
//    _glutWidget->showMaximized();
//    _glutWidget->show();
    NeverlandWindow *neverland = new NeverlandWindow();
    _glutMasterWidget->bind(neverland);
}
 
int main(int argc, char *argv[])
{
    glutInit(&argc,argv);

    //

    QApplication app(argc, argv);
    MainWindow *window = new MainWindow();
    window->setWindowTitle("QtTest");
    window->setWindowState(window->windowState() | Qt::WindowFullScreen);
    window->show();
    return app.exec();
}
