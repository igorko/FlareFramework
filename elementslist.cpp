#include "elementslist.h"
#include "ui_elementslist.h"

ElementsList::ElementsList(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ElementsList)
{
    ui->setupUi(this);
    setAccessibleName("elementslist");
}

ElementsList::~ElementsList()
{
    delete ui;
}
