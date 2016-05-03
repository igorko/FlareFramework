#include "lineedit.h"
#include "ui_lineedit.h"

LineEdit::LineEdit(QString name, QString description, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LineEdit)
{
    ui->setupUi(this);
    ui->label->setText(name);
    ui->label->setToolTip(description);
}

LineEdit::~LineEdit()
{
    delete ui;
}
