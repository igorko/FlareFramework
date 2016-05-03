#ifndef ICONCHOOSER_H
#define ICONCHOOSER_H

#include <QFrame>

namespace Ui {
class IconChooser;
}

class IconChooser : public QFrame
{
    Q_OBJECT

public:
    explicit IconChooser(QWidget *parent = 0);
    ~IconChooser();

private:
    Ui::IconChooser *ui;
};

#endif // ICONCHOOSER_H
