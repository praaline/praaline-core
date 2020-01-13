#ifndef SQLSERIALISERANNOTATIONSTRUCTURE_H
#define SQLSERIALISERANNOTATIONSTRUCTURE_H

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

#include <QSqlDatabase>

#include "praaline-core_global.h"
#include "structure/AnnotationStructure.h"
#include "serialisers/sql/SQLSchemaProxyBase.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class SQLSerialiserAnnotationStructure : public SQLSchemaProxyBase
{
public:
    static bool initialiseAnnotationStructureTables(QSqlDatabase &db);

    static bool loadAnnotationStructure(AnnotationStructure *structure, QSqlDatabase &db);
    static bool saveAnnotationStructure(AnnotationStructure *structure, QSqlDatabase &db);

    static bool createAnnotationLevel(AnnotationStructureLevel *newLevel, QSqlDatabase &db);
    static bool updateAnnotationLevel(AnnotationStructureLevel *updatedLevel, QSqlDatabase &db);
    static bool renameAnnotationLevel(const QString &levelID, const QString &newLevelID, QSqlDatabase &db);
    static bool deleteAnnotationLevel(const QString &levelID, QSqlDatabase &db);

    static bool createAnnotationAttribute(const QString &levelID, AnnotationStructureAttribute *newAttribute, QSqlDatabase &db);
    static bool updateAnnotationAttribute(const QString &levelID, AnnotationStructureAttribute *updatedAttribute, QSqlDatabase &db);
    static bool renameAnnotationAttribute(const QString &levelID, const QString &attributeID, const QString &newAttributeID, QSqlDatabase &db);
    static bool retypeAnnotationAttribute(const QString &levelID, const QString &attributeID, const DataType &newDataType, QSqlDatabase &db);
    static bool deleteAnnotationAttribute(const QString &levelID, const QString &attributeID, QSqlDatabase &db);

private:
    SQLSerialiserAnnotationStructure() {}
};

PRAALINE_CORE_END_NAMESPACE

#endif // SQLSERIALISERANNOTATIONSTRUCTURE_H
