#include "spinbox.h"
#include "ui_spinbox.h"

SpinBox::SpinBox(QString name, QString description, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SpinBox),
    editedStyle("background-color:#66FF99;")
{
    ui->setupUi(this);
    ui->label->setText(name);
    ui->label->setToolTip(description);
    setAccessibleName(name);
    defaultValue = 0;

    if (name == "max_quantity")
        defaultValue = 1;

    connect(ui->spinBox, SIGNAL(valueChanged(int)),
        SLOT(markNotDefaultSpinBox(int)));
}

SpinBox::~SpinBox()
{
    delete ui;
}

void SpinBox::setValue(int value)
{
    ui->spinBox->setValue(value);
}

int SpinBox::value()
{
    return ui->spinBox->value();
}

void SpinBox::markNotDefaultSpinBox(int value)
{
    if (value != defaultValue)
    {
        ui->spinBox->setStyleSheet(editedStyle);
    }
    else
    {
        ui->spinBox->setStyleSheet("");
    }
}
