#include "iconchooser.h"
#include "ui_iconchooser.h"

IconChooser::IconChooser(QString name, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::IconChooser)
{
    ui->setupUi(this);
    setAccessibleName(name);

    // fix icon selection for poly
}

IconChooser::~IconChooser()
{
    delete ui;
}

void IconChooser::setActiveIcon(int value)
{
    ui->iconsView->setActiveIcon(value);
}
