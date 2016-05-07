#include "lineedit.h"
#include "ui_lineedit.h"

LineEdit::LineEdit(QString name, QString description, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LineEdit),
    editedStyle("background-color:#66FF99;")
{
    ui->setupUi(this);
    ui->label->setText(name);
    ui->label->setToolTip(description);
    setAccessibleName(name);

    connect(ui->lineEdit, SIGNAL(textChanged(const QString&)),
        SLOT(markNotEmptyLineEdit(const QString& text)));
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

void LineEdit::markNotEmptyLineEdit(const QString &text)
{
    if (text != "")
    {
        ui->lineEdit->setStyleSheet(editedStyle);
    }
    else
    {
        ui->lineEdit->setStyleSheet("");
    }
}
