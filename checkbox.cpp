#include "checkbox.h"
#include "ui_checkbox.h"

CheckBox::CheckBox(QString name, QString description, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CheckBox)
{
    ui->setupUi(this);
    ui->checkBox->setText(name);
    ui->checkBox->setToolTip(description);
}

CheckBox::~CheckBox()
{
    delete ui;
}
