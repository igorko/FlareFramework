#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QCheckBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_itemswidget.h"
#include "lineedit.h"
#include "spinbox.h"
#include "doublespinbox.h"
#include "checkbox.h"
#include "iconchooser.h"
#include "stringlistwidget.h"
#include "lootanimationwidget.h"
#include "twospinbox.h"
#include "twostringlists.h"
#include "combobox.h"
#include "elementslist.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    menuBar()->setNativeMenuBar(false);

    predefinedNameTypeElements[ITEM_TYPES] = -1;
    predefinedNameTypeElements[ITEMS] = -1;
    predefinedNameTypeElements[ITEM_QUALITIES] = -1;
    predefinedNameTypeElements[ITEM_SETS] = -1;
    predefinedNameTypeElements[EFFECTS] = -1;
    predefinedNameTypeElements[POWERS] = -1;
    predefinedNameTypeElements[QUEST_LOG] = -1;
    predefinedNameTypeElements[CUTSCENE] = -1;
    predefinedNameTypeElements[NPC] = -1;


    ParseAttributesXML();

    setMenusEnabled(false);
    disableAllTabsExceptIndex(0);

    // add tabs and not disable unselected, for testing
    BuildUI();

    modPath = "";

    setupConnections();

    connect(ui->Items, SIGNAL(itemsNotEdited()), this, SLOT(disableSaving()));
    connect(ui->Items, SIGNAL(itemsWereEdited()), this, SLOT(enableSaving()));
}

