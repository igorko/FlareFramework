#ifndef ITEMSHANDLER_H
#define ITEMSHANDLER_H

#include "entityhandler.h"

class EditorItemManager;

class ItemsHandler : public EntityHandler
{
	Q_OBJECT
public:
    explicit ItemsHandler(MainWindow * _mainWindow, int tabIndex, QObject *parent = 0);
    ~ItemsHandler();
    virtual void saveEntityList(const QString& path);
    virtual void loadEntityList(const std::string& path);
    virtual void clearItemsList();

public slots:
    virtual void clearBtn();
    virtual void pushBtn();
    virtual void selectElementFromList(QListWidgetItem *_item);

    void addNewItem();
    void finishIconAdd();
    void skipIconAdd();
    void requestIconAdd();

protected:
    virtual void setupConnections();

private:
    void collectFileLists(const std::string& path);

    EditorItemManager * items;
};

#endif // ITEMSHANDLER_H
