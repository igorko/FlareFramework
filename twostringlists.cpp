#include "twostringlists.h"
#include "ui_twostringlists.h"

#include <QTextDocument>
#include <QTextBlock>

TwoStringLists::TwoStringLists(QString name, QString description, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TwoStringLists),
    editedStyle("background-color:#66FF99;")
{
    ui->setupUi(this);
    ui->label->setText(name);
    ui->label->setToolTip(description);
    setAccessibleName(name);

    connect(ui->edit_1, SIGNAL(textChanged()), SLOT(markNotEmptyPlainTextEdits()));
    connect(ui->edit_2, SIGNAL(textChanged()), SLOT(markNotEmptyPlainTextEdits()));
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

void TwoStringLists::setValues(QVector<QPair<QString, QString> > values)
{
    ui->edit_1->clear();
    ui->edit_2->clear();

    for (int i = 0; i < values.size(); i++)
    {
        ui->edit_1->appendPlainText(values[i].first);
        ui->edit_2->appendPlainText(values[i].second);
    }
}

void TwoStringLists::markNotEmptyPlainTextEdits()
{
    QTextDocument* doc1 = ui->edit_1->document();

    if (doc1->lineCount() >= 1 && !doc1->findBlockByLineNumber(0).text().isEmpty())
    {
        ui->edit_1->setStyleSheet(editedStyle);
    }
    else
    {
        ui->edit_1->setStyleSheet("");
    }

    QTextDocument* doc2 = ui->edit_2->document();

    if (doc2->lineCount() >= 1 && !doc2->findBlockByLineNumber(0).text().isEmpty())
    {
        ui->edit_2->setStyleSheet(editedStyle);
    }
    else
    {
        ui->edit_2->setStyleSheet("");
    }
}
