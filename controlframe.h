#ifndef CONTROLFRAME_H
#define CONTROLFRAME_H

#include <QFrame>

namespace Ui {
class ControlFrame;
}

class ControlFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ControlFrame(QString name, QWidget *parent = 0);
    ~ControlFrame();

    Ui::ControlFrame *ui;
};

#endif // CONTROLFRAME_H
