#include "iconselector.h"
#include "ui_iconselector.h"
#include "iconwidget.h"

#include <QPainter>
#include <QFileDialog>
#include <QDesktopServices>
#include <QMouseEvent>
#include <QDebug>

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
        int size = ratio * ICON_SIZE - 2;
        selection = QRect(0, 0, size, size);
        selectionChanged = true;
    }
}

void IconSelector::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
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
        updateSelection(event->pos());
    }
}

void IconSelector::mousePressEvent(QMouseEvent *event)
{
    this->setCursor(Qt::OpenHandCursor);
    QDialog::mousePressEvent(event);
}

void IconSelector::mouseReleaseEvent(QMouseEvent *event)
{
    this->setCursor(Qt::ArrowCursor);
    QDialog::mouseReleaseEvent(event);
}

void IconSelector::wheelEvent(QWheelEvent *event)
{
    if (ui->iconImage->rect().contains(event->pos()))
    {
        int numDegrees = event->delta() / 8;

        int numSteps = numDegrees / 5;

        int width = selection.width() + numSteps;
        int height = selection.height() + numSteps;

        if (width > ui->iconImage->width() || height > ui->iconImage->height() || width < 32 || height < 32)
        {
            return;
        }

        selection = QRect(selection.x() - numSteps/2, selection.y() - numSteps/2, width, height);
        selectionChanged = true;

        event->accept();
    }
    QDialog::wheelEvent(event);
}

void IconSelector::updateSelection(const QPoint &pos)
{
    selection.moveCenter(pos);

    // TODO: review offsets, something is wrong with mouse pointer centering
    int xOffset = abs(ui->iconImage->width() - image.width()) / 2;
    int yOffset = abs(ui->iconImage->height() - image.height()) / 2;
    selection.moveTopLeft(QPoint(selection.left() - xOffset, selection.top() - yOffset));

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
