#include "iconview.h"
#include <QPainter>
#include <QLabel>
#include <QMouseEvent>
#include <QScrollBar>

IconView::IconView(QWidget *parent) :
    QScrollArea(parent)
{
}

void IconView::init(const QString &path)
{
    QLabel *imageLabel = new QLabel;
    icons = QImage(path + "images/icons/icons.png");
    imageLabel->setPixmap(QPixmap::fromImage(icons));
    this->setWidget(imageLabel);
}

void IconView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.begin(viewport());
    painter.setPen(QPen(Qt::red));

    if(!selection.isNull())
    {
        drawSelection(painter, selection);
    }
    painter.end();
}

void IconView::mousePressEvent(QMouseEvent *event)
{
    if (event->modifiers() & Qt::AltModifier)
    {
        QPoint point = event->pos();
        if (point.x() >= 0 && point.x() <= icons.width() && point.y() >= 0 && point.y() <= icons.height())
        {
            selection = point;
            update();
        }
    }
    QWidget::mousePressEvent(event);
}

void IconView::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        updateSelection(event->pos().x(), event->pos().y());
    }
}

void IconView::updateSelection(int x, int y)
{
    QScrollBar* hBar = horizontalScrollBar();
    QScrollBar* vBar = verticalScrollBar();

    hBar->setValue(x);
    vBar->setValue(y);
}

void IconView::drawSelection(QPainter& painter, QPoint selection)
{
    QRect selectionRect = QRect(selection.x(), selection.y(), 32, 32);

    painter.drawRect(selectionRect);
}
