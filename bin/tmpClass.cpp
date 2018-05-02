#include "<<fileName>>.h"
#include <QDebug>

<<objClassName>>::<<objClassName>>(<<listCopyConstructorParameters>>)
    : <<listPrivateAssign1>>
{
	<<listPrivateAssign2>>
}

<<listGetMethodsDefinitions>>

<<modelClassName>>::<<modelClassName>>(QObject *parent)
    : QAbstractListModel(parent)
{
    //...
}

void <<modelClassName>>::addItem(const <<objClassName>> &newItem)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_items << newItem;
    endInsertRows();
}

int <<modelClassName>>::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return m_items.count();
}

QVariant <<modelClassName>>::data(const QModelIndex & index,
								int role) const
{
    if (index.row() < 0 || (index.row() >= m_items.count()))
        return QVariant();
    
	<<listReturnByRole>>
	
    return QVariant();
}

QHash<int, QByteArray> <<modelClassName>>::roleNames() const
{
    QHash<int, QByteArray> roles;
    <<listRolesAndNames>>
    return roles;
}

QVariantMap <<modelClassName>>::get(int idx) const
{
    QVariantMap map;
    foreach(int k, roleNames().keys())
    {
        map[roleNames().value(k)] = data(index(idx, 0), k);
    }
    return map;
}

void <<modelClassName>>::clear()
{
    beginRemoveRows(QModelIndex(), 0, rowCount()-1);
    m_items.clear();
    endRemoveRows();
}

<<controllerClassName>>::<<controllerClassName>>()
    :QObject()
{
    // ...
}
