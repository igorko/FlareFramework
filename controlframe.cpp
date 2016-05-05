#include "controlframe.h"
#include "ui_controlframe.h"

ControlFrame::ControlFrame(QString name, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ControlFrame)
{
    ui->setupUi(this);
    setAccessibleName(name);
}

ControlFrame::~ControlFrame()
{
    delete ui;
}
