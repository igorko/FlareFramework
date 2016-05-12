#include "iconwidget.h"

#include <QPainter>
#include <QMouseEvent>

IconWidget::IconWidget(QWidget *parent) :
    QLabel(parent), iconNumber(0), iconPlacingRequested(false), iconsEdited(false), iconsInRow(0)
{
}

void IconWidget::init()
{
    iconsInRow = pixmap()->width() / ICON_SIZE;
}

void IconWidget::setIconNumber(int icon)
{
    iconNumber = icon;
    selection = QPoint(icon % iconsInRow, icon / iconsInRow);
}

int IconWidget::getIconNumber()
{
    return iconNumber;
}

void IconWidget::requestIconAppend(QImage icon)
{
    iconPlacingRequested = true;
    newIcon = icon;
}

bool IconWidget::iconsWereEdited()
{
    return iconsEdited;
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
    if (iconPlacingRequested && event->button() == Qt::LeftButton)
    {
        QPoint point = event->pos();
        if (point.x() >= 0 && point.x() <= this->width() && point.y() >= 0 && point.y() <= this->height())
        {
            QImage icons = pixmap()->toImage();
            QPainter p(&icons);
            p.setCompositionMode(QPainter::CompositionMode_Source);

            QPoint selection = QPoint((point.x() / ICON_SIZE) * ICON_SIZE,
                                      (point.y() / ICON_SIZE) * ICON_SIZE);

            p.drawImage(selection, newIcon);
            setPixmap(QPixmap::fromImage(icons));

            iconsEdited = true;
            iconPlacingRequested = false;
            emit iconPlaced();
        }
    }
    else if (event->button() == Qt::RightButton)
    {
        iconPlacingRequested = false;
        emit iconSkipped();
    }

    if (event->modifiers() & Qt::AltModifier)
    {
        QPoint point = event->pos();
        if (point.x() >= 0 && point.x() <= this->width() && point.y() >= 0 && point.y() <= this->height())
        {
            selection = QPoint(point.x() / ICON_SIZE, point.y() / ICON_SIZE);
            iconNumber = iconsInRow * selection.y() + selection.x();
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
