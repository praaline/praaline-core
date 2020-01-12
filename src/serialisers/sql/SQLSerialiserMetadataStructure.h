#ifndef SQLSERIALISERMETADATASTRUCTURE_H
#define SQLSERIALISERMETADATASTRUCTURE_H

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

#include <QSqlDatabase>

#include "pncore_global.h"
#include "structure/MetadataStructure.h"
#include "SQLSerialiserBase.h"
#include "SQLSchemaProxyBase.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class SQLSerialiserMetadataStructure : public SQLSchemaProxyBase, public SQLSerialiserBase
{
public:
    static bool initialiseMetadataStructureSchema(QSqlDatabase &db);
    static bool upgradeMetadataStructureSchema(QSqlDatabase &db);
    static bool initialiseMetadataSchema(MetadataStructure *structure, QSqlDatabase &db);
    static bool upgradeMetadataSchema(MetadataStructure *structure, QSqlDatabase &db);

    static bool loadMetadataStructure(MetadataStructure *structure, QSqlDatabase &db);
    static bool saveMetadataStructure(MetadataStructure *structure, QSqlDatabase &db);

    static bool createMetadataSection(CorpusObject::Type type, MetadataStructureSection *newSection, QSqlDatabase &db);
    static bool updateMetadataSection(CorpusObject::Type type, MetadataStructureSection *updatedSection, QSqlDatabase &db);
    static bool deleteMetadataSection(CorpusObject::Type type, const QString &sectionID, QSqlDatabase &db);

    static bool createMetadataAttribute(CorpusObject::Type type, MetadataStructureAttribute *newAttribute, QSqlDatabase &db);
    static bool updateMetadataAttribute(CorpusObject::Type type, MetadataStructureAttribute *updatedAttribute, QSqlDatabase &db);
    static bool renameMetadataAttribute(CorpusObject::Type type, const QString &attributeID, const QString &newAttributeID, QSqlDatabase &db);
    static bool retypeMetadataAttribute(CorpusObject::Type type, const QString &attributeID, const DataType &newDataType, QSqlDatabase &db);
    static bool deleteMetadataAttribute(CorpusObject::Type type, const QString &attributeID, QSqlDatabase &db);

private:
    SQLSerialiserMetadataStructure() {}
};

PRAALINE_CORE_END_NAMESPACE

#endif // SQLSERIALISERMETADATASTRUCTURE_H
