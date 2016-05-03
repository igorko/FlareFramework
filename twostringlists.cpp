#include "twostringlists.h"
#include "ui_twostringlists.h"

TwoStringLists::TwoStringLists(QString name, QString description, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TwoStringLists)
{
    ui->setupUi(this);
    ui->label->setText(name);
    ui->label->setToolTip(description);
}

TwoStringLists::~TwoStringLists()
{
    delete ui;
}
