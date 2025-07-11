#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Простые делители");
}

MainWindow::~MainWindow() {
    delete ui;
}

QVector<int> MainWindow::getPrimeFactors(int number) {
    QVector<int> factors;
    for (int i = 2; i <= number; ++i) {
        while (number % i == 0) {
            factors.append(i);
            number /= i;
        }
    }
    return factors;
}

void MainWindow::on_calculateButton_clicked() {
    bool ok;
    int number = ui->lineEdit->text().toInt(&ok);

    if (!ok || number <= 0 || number > 10000) {
        QMessageBox::warning(this, "Ошибочный ввод", "Введите число от 1 до 10000.");
        return;
    }

    QVector<int> factors = getPrimeFactors(number);
    ui->tableWidget->setRowCount(factors.size());

    for (int i = 0; i < factors.size(); ++i) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(factors[i])));
    }
}
