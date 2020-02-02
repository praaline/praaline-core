#ifndef SQLSERIALISERBASE_H
#define SQLSERIALISERBASE_H

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

#include "PraalineCore/PraalineCore_Global.h"

namespace QSqlMigrator {
namespace Migrations {
class Migration;
}
}

PRAALINE_CORE_BEGIN_NAMESPACE

struct SQLSerialiserBaseData;

class SQLSerialiserBase
{
public:
    enum DatabaseSystem {
        Sqlite,
        MySQL,
        Postgres
    };

    SQLSerialiserBase();
    ~SQLSerialiserBase();

    static bool applyMigration(const QString &migrationName, const QSqlMigrator::Migrations::Migration *migration,
                               QSqlDatabase &db);

    static int getPraalineSchemaVersion(QSqlDatabase &db);
    static bool setPraalineSchemaVersion(int version, QSqlDatabase &db);
    static bool upgradeSchema(QSqlDatabase &db);

private:
    SQLSerialiserBaseData *d;
};

PRAALINE_CORE_END_NAMESPACE

#endif // SQLSERIALISERBASE_H
