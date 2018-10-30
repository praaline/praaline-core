#ifndef DATASETDEFINITION_H
#define DATASETDEFINITION_H

/*
    Praaline - Core module - Queries and Datasets
    Copyright (c) 2011-2018 George Christodoulides

    This program or module is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version. It is provided
    for educational purposes and is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
    the GNU General Public License for more details.
*/

#include "pncore_global.h"
#include <QString>
#include <QPair>
#include <QVariantHash>

namespace Praaline {
namespace Core {

struct DatasetDefinitionData;

class PRAALINE_CORE_SHARED_EXPORT DatasetDefinition
{
public:
    class Column {
    public:
        QString columnName;
        QString levelID;
        QString attributeID;
        QString function;
        QVariantHash parameters;
    };

    DatasetDefinition();
    ~DatasetDefinition();

    QString datasetName() const;
    void setDatasetName(const QString &name);

    QString minimalLevelID() const;
    void setMinimalLevelID(const QString &levelID);

    QList<Column> columns() const;
    Column column(int index) const;
    int columnCount() const;
    void addColumn(const Column &column);
    void addColumns(const QList<Column> &columns);
    void removeColumn(int index);
    void clear();

private:
    DatasetDefinitionData *d;
};

} // namespace Core
} // namespace Praaline

#endif // DATASETDEFINITION_H
