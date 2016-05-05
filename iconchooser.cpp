#include "iconchooser.h"
#include "ui_iconchooser.h"

IconChooser::IconChooser(QString name, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::IconChooser)
{
    ui->setupUi(this);
    setAccessibleName(name);
}

IconChooser::~IconChooser()
{
    delete ui;
}
