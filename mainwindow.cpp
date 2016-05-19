#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QCheckBox>
#include <QLabel>
#include <QScrollArea>

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
#include "controlframe.h"
#include "comboboxkeyvaluelist.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    menuBar()->setNativeMenuBar(false);

    ParseAttributesXML();

    setMenusEnabled(false);

    modPath = "";
}

void MainWindow::setupConnections()
{
    connect(itemsHandler->CloseButton(), SIGNAL(clicked()), SLOT(itemClose()));

    connect(itemsHandler, SIGNAL(entityNotEdited()), this, SLOT(disableSaving()));
    connect(itemsHandler, SIGNAL(entityWasEdited()), this, SLOT(enableSaving()));

    connect(ui->actionClose_Mod, SIGNAL(triggered()), SLOT(Close_Mod()));

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
    itemsHandler->clearItemsList();
}

void MainWindow::disableAllTabs()
{
    for (int i = 0; i < ui->tabWidget->count(); i++)
    {
        ui->tabWidget->setTabEnabled(i, false);
    }
}

void MainWindow::enableAllTabs()
{
    for (int i = 0; i < ui->tabWidget->count(); i++)
    {
        ui->tabWidget->setTabEnabled(i, true);
    }
}

void MainWindow::setMenusEnabled(bool state)
{
    QList<QAction*> actions = menuBar()->actions();

    actions.at(MENU_FILE)->menu()->actions().at(0)->setEnabled(!state);
    actions.at(MENU_FILE)->menu()->actions().at(1)->setEnabled(!state);
    actions.at(MENU_FILE)->menu()->actions().at(2)->setEnabled(state);
    actions.at(MENU_FILE)->menu()->actions().at(3)->setEnabled(state);
}

void MainWindow::Close_Mod()
{
    if (modPath == "") return;
    if (itemsHandler->entityEdited())
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Save mod", "Save mod before closing?", QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            itemsHandler->saveEntityList(modPath);
        }
    }
    modPath = "";
    setMenusEnabled(false);
    itemsHandler->clearItemsList();

    CloseAll();
}

void MainWindow::CloseAll()
{
    disableAllTabs();
    //ToDo
}

