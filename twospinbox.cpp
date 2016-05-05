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
