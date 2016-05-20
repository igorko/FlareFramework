#include "threespinbox.h"
#include "ui_threespinbox.h"

ThreeSpinBox::ThreeSpinBox(QString name, QString description, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ThreeSpinBox)
{
    ui->setupUi(this);
    ui->label->setText(name);
    ui->label->setToolTip(description);
    setAccessibleName(name);
}

ThreeSpinBox::~ThreeSpinBox()
{
    delete ui;
}

void ThreeSpinBox::setValue1(int value)
{
    ui->spinBox->setValue(value);
}

void ThreeSpinBox::setValue2(int value)
{
    ui->spinBox_2->setValue(value);
}

void ThreeSpinBox::setValue3(int value)
{
    ui->spinBox_3->setValue(value);
}

int ThreeSpinBox::value1()
{
    return ui->spinBox->value();
}

int ThreeSpinBox::value2()
{
    return ui->spinBox_2->value();
}

int ThreeSpinBox::value3()
{
    return ui->spinBox_3->value();
}
