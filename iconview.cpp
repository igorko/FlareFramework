#include "iconview.h"

#include <QPainter>
#include <QLabel>
#include <QMouseEvent>
#include <QScrollBar>
#include <QDir>

#include "iconwidget.h"

IconView::IconView(QWidget *parent) :
    QScrollArea(parent), iconsInRow(0)
{
}

void IconView::init(const QString &path)
{
    IconWidget *imageLabel = new IconWidget;
    connect(imageLabel, SIGNAL(iconPlaced()), this, SIGNAL(iconPlaced()));
    connect(imageLabel, SIGNAL(iconSkipped()), this, SIGNAL(iconSkipped()));

    QDir iconsDir(path + "images/icons/");
    QStringList files = iconsDir.entryList(QDir::Files);
    if (files.size() > 0)
    {
        icons = QPixmap(iconsDir.absoluteFilePath(files[0]));
        imageLabel->setPixmap(icons);
        iconsInRow = icons.width() / ICON_SIZE;
        imageLabel->init(iconsInRow);
        this->setWidget(imageLabel);
    }
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
    if (iconsInRow != 0 && widget() != NULL)
    {
        dynamic_cast<IconWidget*>(this->widget())->setIconNumber(icon);
        horizontalScrollBar()->setValue(ICON_SIZE * (icon % iconsInRow) );
        verticalScrollBar()->setValue(ICON_SIZE * (icon / iconsInRow) );
        this->widget()->update();
    }
}

int IconView::getActiveIcon()
{
    if (widget() != NULL)
    {
        return dynamic_cast<IconWidget*>(this->widget())->getIconNumber();
    }
    else
    {
        return 0;
    }
}

void IconView::appendIcon(QImage newIcon)
{
    if (widget() != NULL)
    {
        IconWidget* widget = dynamic_cast<IconWidget*>(this->widget());

        widget->requestIconAppend(newIcon);
    }
}

void IconView::saveIcons(const QString& path)
{
    if (widget() != NULL)
    {
        IconWidget* widget = dynamic_cast<IconWidget*>(this->widget());

        if (widget->iconsWereEdited())
        {
            QImage icons = widget->pixmap()->toImage();
            icons.save(path);
        }
    }
}
