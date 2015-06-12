#include "iconview.h"
#include "iconwidget.h"
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
    IconWidget *imageLabel = new IconWidget;
    icons = QImage(path + "images/icons/icons.png");
    imageLabel->setPixmap(QPixmap::fromImage(icons));
    this->setWidget(imageLabel);
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