void MainWindow::setupConnections()
{
    connect(ui->Items->ui->itemClose, SIGNAL(clicked()), SLOT(itemClose()));

    connect(ui->actionClose_Mod, SIGNAL(triggered()), SLOT(Close_Mod()));

    connect(ui->actionAdd_Item, SIGNAL(triggered()), SLOT(Add_Item()));

    connect(ui->actionSave_Mod, SIGNAL(triggered()), SLOT(Save_Mod()));

    connect(ui->actionQuit, SIGNAL(triggered()), SLOT(Quit()));

    connect(ui->actionAbout, SIGNAL(triggered()), SLOT(About()));

    connect(ui->actionOpen_Mod, SIGNAL(triggered()), SLOT(Open_Mod()));

    connect(ui->actionNew_Mod, SIGNAL(triggered()), SLOT(New_Mod()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enableSaving()
{
    QList<QAction*> actions = menuBar()->actions();
    actions.at(MENU_FILE)->menu()->actions().at(2)->setEnabled(true);
}

void MainWindow::disableSaving()
{
    QList<QAction*> actions = menuBar()->actions();
    actions.at(MENU_FILE)->menu()->actions().at(2)->setEnabled(false);
}

void MainWindow::itemClose()
{
    disableAllTabsExceptIndex(TAB_MAIN);
    ui->Items->clearItemsList();
}

void MainWindow::disableAllTabsExceptIndex(int index)
{
    for (int i = 0; i < ui->tabWidget->count(); i++)
    {
        ui->tabWidget->setTabEnabled(i, false);
    }
    if (index >= 0 && index < ui->tabWidget->count())
    {
        ui->tabWidget->setTabEnabled(index, true);
        ui->tabWidget->setCurrentIndex(index);
    }
}

void MainWindow::setMenusEnabled(bool state)
{
    QList<QAction*> actions = menuBar()->actions();

    actions.at(MENU_FILE)->menu()->actions().at(0)->setEnabled(!state);
    actions.at(MENU_FILE)->menu()->actions().at(1)->setEnabled(!state);
    actions.at(MENU_FILE)->menu()->actions().at(2)->setEnabled(state);
    actions.at(MENU_FILE)->menu()->actions().at(3)->setEnabled(state);

    actions.at(MENU_CREATURES)->menu()->actions().at(0)->setEnabled(state);
    actions.at(MENU_CREATURES)->menu()->actions().at(1)->setEnabled(state);

    for (int i = 0; i < 9; i++)
    {
        actions.at(MENU_MENUS)->menu()->actions().at(0)->menu()->actions().at(i)->setEnabled(state);
    }

    actions.at(MENU_MENUS)->menu()->actions().at(1)->menu()->actions().at(0)->setEnabled(state);
    actions.at(MENU_MENUS)->menu()->actions().at(1)->menu()->actions().at(1)->setEnabled(state);
    actions.at(MENU_MENUS)->menu()->actions().at(1)->menu()->actions().at(2)->setEnabled(state);

    actions.at(MENU_STUFF)->menu()->actions().at(0)->setEnabled(state);
    actions.at(MENU_STUFF)->menu()->actions().at(1)->setEnabled(state);

    actions.at(MENU_STORY)->menu()->actions().at(0)->setEnabled(state);
}

void MainWindow::Close_Mod()
{
    if (modPath == "") return;
    if (ui->Items->itemsAreEdited())
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Save mod", "Save mod before closing?", QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            ui->Items->saveItems(modPath);
        }
    }
    modPath = "";
    setMenusEnabled(false);
    ui->Items->clearItemsList();

    CloseAll();
}

void MainWindow::CloseAll()
{
    disableAllTabsExceptIndex(TAB_MAIN);
    //ToDo
}

void MainWindow::ReadNameTypeElementAttributes(QString elementName)
{
    NameTypeElementAttributes elementAttributes;
    while(xml.readNext())
    {
        if(xml.isEndElement() && xml.name() == "class")
        {
            m_nameTypeElements.insert(elementName, elementAttributes);
            break;
        }
        else if(xml.isStartElement() && xml.name() == "description")
        {
            m_nameTypeElementDescriptions[elementName] = xml.readElementText();
        }
        else if(xml.isStartElement())
        {
            QXmlStreamAttributes attributes = xml.attributes();
            if (!attributes.empty())
            {
                QString description = xml.readElementText();
                elementAttributes.insert(attributes.value("name").toString(),
                    qMakePair(attributes.value("type").toString(), description));
            }
        }
    }
}

bool MainWindow::ParseAttributesXML()
{
    QFile attributesXML("../FlareFramework/Resources/code_documentation.xml");

    if(!attributesXML.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }

    xml.setDevice(&attributesXML);

    if (xml.readNextStartElement())
    {
        if (xml.name() == "classes")
        {
            while(xml.readNextStartElement())
            {
                if (xml.name() == "class" && xml.attributes().hasAttribute("name")
                    && predefinedNameTypeElements.contains(xml.attributes().value("name").toString())
                   )
                {
                    ReadNameTypeElementAttributes(xml.attributes().value("name").toString());
                }
                else
                    xml.skipCurrentElement();
            }
        }
        else
        {
            return false;
        }
    }

    attributesXML.close();

    return true;
}

void MainWindow::Add_Item()
{
    // for testing
    //disableAllTabsExceptIndex(TAB_ITEMS);

    if (!QDir(modPath + QDir::separator() + "items").exists())
        QDir().mkdir(modPath + QDir::separator() + "items");

    //QFile itemsFile(filepath);
    //if (!itemsFile.exists())
    //    itemsFile.Create();

    std::string path = (modPath + QDir::separator()).toUtf8().constData();
    itemsHandler = new ItemsHandler(this);
    itemsHandler->loadItems(path);
    ui->Items->loadItems(path);
}

void MainWindow::Save_Mod()
{
    QString filename = modPath + QDir::separator() + "items" + QDir::separator() + "items.txt";
    ui->Items->saveItems(filename.toUtf8().constData());
    //ToDo

}

void MainWindow::Quit()
{
    QApplication::quit();
}

void MainWindow::About()
{
    QString msg = "FLARE Game Development Environment v0.1";
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setText(msg);
    msgBox->exec();
}

void MainWindow::Open_Mod()
{
    newMod = false;
    QString path = QFileDialog::getExistingDirectory(this, QObject::tr("Select mod folder"));

    if (!path.isEmpty()){
        modPath = path;
        setMenusEnabled(true);
        disableSaving();
    }
}

void MainWindow::New_Mod()
{
    newMod = true;
    QString path = QFileDialog::getExistingDirectory(this, QObject::tr("Select mod folder"));
    if (!path.isEmpty()){
        modPath = path;
        setMenusEnabled(true);
        disableSaving();
    }
}

void MainWindow::BuildUI()
{
    QMap<QString, NameTypeElementAttributes>::iterator end = m_nameTypeElements.end();
    for (QMap<QString, NameTypeElementAttributes>::iterator it = m_nameTypeElements.begin(); it != end; ++it)
    {
        QString widgetTabName = it.key();
        int rowOnTab = 0;
        int columnOntab = 0;
        QScrollArea * tab = new QScrollArea();
        tab->setWidgetResizable(true);
        QWidget * widget = new QWidget();
        tab->setWidget(widget);
        QGridLayout * layout = new QGridLayout();
        widget->setLayout(layout);
        tab->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tab->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        layout->addWidget(new ElementsList(),
                          rowOnTab, columnOntab, Qt::AlignLeft | Qt::AlignTop);

        columnOntab++;

        NameTypeElementAttributes attributes = it.value();
        NameTypeElementAttributes::iterator attrEnd = attributes.end();
        for (NameTypeElementAttributes::iterator attrIt = attributes.begin(); attrIt != attrEnd; ++attrIt)
        {
            QString attribute = attrIt.key();
            QString attrType = attrIt.value().first;
            if (attrType == "integer" || attrType == "duration" || attrType == "power_id")
            {
                layout->addWidget(new SpinBox(attribute, attributes[attribute].second),
                                  rowOnTab, columnOntab, Qt::AlignLeft | Qt::AlignTop);
            }
            else if (attrType == "icon_id")
            {
                layout->addWidget(new IconChooser(attribute),
                                  rowOnTab, columnOntab, Qt::AlignLeft | Qt::AlignTop);
            }
            else if (attrType == "float")
            {
                layout->addWidget(new DoubleSpinBox(attribute, attributes[attribute].second),
                                  rowOnTab, columnOntab, Qt::AlignLeft | Qt::AlignTop);
            }
            else if (attrType == "bool")
            {
                layout->addWidget(new CheckBox(attribute, attributes[attribute].second),
                                  rowOnTab, columnOntab, Qt::AlignLeft | Qt::AlignTop);
            }
            else if (attrType == "string")
            {
                layout->addWidget(new LineEdit(attribute, attributes[attribute].second),
                                  rowOnTab, columnOntab, Qt::AlignLeft | Qt::AlignTop);
            }
            else if (attrType == "stringlist")
            {
                layout->addWidget(new StringListWidget(attribute, attributes[attribute].second),
                                  rowOnTab, columnOntab, Qt::AlignLeft | Qt::AlignTop);
            }
            else if (attrType == "integer,integer")
            {
                layout->addWidget(new TwoSpinBox(attribute, attributes[attribute].second),
                                  rowOnTab, columnOntab, Qt::AlignLeft | Qt::AlignTop);
            }
            else if (attrType == "repeatable(integer,integer)")
            {
                layout->addWidget(new TwoStringLists(attribute, attributes[attribute].second),
                                  rowOnTab, columnOntab, Qt::AlignLeft | Qt::AlignTop);
            }
            else if (attrType == "filename")
            {
                layout->addWidget(new ComboBox(attribute, attributes[attribute].second),
                                  rowOnTab, columnOntab, Qt::AlignLeft | Qt::AlignTop);
            }
            else if (attrType == "filename (string), min quantity (int), max quantity (int)")
            {
                layout->addWidget(new LootAnimationWidget(attribute),
                                  rowOnTab, columnOntab, Qt::AlignLeft | Qt::AlignTop);
            }
            else
            {
                QLabel * label = new QLabel();
                label->setText("UNSUPPORTED TYPE");
                label->setMinimumHeight(46);
                label->resize(231, 46);
                label->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
                layout->addWidget(label, rowOnTab, columnOntab, Qt::AlignLeft | Qt::AlignTop);
            }

            columnOntab++;
            if (columnOntab == 4)
            {
                columnOntab = 0;
                rowOnTab++;
            }
        }
        int tabIndex = ui->tabWidget->addTab(tab, widgetTabName);
        ui->tabWidget->setTabToolTip(tabIndex, m_nameTypeElementDescriptions[widgetTabName]);
        predefinedNameTypeElements[widgetTabName] = tabIndex;
    }
}
