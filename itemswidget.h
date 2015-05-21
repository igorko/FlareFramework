#ifndef ITEMSWIDGET_H
#define ITEMSWIDGET_H

#include <QWidget>
#include <QListWidgetItem>

class EditorItemManager;

namespace Ui {
class ItemsWidget;
}

class ItemsWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ItemsWidget(QWidget *parent = 0);
    ~ItemsWidget();
    void saveItems(const std::string& path);
    void loadItems(const std::string& path);

    void clearItemsList();

    bool itemsEdited;

signals:

public slots:
	void on_addNewItem_clicked();

	void on_clearBtn_clicked();

	void on_pushBtn_clicked();

	void on_itemsList_itemClicked(QListWidgetItem *item);

private slots:
    void on_absorbMin_valueChanged(int arg1);

    void on_absorbMax_valueChanged(int arg1);

    void on_power_valueChanged(int arg1);

    void on_itemFlavor_textChanged(const QString &arg1);

    void on_itemBook_textChanged(const QString &arg1);

    void on_itemQualityCB_currentTextChanged(const QString &arg1);

    void on_meleeMin_valueChanged(int arg1);

    void on_meleeMax_valueChanged(int arg1);

    void on_rangMin_valueChanged(int arg1);

    void on_rangMax_valueChanged(int arg1);

    void on_mentalMin_valueChanged(int arg1);

    void on_mentalMax_valueChanged(int arg1);

    void on_replacePowerFrom_textChanged();

    void on_replacePowerTo_textChanged();

    void on_disableSlots_textChanged();

    void on_reqPhys_valueChanged(int arg1);

    void on_reqMent_valueChanged(int arg1);

    void on_reqOff_valueChanged(int arg1);

    void on_reqDef_valueChanged(int arg1);

    void on_price_valueChanged(int arg1);

    void on_sellPrice_valueChanged(int arg1);

    void on_maxQuantity_valueChanged(int arg1);

    void on_pickupStatus_textChanged(const QString &arg1);

    void on_powerDesc_textChanged(const QString &arg1);

private:
    Ui::ItemsWidget *ui;

    EditorItemManager * items;

    QString editedStyle;

};

#endif // ITEMSWIDGET_H
