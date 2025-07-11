#include "paintarea.h"
#include <QPainter>
#include <QMouseEvent>

PaintArea::PaintArea(QWidget *parent)
    : QWidget(parent), drawing(false)
{
    setAttribute(Qt::WA_StaticContents);
    setMouseTracking(true);
}

void PaintArea::paintEvent(QPaintEvent * /*event*/)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), Qt::white);

    QPen pen(Qt::black, 2);
    painter.setPen(pen);

    // Рисуем все сохранённые линии
    for (const Line &line : lines) {
        painter.drawLine(line.start, line.end);
    }

    // Рисуем текущую линию, если идет рисование
    if (drawing) {
        painter.drawLine(currentLine.start, currentLine.end);
    }
}

void PaintArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        currentLine.start = event->pos();
        currentLine.end = event->pos();
        update();
    }
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    if (drawing) {
        currentLine.end = event->pos();
        update();
    }
}

void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        currentLine.end = event->pos();
        lines.append(currentLine);
        drawing = false;
        update();
    }
}
