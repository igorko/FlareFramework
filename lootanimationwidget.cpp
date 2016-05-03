#include "lootanimationwidget.h"
#include "ui_lootanimationwidget.h"

LootAnimationWidget::LootAnimationWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LootAnimationWidget)
{
    ui->setupUi(this);
}

LootAnimationWidget::~LootAnimationWidget()
{
    delete ui;
}
