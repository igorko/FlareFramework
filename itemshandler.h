#ifndef ITEMSHANDLER_H
#define ITEMSHANDLER_H

#include <QObject>

class EditorItemManager;
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

    void itemsList(QListWidgetItem *item);

    void finishIconAdd();
    void skipIconAdd();
private slots:
    void requestIconAdd();

    void absorbMin(int arg1);

    void absorbMax(int arg1);

    void power(int arg1);

    void itemFlavor(const QString &arg1);

    void itemBook(const QString &arg1);

    void meleeMin(int arg1);

    void meleeMax(int arg1);

    void rangMin(int arg1);

    void rangMax(int arg1);

    void mentalMin(int arg1);

    void mentalMax(int arg1);

    void replacePowerFrom();

    void replacePowerTo();

    void disableSlots();

    void reqPhys(int arg1);

    void reqMent(int arg1);

    void reqOff(int arg1);

    void reqDef(int arg1);

    void price(int arg1);

    void sellPrice(int arg1);

    void maxQuantity(int arg1);

    void pickupStatus(const QString &arg1);

    void powerDesc(const QString &arg1);

    void itemName(const QString &arg1);

    void equipFlags();

    void bonusName();

    void bonusValue();

    void addDisableSlot();

    void addEquipFlag();

    void addBonus();

    void lootAnimAdd();

    void animations();

    void animationMin();

    void animationMax();

private:
    void collectFileLists(const std::string& path);

    void checkComboBoxForError(QComboBox* widget, const QString& errorText);
    void markNotDefaultSpinBox(QSpinBox* widget, int value, int defaultValue);

    void markNotEmptyLineEdit(QLineEdit* widget, const QString& text);
    void markNotEmptyPlainTextEdit(QPlainTextEdit* widget);

    void selectComboBoxItemByText(QComboBox* widget, const QString& text);
    void setupConnections();

    MainWindow * mainWindow;
    QGridLayout * itemsLayout;

    EditorItemManager * items;
    bool itemsEdited;

    QString editedStyle;
    QString invalidStyle;
};

#endif // ITEMSHANDLER_H
