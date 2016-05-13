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
    explicit ComboBox(QString name, QString description,
                      QStringList comboBoxValues, QWidget *parent = 0);
    ~ComboBox();

    void setCurrentIndex(int index);
    void clear();
    QVariant itemData(int index);
    int currentIndex();

    void addItem(QString value);
    void addItem(QString text, const QVariant & data);
    void addItems(QStringList values);
    void selectComboBoxItemByText(const QString &text);

    int count();
    void setStyleSheet(QString text);
    void setToolTip(QString text);

    QString currentText();

private:
    Ui::ComboBox *ui;
};

#endif // COMBOBOX_H
