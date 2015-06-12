#include "iconwidget.h"
#include <QPainter>
#include <QMouseEvent>

IconWidget::IconWidget(QWidget *parent) :
    QLabel(parent), iconNumber(0)
{
}

void IconWidget::setIconNumber(int icon)
{
    iconNumber = icon;
    selection = QPoint(icon % ICONS_IN_ROW, icon / ICONS_IN_ROW);
}

int IconWidget::getIconNumber()
{
    return iconNumber;
}

void IconWidget::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    QPainter painter(this);
    painter.setPen(QPen(Qt::green));

    if(selection.x() >= 0 && selection.y() >= 0)
    {
        drawSelection(painter, selection);
    }
}

void IconWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->modifiers() & Qt::AltModifier)
    {
        QPoint point = event->pos();
        if (point.x() >= 0 && point.x() <= this->width() && point.y() >= 0 && point.y() <= this->height())
        {
            selection = QPoint(point.x() / ICON_SIZE, point.y() / ICON_SIZE);
            iconNumber = ICONS_IN_ROW * selection.y() + selection.x();
            update();
        }
    }
    QWidget::mousePressEvent(event);
}

void IconWidget::drawSelection(QPainter& painter, QPoint selection)
{
    QRect selectionRect = QRect(ICON_SIZE * selection.x(), ICON_SIZE * selection.y(), ICON_SIZE, ICON_SIZE);

    painter.drawRect(selectionRect);
}
