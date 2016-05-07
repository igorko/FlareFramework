#ifndef TWOSTRINGLISTS_H
#define TWOSTRINGLISTS_H

#include <QFrame>

namespace Ui {
class TwoStringLists;
}

class TwoStringLists : public QFrame
{
    Q_OBJECT

public:
    explicit TwoStringLists(QString name, QString description, QWidget *parent = 0);
    ~TwoStringLists();

    void clear();

    void setValues(QVector< QPair<QString, QString> > values);

public slots:
    void markNotEmptyPlainTextEdits();

private:
    Ui::TwoStringLists *ui;

    QString editedStyle;
};

#endif // TWOSTRINGLISTS_H
