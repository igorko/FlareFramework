#ifndef ITEMSHANDLER_H
#define ITEMSHANDLER_H

#include <QObject>

class EditorItemManager;
class ComboBox;
class MainWindow;
class QGridLayout;
class QListWidgetItem;
class QComboBox;
class QSpinBox;
class QLineEdit;
class QPlainTextEdit;

class ItemsHandler : public QObject
{
	Q_OBJECT
public:
    explicit ItemsHandler(MainWindow * _mainWindow, QObject *parent = 0);
    ~ItemsHandler();
    void saveItems(const QString& path);
    void loadItems(const std::string& path);

    void clearItemsList();

    bool itemsAreEdited();
    void setItemsAreEdited(bool state);

    static QString qString(std::string value);
    static std::string stdString(QString value);

signals:
    void itemsWereEdited();
    void itemsNotEdited();

public slots:
    QObject * CloseButton();

    void addNewItem();

    void clearBtn();

    void pushBtn();

    void selectItem(QListWidgetItem *_item);

    void finishIconAdd();
    void skipIconAdd();
private slots:
    void requestIconAdd();

private:
    void collectFileLists(const std::string& path);

    void checkComboBoxForError(ComboBox* widget, const QString& errorText);
    void checkComboBoxForError(QComboBox* widget, const QString& errorText);

    void setupConnections();

    MainWindow * mainWindow;
    QGridLayout * itemsLayout;

    EditorItemManager * items;
    bool itemsEdited;

    QString editedStyle;
    QString invalidStyle;
};

#endif // ITEMSHANDLER_H
