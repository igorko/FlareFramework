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

QVariant ComboBox::itemData(int index)
{
    return ui->comboBox->itemData(index);
}

int ComboBox::currentIndex()
{
    ui->comboBox->currentIndex();
}

void ComboBox::addItem(QString value)
{
    ui->comboBox->addItem(value);
}

void ComboBox::addItem(QString text, const QVariant & data)
{
    ui->comboBox->addItem(text, data);
}

void ComboBox::addItems(QStringList values)
{
    ui->comboBox->addItems(values);
}

void ComboBox::selectComboBoxItemByText(const QString &text)
{
    ui->comboBox->setCurrentIndex(-1);
    for (int i = 0; i < ui->comboBox->count(); i++)
    {
        if (ui->comboBox->itemText(i) == text)
        {
            ui->comboBox->setCurrentIndex(i);
            break;
        }
    }
}

int ComboBox::count()
{
    return ui->comboBox->count();
}

void ComboBox::setStyleSheet(QString text)
{
    ui->comboBox->setStyleSheet(text);
}

void ComboBox::setToolTip(QString text)
{
    ui->comboBox->setToolTip(text);
}

QString ComboBox::currentText()
{
    return ui->comboBox->currentText();
}
