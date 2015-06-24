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

    QImage getSelection();

protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private slots:
    void openIcon();

private:
    void updateSelection(const QPoint& pos);

    Ui::IconSelector *ui;
    bool selectionChanged;
    QPixmap image;
    QRect selection;
    float ratio;
};

#endif // ICONSELECTOR_H