void MainWindow::ReadNameTypeElementAttributes(QString elementName)
{
    bool skipElement = false;
    bool typeElement = false;

    NameTypeElementAttributes elementAttributes;
    NameElementAttributes elementTypes;
    while(xml.readNext())
    {
        if(xml.isEndElement() && xml.name() == "class")
        {
            if (!skipElement)
            {
                if (!typeElement)
                {
                    m_classAttributes.insert(elementName, elementAttributes);
                }
                else
                {
                    m_classTypes.insert(elementName, elementTypes);
                }
            }
            break;
        }
        else if(xml.isStartElement() && xml.name() == "description" && !skipElement)
        {
            m_classDescriptions[elementName] = xml.readElementText();
        }
        else if(xml.isStartElement() && !skipElement)
        {
            QXmlStreamAttributes attributes = xml.attributes();
            if (!attributes.empty())
            {
                if (xml.name() != "attribute" && xml.name() != "type")
                {
                    skipElement = true;
                }
                else if (xml.name() == "attribute")
                {
                    QString description = xml.readElementText();
                    elementAttributes.insert(attributes.value("name").toString(),
                        qMakePair(attributes.value("type").toString(), description));
                }
                else // xml.name() == "type"
                {
                    QString description = xml.readElementText();
                    elementTypes.append(qMakePair(attributes.value("name").toString(), description));
                    typeElement = true;
                }
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
                if (xml.name() == "class" && xml.attributes().hasAttribute("name"))
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
    if (!QDir(modPath + QDir::separator() + "items").exists())
        QDir().mkdir(modPath + QDir::separator() + "items");

    //QFile itemsFile(filepath);
    //if (!itemsFile.exists())
    //    itemsFile.Create();

    std::string path = (modPath + QDir::separator()).toUtf8().constData();
    itemsHandler->loadEntityList(path);
}

void MainWindow::loadTab(int index)
{
    if (ui->tabWidget->tabText(index) == ITEMS)
    {
        Add_Item();
    }
}

void MainWindow::Save_Mod()
{
    QString filename = modPath + QDir::separator() + "items" + QDir::separator() + "items.txt";
    itemsHandler->saveEntityList(filename.toUtf8().constData());
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
    enableAllTabs();
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
    enableAllTabs();
}

void MainWindow::selectWidgetWithPredefinedString(QGridLayout * layout, int row, int column,
    QString widgetName, QString widgetDescription, QString attrType, QString valuesList)
{
    QStringList values = valuesList.split(", ");
    for (int i = 0; i < values.size(); i++)
    {
        QString value = values[i];
        if (value.startsWith("\"") && value.endsWith("\""))
        {
            values[i] = value.mid(1, value.size() - 2);
        }
    }
    if (attrType == "predefined_string")
    {
        layout->addWidget(new ComboBox(widgetName, widgetDescription, values),
                          row, column, Qt::AlignLeft | Qt::AlignTop);
    }
    else if (attrType == "list(predefined_string)")
    {
        layout->addWidget(new StringListWidget(widgetName, widgetDescription, values),
                          row, column, Qt::AlignLeft | Qt::AlignTop);
    }
    else if (attrType == "list(predefined_string, int)" || attrType == "repeatable(predefined_string, int)")
    {
        layout->addWidget(new ComboBoxKeyValueList(widgetName, widgetDescription, values),
                          row, column, Qt::AlignLeft | Qt::AlignTop);
    }
}

void MainWindow::BuildUI()
{
    QMap<QString, NameTypeElementAttributes>::iterator end = m_classAttributes.end();
    for (QMap<QString, NameTypeElementAttributes>::iterator it = m_classAttributes.begin(); it != end; ++it)
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
            if (attrType == "int" || attrType == "duration" || attrType == "item_id" || attrType == "power_id")
            {
                layout->addWidget(new SpinBox(attribute, attributes[attribute].second),
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
            else if (attrType == "list(predefined_string)")
            {
                layout->addWidget(new StringListWidget(attribute, attributes[attribute].second,
                                                       QStringList()),
                                  rowOnTab, columnOntab, Qt::AlignLeft | Qt::AlignTop);
            }
            else if (attrType == "int, int")
            {
                layout->addWidget(new TwoSpinBox(attribute, attributes[attribute].second),
                                  rowOnTab, columnOntab, Qt::AlignLeft | Qt::AlignTop);
            }
            else if (attrType == "repeatable(int, int)")
            {
                layout->addWidget(new TwoStringLists(attribute, attributes[attribute].second),
                                  rowOnTab, columnOntab, Qt::AlignLeft | Qt::AlignTop);
            }
            else if (attrType == "filename" || attrType == "predefined_string")
            {
                layout->addWidget(new ComboBox(attribute, attributes[attribute].second,
                                               QStringList()),
                                  rowOnTab, columnOntab, Qt::AlignLeft | Qt::AlignTop);
            }
            else if (attrType == "list(predefined_string, int)" || attrType == "repeatable(predefined_string, int)")
            {
                layout->addWidget(new ComboBoxKeyValueList(attribute, attributes[attribute].second,
                                                           QStringList()),
                                  rowOnTab, columnOntab, Qt::AlignLeft | Qt::AlignTop);
            }
            // item specific
            else if (attrType == "repeatable(filename, int, int)")
            {
                layout->addWidget(new LootAnimationWidget(attribute),
                                  rowOnTab, columnOntab, Qt::AlignLeft | Qt::AlignTop);
            }
            else if (attrType == "icon_id")
            {
                layout->addWidget(new IconChooser(attribute),
                                  rowOnTab, columnOntab, Qt::AlignLeft | Qt::AlignTop);
            }
            else if (attrType.contains("[") &&  attrType.contains("]"))
            {
                // parse predefined stringlist inside [...]
                int start = attrType.indexOf("[");
                int end = attrType.lastIndexOf("]");
                int size = end - start + 1;
                QString list = attrType.mid(start + 1, size - 2);
                attrType.replace(start, size, "predefined_string");

                selectWidgetWithPredefinedString(layout, rowOnTab, columnOntab, attribute,
                                                 attributes[attribute].second, attrType, list);
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
        int tabIndex = -1;
        tabIndex = ui->tabWidget->addTab(tab, widgetTabName);

        ui->tabWidget->setTabToolTip(tabIndex, m_classDescriptions[widgetTabName]);
        if (widgetTabName == ITEMS)
        {
            itemsHandler = new ItemsHandler(this, tabIndex);
        }

        layout->addWidget(new ControlFrame("controlframe"), rowOnTab, columnOntab, Qt::AlignLeft | Qt::AlignTop);
    }

    setupConnections();
    disableAllTabs();

    connect(ui->tabWidget, SIGNAL(currentChanged(int)), SLOT(loadTab(int)));

}

const NameElementAttributes & MainWindow::getClassTypes(QString className)
{
    return m_classTypes[className];
}
