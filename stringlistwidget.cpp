#include "stringlistwidget.h"
#include "ui_stringlistwidget.h"

StringListWidget::StringListWidget(QString name, QString description, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::StringListWidget)
{
    ui->setupUi(this);
    ui->Label->setText(name);
    ui->Label->setToolTip(description);
    setAccessibleName(name);
}

StringListWidget::~StringListWidget()
{
    delete ui;
}

void StringListWidget::clear()
{
    ui->List->clear();
    ui->Selector->setCurrentIndex(0);
}

void StringListWidget::setValues(QVector<QString> values)
{
    for (unsigned int i = 0; i < values.size(); i++)
    {
        ui->List->appendPlainText(values[i]);
    }
}
