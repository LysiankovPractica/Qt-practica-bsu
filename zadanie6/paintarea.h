#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QPoint>
#include <QVector>

struct Line {
    QPoint start;
    QPoint end;
};

class PaintArea : public QWidget
{
    Q_OBJECT

public:
    explicit PaintArea(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QVector<Line> lines;   // Нарисованные линии
    Line currentLine;      // Линия, которая рисуется сейчас
    bool drawing;          // Флаг рисования
};

#endif // PAINTAREA_H
