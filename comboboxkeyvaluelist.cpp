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

    connect(ui->add, SIGNAL(clicked()), SLOT(addItem()));
}

ComboBoxKeyValueList::~ComboBoxKeyValueList()
{
    delete ui;
}

QComboBox *ComboBoxKeyValueList::comboBox()
{
    return ui->list;
}

void ComboBoxKeyValueList::addItem()
{
    ui->keys->appendPlainText(ui->list->currentText());
}
