#ifndef SPINBOX_H
#define SPINBOX_H

#include <QFrame>

namespace Ui {
class SpinBox;
}

class SpinBox : public QFrame
{
    Q_OBJECT

public:
    explicit SpinBox(QString name, QString description, QWidget *parent = 0);
    ~SpinBox();

private:
    Ui::SpinBox *ui;
};

#endif // SPINBOX_H
