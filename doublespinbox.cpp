#include "doublespinbox.h"
#include "ui_doublespinbox.h"

DoubleSpinBox::DoubleSpinBox(QString name, QString description, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DoubleSpinBox)
{
    ui->setupUi(this);
    ui->label->setText(name);
    ui->label->setToolTip(description);
    setAccessibleName(name);
}

DoubleSpinBox::~DoubleSpinBox()
{
    delete ui;
}
