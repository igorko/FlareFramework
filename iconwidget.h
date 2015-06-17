#ifndef ICONWIDGET_H
#define ICONWIDGET_H

#include <QLabel>

#define ICONS_IN_ROW 8
#define ICON_SIZE 32

class IconWidget : public QLabel
{
    Q_OBJECT
public:
    explicit IconWidget(QWidget *parent = 0);

    void setIconNumber(int icon);
    int getIconNumber();
    void requestIconAppend(QImage icon);
    bool iconsWereEdited();

signals:
    void iconPlaced();
    void iconSkipped();

public slots:

protected:
    void paintEvent(QPaintEvent* event);

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    void drawSelection(QPainter& painter, QPoint selection);

    QPoint selection;
    int iconNumber;
    bool iconPlacingRequested;
    QImage newIcon;
    bool iconsEdited;

};

#endif // ICONWIDGET_H
