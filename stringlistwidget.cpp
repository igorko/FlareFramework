#include "stringlistwidget.h"
#include "ui_stringlistwidget.h"

StringListWidget::StringListWidget(QString name, QString description, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::StringListWidget)
{
    ui->setupUi(this);
    ui->Label->setText(name);
    ui->Label->setToolTip(description);
}

StringListWidget::~StringListWidget()
{
    delete ui;
}
