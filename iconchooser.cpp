#include "iconchooser.h"
#include "ui_iconchooser.h"

IconChooser::IconChooser(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::IconChooser)
{
    ui->setupUi(this);
}

IconChooser::~IconChooser()
{
    delete ui;
}
