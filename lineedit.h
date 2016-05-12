#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QFrame>

namespace Ui {
class LineEdit;
}

class LineEdit : public QFrame
{
    Q_OBJECT

public:
    explicit LineEdit(QString name, QString description, QWidget *parent = 0);
    ~LineEdit();

    void clear();

    void setText(QString text);

    QString text();

public slots:
    void markNotEmptyLineEdit(const QString& text);

private:
    Ui::LineEdit *ui;
    QString editedStyle;
};

#endif // LINEEDIT_H
