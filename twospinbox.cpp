#include "twospinbox.h"
#include "ui_twospinbox.h"

TwoSpinBox::TwoSpinBox(QString name, QString description, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TwoSpinBox)
{
    ui->setupUi(this);
    ui->label->setText(name);
    ui->label->setToolTip(description);
    setAccessibleName(name);
}

TwoSpinBox::~TwoSpinBox()
{
    delete ui;
}

void TwoSpinBox::setValue1(int value)
{
    ui->spinBox->setValue(value);
}

void TwoSpinBox::setValue2(int value)
{
    ui->spinBox_2->setValue(value);
}

int TwoSpinBox::value1()
{
    return ui->spinBox->value();
}

int TwoSpinBox::value2()
{
    return ui->spinBox_2->value();
}
