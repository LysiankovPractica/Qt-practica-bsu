#include "mainwindow.h"
#include <QIntValidator>
#include <QHeaderView>
#include <QMessageBox>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText("Введите натуральное число");
    lineEdit->setValidator(new QIntValidator(1, 1000000000, this)); // Ограничение на ввод

    calcButton = new QPushButton("Выполнить", this);

    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(2);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Число" << "Сумма цифр");
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(lineEdit);
    layout->addWidget(calcButton);
    layout->addWidget(tableWidget);

    connect(calcButton, &QPushButton::clicked, this, &MainWindow::onCalculate);

    setWindowTitle("Поиск чисел по условию");
}

int MainWindow::sumOfDigits(int number)
{
    int sum = 0;
    while (number > 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

void MainWindow::onCalculate()
{
    tableWidget->setRowCount(0); // Очистка таблицы

    QString text = lineEdit->text().trimmed();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите число.");
        return;
    }

    bool ok;
    int N = text.toInt(&ok);
    if (!ok || N <= 0) {
        QMessageBox::warning(this, "Ошибка", "Введите корректное натуральное число.");
        return;
    }

    // Перебираем числа от 1 до N
    for (int x = 1; x <= N; ++x) {
        int s = sumOfDigits(x);

        // Проверяем степени k: s^k == N
        // k >=1, s^k <= N
        if (s <= 1) {
            // Если s=1, то только k=log(N) проверяем — но 1^k всегда 1,
            // значит подходит только если N==1
            if (s == 1 && N == 1) {
                int rowCount = tableWidget->rowCount();
                tableWidget->insertRow(rowCount);
                tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(x)));
                tableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString::number(s)));
            }
            continue;
        }

        // Ищем k: s^k == N
        // k максимальное ~ log(N)/log(s)
        int maxK = static_cast<int>(std::log(N) / std::log(s)) + 1;

        bool found = false;
        for (int k = 1; k <= maxK; ++k) {
            double powVal = std::pow(s, k);
            if (std::abs(powVal - N) < 1e-9) { // Проверка с плавающей точкой
                found = true;
                break;
            }
            if (powVal > N)
                break;
        }

        if (found) {
            int rowCount = tableWidget->rowCount();
            tableWidget->insertRow(rowCount);
            tableWidget->setItem(rowCount, 0, new QTableWidgetItem(QString::number(x)));
            tableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString::number(s)));
        }
    }

    if (tableWidget->rowCount() == 0) {
        QMessageBox::information(this, "Результат", "Подходящих чисел не найдено.");
    }
}

