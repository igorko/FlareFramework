#include "combobox.h"
#include "ui_combobox.h"

ComboBox::ComboBox(QString name, QString description, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ComboBox)
{
    ui->setupUi(this);
    ui->label->setText(name);
    ui->label->setToolTip(description);
    setAccessibleName(name);
}

ComboBox::~ComboBox()
{
    delete ui;
}
