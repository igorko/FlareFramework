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

signals:

public slots:
	void on_addNewItem_clicked();

	void on_clearBtn_clicked();

	void on_pushBtn_clicked();

	void on_itemsList_itemClicked(QListWidgetItem *item);

private:
    Ui::ItemsWidget *ui;

	EditorItemManager * items;

};

#endif // ITEMSWIDGET_H
