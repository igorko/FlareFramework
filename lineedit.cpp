#include "lineedit.h"
#include "ui_lineedit.h"

LineEdit::LineEdit(QString name, QString description, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LineEdit)
{
    ui->setupUi(this);
    ui->label->setText(name);
    ui->label->setToolTip(description);
    setAccessibleName(name);
}

LineEdit::~LineEdit()
{
    delete ui;
}

void LineEdit::clear()
{
    ui->lineEdit->clear();
}

void LineEdit::setText(QString text)
{
    ui->lineEdit->setText(text);
}
