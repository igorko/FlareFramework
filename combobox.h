#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QFrame>

namespace Ui {
class ComboBox;
}

class ComboBox : public QFrame
{
    Q_OBJECT

public:
    explicit ComboBox(QString name, QString description, QWidget *parent = 0);
    ~ComboBox();

    void setCurrentIndex(int index);
    void clear();

private:
    Ui::ComboBox *ui;
};

#endif // COMBOBOX_H
