#include "iconview.h"

#include <QPainter>
#include <QLabel>
#include <QMouseEvent>
#include <QScrollBar>

#include "iconwidget.h"

IconView::IconView(QWidget *parent) :
    QScrollArea(parent)
{
}

void IconView::init(const QString &path)
{
    IconWidget *imageLabel = new IconWidget;
    connect(imageLabel, SIGNAL(iconPlaced()), this, SIGNAL(iconPlaced()));
    connect(imageLabel, SIGNAL(iconSkipped()), this, SIGNAL(iconSkipped()));

    icons = QPixmap(path + "images/icons/icons.png");
    imageLabel->setPixmap(icons);
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

    widget->requestIconAppend(newIcon);
}

void IconView::saveIcons(const QString& path)
{
    IconWidget* widget = dynamic_cast<IconWidget*>(this->widget());

    if (widget->iconsWereEdited())
    {
        QImage icons = widget->pixmap()->toImage();
        icons.save(path);
    }
}
