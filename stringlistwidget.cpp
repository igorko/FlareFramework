#include "stringlistwidget.h"
#include "ui_stringlistwidget.h"

StringListWidget::StringListWidget(QString name, QString description, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::StringListWidget)
{
    ui->setupUi(this);
    ui->label->setText(name);
    ui->label->setToolTip(description);
    setAccessibleName(name);

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
    for (int i = 0; i < values.size(); i++)
    {
        ui->list->appendPlainText(values[i]);
    }
}

void StringListWidget::addItem()
{
    ui->list->appendPlainText(ui->selector->currentText());
}

