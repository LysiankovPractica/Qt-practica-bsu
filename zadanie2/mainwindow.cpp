#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

QString MainWindow::processString(const QString &input) {
    QStringList words = input.split(QRegularExpression("[\\s,.:;?!]+")); // Разделители
    QStringList digits;
    QStringList others;

    for (const QString &word : words) {
        if (word.isEmpty()) continue; // Пропустить пустые слова
        if (word.contains(QRegularExpression("^[0-9]+$"))) {
            digits.append(word);
        } else {
            others.append(word);
        }
    }

    // Объединяем слова: сначала цифры, затем остальные
    QString result = (digits + others).join(" ");
    return result;
}

void MainWindow::on_pushButton_clicked() {
    QString input = ui->inputLineEdit->text(); // Чтение текста из поля ввода
    QString output = processString(input); // Обработка строки
    ui->outputLabel->setText(output); // Вывод результата на экран
}




