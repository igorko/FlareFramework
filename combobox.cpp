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

void ComboBox::setCurrentIndex(int index)
{
    ui->comboBox->setCurrentIndex(index);
}

void ComboBox::clear()
{
    ui->comboBox->clear();
}

void ComboBox::addItem(QString value)
{
    ui->comboBox->addItem(value);
}

void ComboBox::addItems(QStringList values)
{
    ui->comboBox->addItems(values);
}
