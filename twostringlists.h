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

private:
    Ui::TwoStringLists *ui;
};

#endif // TWOSTRINGLISTS_H
