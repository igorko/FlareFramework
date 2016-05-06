#ifndef COMBOBOXKEYVALUELIST_H
#define COMBOBOXKEYVALUELIST_H

#include <QFrame>

namespace Ui {
class ComboBoxKeyValueList;
}

class ComboBoxKeyValueList : public QFrame
{
    Q_OBJECT

public:
    explicit ComboBoxKeyValueList(QString name, QString description, QWidget *parent = 0);
    ~ComboBoxKeyValueList();

private:
    Ui::ComboBoxKeyValueList *ui;
};

#endif // COMBOBOXKEYVALUELIST_H
