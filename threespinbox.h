#ifndef THREESPINBOX_H
#define THREESPINBOX_H

#include <QFrame>

namespace Ui {
class ThreeSpinBox;
}

class ThreeSpinBox : public QFrame
{
    Q_OBJECT

public:
    explicit ThreeSpinBox(QString name, QString description, QWidget *parent = 0);
    ~ThreeSpinBox();

    void setValue1(int value);
    void setValue2(int value);
    void setValue3(int value);

    int value1();
    int value2();
    int value3();

private:
    Ui::ThreeSpinBox *ui;

};

#endif // THREESPINBOX_H
