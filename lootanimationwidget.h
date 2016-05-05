#ifndef LOOTANIMATIONWIDGET_H
#define LOOTANIMATIONWIDGET_H

#include <QFrame>

struct QAnimation
{
    QString name;
    int low;
    int high;
};

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

    void setValues(QVector<QAnimation> values);

    Ui::LootAnimationWidget *ui;
};

#endif // LOOTANIMATIONWIDGET_H
