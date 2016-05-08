#ifndef STRINGLISTWIDGET_H
#define STRINGLISTWIDGET_H

#include <QFrame>

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

    Ui::StringListWidget *ui;

public slots:
    void addItem();
};

#endif // STRINGLISTWIDGET_H
