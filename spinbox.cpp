#include "spinbox.h"
#include "ui_spinbox.h"

SpinBox::SpinBox(QString name, QString description, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SpinBox)
{
    ui->setupUi(this);
    ui->label->setText(name);
    ui->label->setToolTip(description);
    setAccessibleName(name);
}

SpinBox::~SpinBox()
{
    delete ui;
}

void SpinBox::setValue(int value)
{
    ui->spinBox->setValue(value);
}
