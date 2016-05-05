#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QFrame>

namespace Ui {
class CheckBox;
}

class CheckBox : public QFrame
{
    Q_OBJECT

public:
    explicit CheckBox(QString name, QString description, QWidget *parent = 0);
    ~CheckBox();

    void setChecked(bool check);

private:
    Ui::CheckBox *ui;
};

#endif // CHECKBOX_H
