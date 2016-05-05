#ifndef DOUBLESPINBOX_H
#define DOUBLESPINBOX_H

#include <QFrame>

namespace Ui {
class DoubleSpinBox;
}

class DoubleSpinBox : public QFrame
{
    Q_OBJECT

public:
    explicit DoubleSpinBox(QString name, QString description, QWidget *parent = 0);
    ~DoubleSpinBox();

    void setValue(double value);

private:
    Ui::DoubleSpinBox *ui;
};

#endif // DOUBLESPINBOX_H
