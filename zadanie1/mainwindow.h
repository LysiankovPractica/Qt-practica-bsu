#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onCalculate();

private:
    QWidget *centralWidget;
    QLineEdit *lineEdit;
    QPushButton *calcButton;
    QTableWidget *tableWidget;

    int sumOfDigits(int number);
};

#endif // MAINWINDOW_H
