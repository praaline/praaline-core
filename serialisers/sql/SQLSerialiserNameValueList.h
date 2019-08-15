#ifndef SQLSERIALISERNAMEVALUELIST_H
#define SQLSERIALISERNAMEVALUELIST_H

/*
    Praaline - Core module - SQL Serialisers
    Copyright (c) 2011-2019 George Christodoulides

    This program or module is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version. It is provided
    for educational purposes and is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
    the GNU General Public License for more details.
*/

#include <QString>
#include <QMap>
#include <QPointer>
#include <QSqlDatabase>

#include "pncore_global.h"
#include "SQLSerialiserBase.h"
#include "SQLSchemaProxyBase.h"
#include "structure/NameValueList.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class SQLSerialiserNameValueList : public SQLSerialiserBase, public SQLSchemaProxyBase
{
public:
    enum NameValueListType {
        Metadata   = 10,
        Annotation = 20
    };

    // ==========================================================================================================================
    // Name-value lists
    // ==========================================================================================================================
    static bool initialiseNameValueListSchema(QSqlDatabase &db);
    static bool upgradeNameValueListSchema(QSqlDatabase &db);
    static NameValueList *getNameValueList(const QString &listID, NameValueListType listType, QSqlDatabase &db);
    static QStringList getAllNameValueListIDs(NameValueListType listType, QSqlDatabase &db);
    static QMap<QString, QPointer<NameValueList> > getAllNameValueLists(NameValueListType listType, QSqlDatabase &db);
    static bool createNameValueList(NameValueList *newList, NameValueListType listType, QSqlDatabase &db);
    static bool updateNameValueList(NameValueList *list, NameValueListType listType, QSqlDatabase &db);
    static bool deleteNameValueList(const QString &listID, NameValueListType listType, QSqlDatabase &db);
    static bool checkNameValueListExists(const QString &listID, NameValueListType listType, QSqlDatabase &db);

private:
    static QString getTableName(const QString &listID, NameValueListType listType);

    SQLSerialiserNameValueList() {}
};

PRAALINE_CORE_END_NAMESPACE

#endif // SQLSERIALISERNAMEVALUELIST_H
