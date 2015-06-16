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

    void setActiveIcon(int icon);
    int getActiveIcon();
    void appendIcon(QImage newIcon);

signals:

public slots:

protected:
    void mouseMoveEvent(QMouseEvent* event);

private:
    void updateSelection(int x, int y);

    QImage icons;

};

#endif // ICONVIEW_H
