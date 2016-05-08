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

public slots:
    void markNotDefaultSpinBox(double value);

private:
    Ui::DoubleSpinBox *ui;

    QString editedStyle;
    int defaultValue;
};

#endif // DOUBLESPINBOX_H
