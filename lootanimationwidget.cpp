#include "lootanimationwidget.h"
#include "ui_lootanimationwidget.h"

LootAnimationWidget::LootAnimationWidget(QString name, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LootAnimationWidget)
{
    ui->setupUi(this);
    setAccessibleName(name);
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
    for (unsigned int i = 0; i < values.size(); i++)
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
