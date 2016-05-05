#include "twostringlists.h"
#include "ui_twostringlists.h"

TwoStringLists::TwoStringLists(QString name, QString description, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TwoStringLists)
{
    ui->setupUi(this);
    ui->label->setText(name);
    ui->label->setToolTip(description);
    setAccessibleName(name);
}

TwoStringLists::~TwoStringLists()
{
    delete ui;
}

void TwoStringLists::clear()
{
    ui->edit_1->clear();
    ui->edit_2->clear();
}

void TwoStringLists::setValues(QVector<QPair<QString, QString> > values)
{
    for (unsigned int i = 0; i < values.size(); i++)
    {
        ui->edit_1->appendPlainText(values[i].first);
        ui->edit_2->appendPlainText(values[i].second);
    }
}
