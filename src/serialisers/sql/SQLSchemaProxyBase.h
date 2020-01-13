#ifndef SQLSCHEMAPROXYBASE_H
#define SQLSCHEMAPROXYBASE_H

/*
    Praaline - Core module - SQL Serialisers
    Copyright (c) 2011-2020 George Christodoulides

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
#include <QSqlDatabase>

#include "praaline-core_global.h"
#include "base/DataType.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class SQLSchemaProxyBase
{    
protected:
    static bool addColumnToTable(QString table, QString column, DataType datatype, QSqlDatabase &db);
    static bool renameColumn(QString table, QString oldColumn, QString newColumn, QSqlDatabase &db);
    static bool renameTable(QString oldTable, QString newTable, QSqlDatabase &db);
    static bool deleteColumn(QString table, QString column, QSqlDatabase &db);
    static bool deleteTable(QString table, QSqlDatabase &db);
    static bool retypeColumn(QString tableName, QString columnName, DataType oldDataType, DataType newDataType, QSqlDatabase &db);
};

PRAALINE_CORE_END_NAMESPACE

#endif // SQLSCHEMAPROXYBASE_H
