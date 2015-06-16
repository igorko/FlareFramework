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

void IconView::setActiveIcon(int icon)
{
    dynamic_cast<IconWidget*>(this->widget())->setIconNumber(icon);
    horizontalScrollBar()->setValue(ICON_SIZE * (icon % ICONS_IN_ROW) );
    verticalScrollBar()->setValue(ICON_SIZE * (icon / ICONS_IN_ROW) );
    this->widget()->update();
}

int IconView::getActiveIcon()
{
    return dynamic_cast<IconWidget*>(this->widget())->getIconNumber();
}

void IconView::appendIcon(QImage newIcon)
{
    IconWidget* widget = dynamic_cast<IconWidget*>(this->widget());

    widget->setNewIcon(newIcon);
    widget->requestIconAppend();
}
