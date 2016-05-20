#ifndef FOURSPINBOX_H
#define FOURSPINBOX_H

#include <QFrame>

namespace Ui {
class FourSpinBox;
}

class FourSpinBox : public QFrame
{
    Q_OBJECT

public:
    explicit FourSpinBox(QString name, QString description, QWidget *parent = 0);
    ~FourSpinBox();

    void setValue1(int value);
    void setValue2(int value);
    void setValue3(int value);
    void setValue4(int value);

    int value1();
    int value2();
    int value3();
    int value4();

private:
    Ui::FourSpinBox *ui;

};

#endif // FOURSPINBOX_H
