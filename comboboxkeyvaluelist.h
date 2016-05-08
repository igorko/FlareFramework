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

    Ui::ComboBoxKeyValueList *ui;

public slots:
    void addItem();
};

#endif // COMBOBOXKEYVALUELIST_H
