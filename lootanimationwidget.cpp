#include "lootanimationwidget.h"
#include "ui_lootanimationwidget.h"

#include <QTextBlock>

LootAnimationWidget::LootAnimationWidget(QString name, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LootAnimationWidget),
    editedStyle("background-color:#66FF99;")
{
    ui->setupUi(this);
    setAccessibleName(name);

    connect(ui->animations, SIGNAL(textChanged()), SLOT(markNotEmptyPlainTextEdits()));
    connect(ui->animationMin, SIGNAL(textChanged()), SLOT(markNotEmptyPlainTextEdits()));
    connect(ui->animationMax, SIGNAL(textChanged()), SLOT(markNotEmptyPlainTextEdits()));
    connect(ui->lootAnimAdd, SIGNAL(clicked()), SLOT(lootAnimAdd()));
}

LootAnimationWidget::~LootAnimationWidget()
{
    delete ui;
}

void LootAnimationWidget::clear()
{
    ui->lootAnimList->setCurrentIndex(0);

    ui->animationMax->clear();
    ui->animationMin->clear();
    ui->animations->clear();

}

void LootAnimationWidget::setValues(QVector<QAnimation> values)
{
    for (int i = 0; i < values.size(); i++)
    {
        ui->animations->appendPlainText(values[i].name);
        ui->animationMin->appendPlainText(QString::number(values[i].low));
        ui->animationMax->appendPlainText(QString::number(values[i].high));
    }
}

void LootAnimationWidget::addItems(QStringList values)
{
    ui->lootAnimList->addItems(values);
}

void LootAnimationWidget::markNotEmptyPlainTextEdits()
{
    QTextDocument* doc1 = ui->animations->document();

    if (doc1->lineCount() >= 1 && !doc1->findBlockByLineNumber(0).text().isEmpty())
    {
        ui->animations->setStyleSheet(editedStyle);
    }
    else
    {
        ui->animations->setStyleSheet("");
    }

    QTextDocument* doc2 = ui->animationMin->document();

    if (doc2->lineCount() >= 1 && !doc2->findBlockByLineNumber(0).text().isEmpty())
    {
        ui->animationMin->setStyleSheet(editedStyle);
    }
    else
    {
        ui->animationMin->setStyleSheet("");
    }

    QTextDocument* doc3 = ui->animationMax->document();

    if (doc3->lineCount() >= 1 && !doc3->findBlockByLineNumber(0).text().isEmpty())
    {
        ui->animationMax->setStyleSheet(editedStyle);
    }
    else
    {
        ui->animationMax->setStyleSheet("");
    }
}

void LootAnimationWidget::lootAnimAdd()
{
    ui->animations->appendPlainText(ui->lootAnimList->currentText());
}
