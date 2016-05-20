#include "fourspinbox.h"
#include "ui_fourspinbox.h"

FourSpinBox::FourSpinBox(QString name, QString description, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FourSpinBox)
{
    ui->setupUi(this);
    ui->label->setText(name);
    ui->label->setToolTip(description);
    setAccessibleName(name);
}

FourSpinBox::~FourSpinBox()
{
    delete ui;
}

void FourSpinBox::setValue1(int value)
{
    ui->spinBox->setValue(value);
}

void FourSpinBox::setValue2(int value)
{
    ui->spinBox_2->setValue(value);
}

void FourSpinBox::setValue3(int value)
{
    ui->spinBox_3->setValue(value);
}

void FourSpinBox::setValue4(int value)
{
    ui->spinBox_4->setValue(value);
}

int FourSpinBox::value1()
{
    return ui->spinBox->value();
}

int FourSpinBox::value2()
{
    return ui->spinBox_2->value();
}

int FourSpinBox::value3()
{
    return ui->spinBox_3->value();
}

int FourSpinBox::value4()
{
    return ui->spinBox_4->value();
}
