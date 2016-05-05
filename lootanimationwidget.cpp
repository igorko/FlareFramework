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
