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

    void setValue(int value);

    Ui::SpinBox *ui;

public slots:
    void markNotDefaultSpinBox(int value);

private:

    QString editedStyle;
    int defaultValue;
};

#endif // SPINBOX_H
