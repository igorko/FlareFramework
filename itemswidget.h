#ifndef ITEMSWIDGET_H
#define ITEMSWIDGET_H

#include <QScrollArea>
#include <QListWidgetItem>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QPlainTextEdit>

class EditorItemManager;

namespace Ui {
class ItemsWidget;
}

class ItemsWidget : public QScrollArea
{
	Q_OBJECT
public:
	explicit ItemsWidget(QScrollArea *parent = 0);
    ~ItemsWidget();
    void saveItems(const std::string& path);
    void loadItems(const std::string& path);

    void clearItemsList();

    bool itemsAreEdited();
    void setItemsAreEdited(bool state);

signals:
    void itemsWereEdited();
    void itemsNotEdited();

public slots:
    void addNewItem();

    void clearBtn();

    void pushBtn();

    void itemsList(QListWidgetItem *item);

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

public:
    Ui::ItemsWidget *ui;

private:
    void collectFileLists(const std::string& path);
    QString qString(std::string value);
    std::string stdString(QString value);

    void checkComboBoxForError(QComboBox* widget, const QString& errorText);
    void markNotDefaultSpinBox(QSpinBox* widget, int value, int defaultValue);

    void markNotEmptyLineEdit(QLineEdit* widget, const QString& text);
    void markNotEmptyPlainTextEdit(QPlainTextEdit* widget);

    void selectComboBoxItemByText(QComboBox* widget, const QString& text);
    void setupConnections();

    EditorItemManager * items;

    bool itemsEdited;

    QString editedStyle;
    QString invalidStyle;

};

#endif // ITEMSWIDGET_H
