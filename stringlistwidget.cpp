#include "stringlistwidget.h"
#include "ui_stringlistwidget.h"

StringListWidget::StringListWidget(QString name, QString description, QStringList comboBoxValues, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::StringListWidget)
{
    ui->setupUi(this);
    ui->label->setText(name);
    ui->label->setToolTip(description);
    setAccessibleName(name);
    ui->selector->addItems(comboBoxValues);

    connect(ui->addButton, SIGNAL(clicked()), SLOT(addItem()));
}

StringListWidget::~StringListWidget()
{
    delete ui;
}

void StringListWidget::clear()
{
    ui->list->clear();
    ui->selector->setCurrentIndex(0);
}

void StringListWidget::setValues(QVector<QString> values)
{
    ui->list->clear();
    for (int i = 0; i < values.size(); i++)
    {
        ui->list->appendPlainText(values[i]);
    }
}

void StringListWidget::addItemToComboBox(QString text)
{
    ui->selector->addItem(text);
}

QTextDocument *StringListWidget::doc()
{
    return ui->list->document();
}

QComboBox *StringListWidget::comboBox()
{
    return ui->selector;
}

void StringListWidget::addItem()
{
    ui->list->appendPlainText(ui->selector->currentText());
}

