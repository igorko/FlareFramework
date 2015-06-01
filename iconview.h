#ifndef ICONVIEW_H
#define ICONVIEW_H

#include <QScrollArea>
#include <QGraphicsView>

class IconView : public QScrollArea
{
    Q_OBJECT
public:
    explicit IconView(QWidget *parent = 0);
    void init(const QString& path);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);

private:
    void drawSelection(QPainter& painter, QPoint selection);
    void updateSelection(int x, int y);

    QImage icons;
    QPoint selection;

};

#endif // ICONVIEW_H
