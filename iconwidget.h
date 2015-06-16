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
    void requestIconAppend();
    void setNewIcon(QImage iIcon);

signals:

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

};

#endif // ICONWIDGET_H
