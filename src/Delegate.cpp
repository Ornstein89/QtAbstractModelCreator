#include "Delegate.h"

#include <QComboBox>
#include <QLineEdit>

Delegate::Delegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    listTypes << "QString" << "int" << "double" << "char" << "undigned int";
}

QWidget *Delegate::createEditor(QWidget *parent,
                                const QStyleOptionViewItem &/*option*/,
                                const QModelIndex &index) const
{

    if(index.column() == 1)
    {
        // create and return custom widget
        QComboBox *editor = new QComboBox(parent);
        editor->addItems(listTypes);
        editor->setEditable(true);
        return editor;
        //break;
    }
    else
    {
        QLineEdit *editor = new QLineEdit(parent);
        editor->setPlaceholderText("property1"); // TODO number
        return editor;
        //break;
    }
}

void Delegate::setEditorData(QWidget *editor,
                             const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();

    if(index.column() == 1)
    {
        QComboBox * ed = static_cast<QComboBox*>(editor);
        ed->addItems(listTypes);
        ed->setItemText(-1, value);

        // **
        //QStringListModel* cbModel = new QStringListModel();
        //ed->setModel(cbModel);
        // **

        // ***
        //QString textToFind = "abc";
        //int idx = ed->findText(value);
        //ed->setCurrentIndex(idx);
        // ***

        //break;
    }
    else
    {
        QLineEdit * ed = static_cast<QLineEdit*>(editor);
        ed->setText(value);
        //break;
    }

}

void Delegate::setModelData(QWidget *editor,
                            QAbstractItemModel *model,
                            const QModelIndex &index) const
{
    QString value;

    if(index.column() == 1)
    {
        QComboBox * ed = static_cast<QComboBox*>(editor);
        value = ed->currentText();
        //break;
    }
    else
    {
        QLineEdit * ed = static_cast<QLineEdit*>(editor);
        value = ed->text();
        //break;
    }

    model->setData(index, value, Qt::EditRole);
}

void Delegate::updateEditorGeometry(QWidget *editor,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
