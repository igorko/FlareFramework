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
