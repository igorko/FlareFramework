#ifndef TWOSTRINGLISTS_H
#define TWOSTRINGLISTS_H

#include <QFrame>
#include <QTextDocument>

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

    QTextDocument* doc1();
    QTextDocument* doc2();

public slots:
    void markNotEmptyPlainTextEdits();

private:
    Ui::TwoStringLists *ui;

    QString editedStyle;
};

#endif // TWOSTRINGLISTS_H
