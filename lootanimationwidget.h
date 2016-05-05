#ifndef LOOTANIMATIONWIDGET_H
#define LOOTANIMATIONWIDGET_H

#include <QFrame>

namespace Ui {
class LootAnimationWidget;
}

class LootAnimationWidget : public QFrame
{
    Q_OBJECT

public:
    explicit LootAnimationWidget(QString name, QWidget *parent = 0);
    ~LootAnimationWidget();

    void clear();

    Ui::LootAnimationWidget *ui;
};

#endif // LOOTANIMATIONWIDGET_H
