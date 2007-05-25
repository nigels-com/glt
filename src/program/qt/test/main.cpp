#include "main.h"

#include "GlutWidget.h"

#include <QApplication>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent)
:   _glutWidget(new GlutWidget())
{
    setupUi(this);
    setStatusBar(NULL);
//    _stack->addWidget(_glutWidget);
//    _glutWidget->show();
    setCentralWidget(_glutWidget);
//    _glutWidget->showMaximized();
//    _glutWidget->show();
}
 
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow *window = new MainWindow();
    window->show();
    return app.exec();
}
