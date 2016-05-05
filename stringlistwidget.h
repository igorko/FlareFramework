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

private:
    Ui::StringListWidget *ui;
};

#endif // STRINGLISTWIDGET_H
