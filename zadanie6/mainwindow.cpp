#include "mainwindow.h"
#include "paintarea.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Простейший Векторный Редактор");
    resize(800, 600);

    PaintArea *paintArea = new PaintArea(this);
    setCentralWidget(paintArea);
}
