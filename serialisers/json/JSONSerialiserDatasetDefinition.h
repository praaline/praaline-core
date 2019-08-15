#ifndef JSONSERIALISERDATASETDEFINITION_H
#define JSONSERIALISERDATASETDEFINITION_H

/*
    Praaline - Core module - JSON Serialisers
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

#include <QObject>
#include <QPointer>
#include <QString>
#include <QJsonObject>

#include "pncore_global.h"
#include "JSONSerialiserBase.h"
#include "query/DatasetDefinition.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT JSONSerialiserDatasetDefinition : JSONSerialiserBase
{
public:
    static bool saveDatasetDefinition(const DatasetDefinition &definition, const QString &filename);
    static bool saveDatasetDefinition(const DatasetDefinition &definition, QJsonObject &json);
    static bool loadDatasetDefinition(DatasetDefinition &definition, const QString &filename);
    static bool loadDatasetDefinition(DatasetDefinition &definition, QJsonObject &json);

private:
    JSONSerialiserDatasetDefinition();
    ~JSONSerialiserDatasetDefinition();
};

PRAALINE_CORE_END_NAMESPACE

#endif // JSONSERIALISERDATASETDEFINITION_H
