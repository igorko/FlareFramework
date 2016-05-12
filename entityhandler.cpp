#include "entityhandler.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "iconchooser.h"
#include "ui_iconchooser.h"

#include "elementslist.h"
#include "ui_elementslist.h"

#include "lootanimationwidget.h"
#include "ui_lootanimationwidget.h"

#include "controlframe.h"
#include "ui_controlframe.h"

#include "combobox.h"
#include "ui_combobox.h"

#include "stringlistwidget.h"
#include "ui_stringlistwidget.h"

#include "comboboxkeyvaluelist.h"
#include "ui_comboboxkeyvaluelist.h"

#include "lineedit.h"
#include "ui_lineedit.h"

#include "spinbox.h"
#include "ui_spinbox.h"

#include "doublespinbox.h"
#include "ui_doublespinbox.h"

#include "twospinbox.h"
#include "ui_twospinbox.h"

#include "checkbox.h"
#include "ui_checkbox.h"

#include "twostringlists.h"
#include "ui_twostringlists.h"

#include <QMetaProperty>
#include <QTextBlock>

EntityHandler::EntityHandler(MainWindow * _mainWindow, QObject *parent) :
    mainWindow(_mainWindow),
    entityLayout(NULL),
    entity(NULL),
    QObject(parent),
    editedStyle("background-color:#66FF99;"),
    invalidStyle("background-color:#FF3333;"),
    m_entityEdited(false)
{

}

void EntityHandler::clearItemsList()
{
    for (int i = 0; i < entityLayout->count(); i++)
    {
        QWidget * widget = entityLayout->itemAt(i)->widget();

        if (widget && widget->accessibleName() == "elementslist")
        {
            dynamic_cast<ElementsList*>(widget)->ui->itemsList->clear();
            break;
        }
    }
    setEntityEdited(false);
}

void EntityHandler::checkComboBoxForError(ComboBox *widget, const QString &errorText)
{
    if (widget->ui->comboBox->count() == 0)
    {
        widget->ui->comboBox->setStyleSheet(invalidStyle);
        widget->ui->comboBox->setToolTip(errorText);
    }
    else
    {
        widget->ui->comboBox->setStyleSheet("");
        widget->ui->comboBox->setToolTip("");
    }
}

void EntityHandler::checkComboBoxForError(QComboBox *widget, const QString &errorText)
{
    if (widget->count() == 0)
    {
        widget->setStyleSheet(invalidStyle);
        widget->setToolTip(errorText);
    }
    else
    {
        widget->setStyleSheet("");
        widget->setToolTip("");
    }
}

void EntityHandler::setupConnections()
{
    for (int i = 0; i < entityLayout->count(); i++)
    {
        QWidget * widget = entityLayout->itemAt(i)->widget();

        if (widget && widget->accessibleName() == "controlframe")
        {
            ControlFrame * controlFrame = dynamic_cast<ControlFrame*>(widget);
            connect(controlFrame->ui->addNewItem, SIGNAL(clicked()), SLOT(addNewItem()));
            connect(controlFrame->ui->clearBtn, SIGNAL(clicked()), SLOT(clearBtn()));
            connect(controlFrame->ui->pushBtn, SIGNAL(clicked()), SLOT(pushBtn()));
        }
        else if (widget && widget->accessibleName() == "elementslist")
        {
            ElementsList * elementsList = dynamic_cast<ElementsList*>(widget);
            connect(elementsList->ui->itemsList, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(selectElementFromList(QListWidgetItem*)));
        }
    }
}

bool EntityHandler::entityEdited()
{
    return m_entityEdited;
}

void EntityHandler::setEntityEdited(bool state)
{
    if (state)
        emit entityWasEdited();
    else
        emit entityNotEdited();
    m_entityEdited = state;
}

QObject *EntityHandler::CloseButton()
{
    for (int i = 0; i < entityLayout->count(); i++)
    {
        QWidget * widget = entityLayout->itemAt(i)->widget();

        if (widget && widget->accessibleName() == "controlframe")
        {
            return dynamic_cast<ControlFrame*>(widget)->ui->itemClose;
        }
    }

    return NULL;
}

void EntityHandler::pushBtn()
{
    if (entity == NULL)
        return;

    int index = -1;
    for (int i = 0; i < entityLayout->count(); i++)
    {
        QWidget * widget = entityLayout->itemAt(i)->widget();
        if (widget == NULL)
        {
            continue;
        }
        if (widget->accessibleName() == "elementslist")
        {
            index = dynamic_cast<ElementsList*>(widget)->ui->itemsList->currentItem()->data(Qt::UserRole).toInt();
            break;
        }
    }

    const QMetaObject* metaObject = entity->metaObject();
    for(int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i)
    {
        QString propertyName = QString::fromLatin1(metaObject->property(i).name());

        for (int i = 0; i < entityLayout->count(); i++)
        {
            QWidget * widget = entityLayout->itemAt(i)->widget();
            if (widget == NULL)
            {
                continue;
            }
            if (widget->accessibleName() == propertyName)
            {
                if (QString(widget->metaObject()->className()) == "LineEdit")
                {
                    entity->setProperty(propertyName.toStdString().c_str(),
                        dynamic_cast<LineEdit*>(widget)->ui->lineEdit->text());
                }
                else if (QString(widget->metaObject()->className()) == "SpinBox")
                {
                    entity->setProperty(propertyName.toStdString().c_str(),
                        dynamic_cast<SpinBox*>(widget)->ui->spinBox->value());
                }
                else if (QString(widget->metaObject()->className()) == "CheckBox")
                {
                    entity->setProperty(propertyName.toStdString().c_str(),
                        dynamic_cast<CheckBox*>(widget)->ui->checkBox->isChecked());
                }
                else if (QString(widget->metaObject()->className()) == "TwoStringLists")
                {
                    QTextDocument* from = dynamic_cast<TwoStringLists*>(widget)->ui->edit_1->document();
                    QTextDocument* to   = dynamic_cast<TwoStringLists*>(widget)->ui->edit_2->document();

                    QList<QVariant> values;
                    for (int i = 0; i < from->lineCount(); i++)
                    {
                        if (from->findBlockByLineNumber(i).text().isEmpty() || to->findBlockByLineNumber(i).text().isEmpty())
                            break;
                        QStringList list;
                        list << from->findBlockByLineNumber(i).text() << to->findBlockByLineNumber(i).text();
                        values.append(list);
                    }
                    entity->setProperty(propertyName.toStdString().c_str(), values);
                }
                else if (QString(widget->metaObject()->className()) == "StringListWidget")
                {
                    QTextDocument* list = dynamic_cast<StringListWidget*>(widget)->ui->list->document();

                    QList<QVariant> values;
                    for (int i = 0; i < list->lineCount(); i++)
                    {
                        if (list->findBlockByLineNumber(i).text().isEmpty())
                            break;
                        values.append(list->findBlockByLineNumber(i).text());
                    }
                    entity->setProperty(propertyName.toStdString().c_str(), values);
                }
            }
        }
    }
    setEntityEdited(true);
}

