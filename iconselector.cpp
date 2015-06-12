#include "iconselector.h"
#include "ui_iconselector.h"
#include "iconwidget.h"

#include <QPainter>
#include <QFileDIalog>
#include <QDesktopServices>

IconSelector::IconSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IconSelector)
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

        ui->iconImage->setPixmap(p.scaled(w, h, Qt::KeepAspectRatio));
        update();
    }
}

void IconSelector::paintEvent(QPaintEvent *event)
{
    QDialog::paintEvent(event);

    if (ui->iconImage->pixmap())
    {
        float ratio = ui->iconImage->height() / ICON_SIZE;

        QPainter painter(this);
        painter.setPen(QPen(QBrush(Qt::red), 5));

        int xOffset = (ui->iconImage->width() - ratio * ICON_SIZE) / 2;
        painter.drawRect(QRect(ui->iconImage->x() + xOffset,
                               ui->iconImage->y(),
                               ratio * ICON_SIZE, ratio * ICON_SIZE));
    }
}

IconSelector::~IconSelector()
{
    delete ui;
}
