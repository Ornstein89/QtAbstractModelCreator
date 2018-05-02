#ifndef NOTESLISTCONTROLLER_H
#define NOTESLISTCONTROLLER_H

#include <QAbstractListModel>
#include <QVariant>
#pragma once

class <<objClassName>>
{
public:
    <<objClassName>>(<<listCopyConstructorParameters>>);

	<<listGetMethodsDeclarations>>

private:
	<<listPrivatePropertiesDeclarations>>
};

class <<modelClassName>> : public QAbstractListModel
{
    Q_OBJECT
public:
    enum enmRoles {
		<<listRoles>>
    };

    <<modelClassName>>(QObject *parent = 0);

    void addItem(const <<objClassName>> & newItem);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QVariantMap get(int idx) const;
    void clear();
protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<<<objClassName>>> m_items;

};

class <<controllerClassName>> : public QObject
{
    Q_OBJECT
public:
    <<controllerClassName>>();

    <<modelClassName>> <<modelClassName>>;
};

#endif // NOTESLISTCONTROLLER_H
