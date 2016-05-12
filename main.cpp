#include "mainwindow.h"
#include <QApplication>
#include <QMetaType>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<QList<QString>>("QList<QString>");
    qRegisterMetaType<QList<QStringList>>("QList<QStringList>");

    MainWindow w;
    w.BuildUI();
    w.show();

    return a.exec();
}
