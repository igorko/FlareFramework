#include "comboboxkeyvaluelist.h"
#include "ui_comboboxkeyvaluelist.h"

ComboBoxKeyValueList::ComboBoxKeyValueList(QString name, QString description, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ComboBoxKeyValueList)
{
    ui->setupUi(this);
    ui->label->setText(name);
    ui->label->setToolTip(description);
    setAccessibleName(name);
}

ComboBoxKeyValueList::~ComboBoxKeyValueList()
{
    delete ui;
}
