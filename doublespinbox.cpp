#include "doublespinbox.h"
#include "ui_doublespinbox.h"

DoubleSpinBox::DoubleSpinBox(QString name, QString description, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DoubleSpinBox),
    editedStyle("background-color:#66FF99;")
{
    ui->setupUi(this);
    ui->label->setText(name);
    ui->label->setToolTip(description);
    setAccessibleName(name);
    defaultValue = 0.0;

    connect(ui->doubleSpinBox, SIGNAL(valueChanged(double)),
        SLOT(markNotDefaultSpinBox(double)));
}

DoubleSpinBox::~DoubleSpinBox()
{
    delete ui;
}

void DoubleSpinBox::setValue(double value)
{
    ui->doubleSpinBox->setValue(value);
}

void DoubleSpinBox::markNotDefaultSpinBox(double value)
{
    if (value != defaultValue)
    {
        ui->doubleSpinBox->setStyleSheet(editedStyle);
    }
    else
    {
        ui->doubleSpinBox->setStyleSheet("");
    }
}
