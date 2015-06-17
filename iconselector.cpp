#include "iconselector.h"
#include "ui_iconselector.h"
#include "iconwidget.h"

#include <QPainter>
#include <QFileDialog>
#include <QDesktopServices>
#include <QMouseEvent>

IconSelector::IconSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IconSelector),
    selectionChanged(false)
{
    ui->setupUi(this);

    connect(ui->browseButton, SIGNAL(clicked()), SLOT(openIcon()));
}

void IconSelector::openIcon()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File",
                                 QDesktopServices::storageLocation(QDesktopServices::HomeLocation),
                                 "Images (*.png *.jpg)");

    if (!fileName.isEmpty())
    {
        QPixmap p(fileName);
        int w = ui->iconImage->width();
        int h = ui->iconImage->height();
        image = p.scaled(w, h, Qt::KeepAspectRatio);

        ui->iconImage->setPixmap(image);
        QSize pixmapSize = image.size();
        ratio = (float)qMin(pixmapSize.width(), pixmapSize.height()) / (float)ICON_SIZE;
        selection = QRect(0, 0, ratio * ICON_SIZE - 2, ratio * ICON_SIZE - 2);
        selectionChanged = true;
    }
}

void IconSelector::paintEvent(QPaintEvent *event)
{
    if (ui->iconImage->pixmap() && selectionChanged)
    {
        QImage tmp(image.toImage());
        QPainter painter(&tmp);

        painter.setPen(QPen(QBrush(Qt::red), 3));
        painter.drawRect(selection);

        ui->iconImage->setPixmap(QPixmap::fromImage(tmp));
        selectionChanged = false;
    }
}

void IconSelector::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        updateSelection(event->pos().x(), event->pos().y());
    }
}

void IconSelector::mousePressEvent(QMouseEvent *event)
{
    this->setCursor(Qt::OpenHandCursor);
}

void IconSelector::mouseReleaseEvent(QMouseEvent *event)
{
    this->setCursor(Qt::ArrowCursor);
}

void IconSelector::updateSelection(int x, int y)
{
    selection = QRect(x - ratio * ICON_SIZE / 2,
                      y - ratio * ICON_SIZE / 2,
                      ratio * ICON_SIZE - 2,
                      ratio * ICON_SIZE - 2);
    selectionChanged = true;
}

IconSelector::~IconSelector()
{
    delete ui;
}

QImage IconSelector::getSelection()
{
    return image.copy(selection).toImage().scaled(QSize(ICON_SIZE, ICON_SIZE), Qt::KeepAspectRatio);
}
