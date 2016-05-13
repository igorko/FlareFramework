#ifndef COMBOBOXKEYVALUELIST_H
#define COMBOBOXKEYVALUELIST_H

#include <QFrame>
#include <QComboBox>
#include <QTextDocument>

namespace Ui {
class ComboBoxKeyValueList;
}

class ComboBoxKeyValueList : public QFrame
{
    Q_OBJECT

public:
    explicit ComboBoxKeyValueList(QString name, QString description,
                                  QStringList comboBoxValues, QWidget *parent = 0);
    ~ComboBoxKeyValueList();

    QComboBox * comboBox();

    QTextDocument * keys();
    QTextDocument * values();

    void appendKey(QString text);
    void appendValue(QString text);

    void clear();

public slots:
    void addItem();

private:
    Ui::ComboBoxKeyValueList *ui;
};

#endif // COMBOBOXKEYVALUELIST_H
