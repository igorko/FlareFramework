#ifndef ELEMENTSLIST_H
#define ELEMENTSLIST_H

#include <QFrame>

namespace Ui {
class ElementsList;
}

class ElementsList : public QFrame
{
    Q_OBJECT

public:
    explicit ElementsList(QWidget *parent = 0);
    ~ElementsList();

    Ui::ElementsList *ui;
};

#endif // ELEMENTSLIST_H
