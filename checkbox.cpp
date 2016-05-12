#include "checkbox.h"
#include "ui_checkbox.h"

CheckBox::CheckBox(QString name, QString description, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CheckBox)
{
    ui->setupUi(this);
    ui->checkBox->setText(name);
    ui->checkBox->setToolTip(description);
    setAccessibleName(name);
}

CheckBox::~CheckBox()
{
    delete ui;
}

void CheckBox::setChecked(bool check)
{
    ui->checkBox->setChecked(check);
}

bool CheckBox::isChecked()
{
    return ui->checkBox->isChecked();
}
