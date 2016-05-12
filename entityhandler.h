#ifndef ENTITYHANDLER_H
#define ENTITYHANDLER_H

#include <QObject>

class MainWindow;
class ComboBox;
class QComboBox;
class QGridLayout;
class QListWidgetItem;

class EntityHandler : public QObject
{
    Q_OBJECT
public:
    explicit EntityHandler(MainWindow * _mainWindow, QObject *parent = 0);

    virtual void saveEntityList(const QString &path) = 0;
    virtual void loadEntityList(const std::string &path) = 0;
    virtual void clearItemsList();

    static QString qString(std::string value);
    static std::string stdString(QString value);

    bool entityEdited();
    void setEntityEdited(bool state);

signals:
    void entityWasEdited();
    void entityNotEdited();

public slots:
    QObject * CloseButton();
    virtual void pushBtn();
    virtual void clearBtn();
    virtual void selectElementFromList(QListWidgetItem *_item);

protected:
    void checkComboBoxForError(ComboBox* widget, const QString& errorText);
    void checkComboBoxForError(QComboBox* widget, const QString& errorText);

    virtual void setupConnections();

protected:
    MainWindow * mainWindow;
    QGridLayout * entityLayout;
    QObject * entity;

    QString editedStyle;
    QString invalidStyle;
    bool m_entityEdited;
};

#endif // ENTITYHANDLER_H
