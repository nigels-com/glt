#ifndef MAIN_DEF
#define MAIN_DEF

#include "ui_main.h"

class GlutWidget;

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private:
    GlutWidget *_glutWidget;
};
 
#endif
