#ifndef ICONSELECTOR_H
#define ICONSELECTOR_H

#include <QDialog>

namespace Ui {
class IconSelector;
}

class IconSelector : public QDialog
{
    Q_OBJECT

public:
    explicit IconSelector(QWidget *parent = 0);
    ~IconSelector();

protected:
    void paintEvent(QPaintEvent* event);

private slots:
    void openIcon();

private:
    Ui::IconSelector *ui;
};

#endif // ICONSELECTOR_H