void EntityHandler::clearBtn()
{
    for (int i = 0; i < entityLayout->count(); i++)
    {
        QWidget * widget = entityLayout->itemAt(i)->widget();
        if (widget == NULL)
        {
            continue;
        }
        QString name = QString(widget->metaObject()->className());
        if (name == "ComboBox")
        {
            dynamic_cast<ComboBox*>(widget)->setCurrentIndex(0);
        }
        else if (name == "SpinBox")
        {
            dynamic_cast<SpinBox*>(widget)->setValue(0);
        }
        else if (name == "DoubleSpinBox")
        {
            dynamic_cast<DoubleSpinBox*>(widget)->setValue(0.0);
        }
        else if (name == "LineEdit")
        {
            dynamic_cast<LineEdit*>(widget)->clear();
        }
        else if (name == "StringListWidget")
        {
            dynamic_cast<StringListWidget*>(widget)->clear();
        }
        else if (name == "TwoSpinBox")
        {
            dynamic_cast<TwoSpinBox*>(widget)->setValue1(0);
            dynamic_cast<TwoSpinBox*>(widget)->setValue2(0);
        }
        else if (name == "TwoStringLists")
        {
            dynamic_cast<TwoStringLists*>(widget)->clear();
        }
        else if (name == "CheckBox")
        {
            dynamic_cast<CheckBox*>(widget)->setChecked(false);
        }
    }
}

#include "API/ItemManager.h"

void EntityHandler::selectElementFromList(QListWidgetItem *_item)
{
    if (entity == NULL)
        return;

    clearBtn();
    for (int i = 0; i < entityLayout->count(); i++)
    {
        QWidget * widget = entityLayout->itemAt(i)->widget();
        if (widget && widget->accessibleName() == "controlframe")
        {
            dynamic_cast<ControlFrame*>(widget)->ui->pushBtn->setEnabled(true);
            break;
        }
    }

    const QMetaObject* metaObject = entity->metaObject();
    for(int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i)
    {
        QString propertyName = QString::fromLatin1(metaObject->property(i).name());

        for (int i = 0; i < entityLayout->count(); i++)
        {
            QWidget * widget = entityLayout->itemAt(i)->widget();
            if (widget == NULL)
            {
                continue;
            }
            QString className = QString(widget->metaObject()->className());
            if (widget->accessibleName() == propertyName)
            {
                if (className == "LineEdit")
                {
                    dynamic_cast<LineEdit*>(widget)->ui->lineEdit->setText(entity->property(propertyName.toStdString().c_str()).toString());
                }
                else if (className == "SpinBox")
                {
                    dynamic_cast<SpinBox*>(widget)->setValue(entity->property(propertyName.toStdString().c_str()).toInt());
                }
                else if (className == "TwoSpinBox")
                {
                    if (propertyName.endsWith("_min"))
                    {
                        dynamic_cast<TwoSpinBox*>(widget)->setValue1(entity->property(propertyName.toStdString().c_str()).toInt());
                    }
                    else if (propertyName.endsWith("_max"))
                    {
                        dynamic_cast<TwoSpinBox*>(widget)->setValue2(entity->property(propertyName.toStdString().c_str()).toInt());
                    }
                }
                else if (className == "TwoStringLists")
                {
                    QList<QVariant> values = entity->property(propertyName.toStdString().c_str()).toList();
                    QVector< QPair<QString,QString> > vector;
                    for(int i = 0; i < values.size(); i++)
                    {
                        vector.append(qMakePair(values[i].toStringList()[0], values[i].toStringList()[1]));
                    }
                    dynamic_cast<TwoStringLists*>(widget)->setValues(vector);
                }
                else if (className == "StringListWidget")
                {
                    QList<QVariant> values = entity->property(propertyName.toStdString().c_str()).toList();
                    QVector<QString> vector;
                    for(int i = 0; i < values.size(); i++)
                    {
                        vector.append(values[i].toString());
                    }
                    dynamic_cast<StringListWidget*>(widget)->setValues(vector);
                }
                else if (className == "ComboBox")
                {
                    dynamic_cast<ComboBox*>(widget)->selectComboBoxItemByText(entity->property(propertyName.toStdString().c_str()).toString());
                }
            }
        }
    }
}

QString EntityHandler::qString(std::string value)
{
    return QString::fromUtf8(value.data(), value.size());
}

std::string EntityHandler::stdString(QString value)
{
    return value.toUtf8().constData();
}
