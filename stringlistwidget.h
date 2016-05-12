#ifndef STRINGLISTWIDGET_H
#define STRINGLISTWIDGET_H

#include <QFrame>
#include <QTextDocument>
#include <QComboBox>

namespace Ui {
class StringListWidget;
}

class StringListWidget : public QFrame
{
    Q_OBJECT

public:
    explicit StringListWidget(QString name, QString description, QWidget *parent = 0);
    ~StringListWidget();

    void clear();

    void setValues(QVector<QString> values);

    void addItemToComboBox(QString text);

    QTextDocument* doc();

    QComboBox * comboBox();

public slots:
    void addItem();

private:
    Ui::StringListWidget *ui;
};

#endif // STRINGLISTWIDGET_H
