#include "iconselector.h"
#include "ui_iconselector.h"
#include "iconwidget.h"

#include <QPainter>
#include <QFileDIalog>
#include <QDesktopServices>

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
        QPixmap scaled = p.scaled(w, h, Qt::KeepAspectRatio);

        ui->iconImage->setPixmap(scaled);
        pixmapSize = scaled.size();
        selectionChanged = true;
    }
}

void IconSelector::paintEvent(QPaintEvent *event)
{
    if (ui->iconImage->pixmap() && selectionChanged)
    {
        float ratio = (float)qMin(pixmapSize.width(), pixmapSize.height()) / (float)ICON_SIZE;

        QImage tmp(ui->iconImage->pixmap()->toImage());
        QPainter painter(&tmp);

        painter.setPen(QPen(QBrush(Qt::red), 3));

        painter.drawRect(QRect(0, 0, ratio * ICON_SIZE - 2, ratio * ICON_SIZE - 2));

        ui->iconImage->setPixmap(QPixmap::fromImage(tmp));
        selectionChanged = false;
    }
}

IconSelector::~IconSelector()
{
    delete ui;
}
