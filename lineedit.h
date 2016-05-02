#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QWidget>

namespace Ui {
class LineEdit;
}

class LineEdit : public QWidget
{
    Q_OBJECT

public:
    explicit LineEdit(QString name, QString description, QWidget *parent = 0);
    ~LineEdit();

private:
    Ui::LineEdit *ui;
};

#endif // LINEEDIT_H
