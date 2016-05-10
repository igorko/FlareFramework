#ifndef TWOSPINBOX_H
#define TWOSPINBOX_H

#include <QFrame>

namespace Ui {
class TwoSpinBox;
}

class TwoSpinBox : public QFrame
{
    Q_OBJECT

public:
    explicit TwoSpinBox(QString name, QString description, QWidget *parent = 0);
    ~TwoSpinBox();

    void setValue1(int value);
    void setValue2(int value);

    Ui::TwoSpinBox *ui;

private:
};

#endif // TWOSPINBOX_H
