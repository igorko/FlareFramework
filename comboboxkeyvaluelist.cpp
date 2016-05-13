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

QTextDocument *ComboBoxKeyValueList::keys()
{
    return ui->keys->document();
}

QTextDocument *ComboBoxKeyValueList::values()
{
    return ui->values->document();
}

void ComboBoxKeyValueList::appendKey(QString text)
{
    ui->keys->appendPlainText(text);
}

void ComboBoxKeyValueList::appendValue(QString text)
{
    ui->values->appendPlainText(text);
}

void ComboBoxKeyValueList::clear()
{
    ui->keys->clear();
    ui->values->clear();
}

void ComboBoxKeyValueList::addItem()
{
    ui->keys->appendPlainText(ui->list->currentText());
}
