#ifndef JSONSERIALISERMETADATASTRUCTURE_H
#define JSONSERIALISERMETADATASTRUCTURE_H

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

#include <QString>
#include <QJsonObject>

#include "pncore_global.h"
#include "structure/MetadataStructure.h"
#include "serialisers/base/SerialiserMetadataStructure.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT JSONSerialiserMetadataStructure
{
public:
    static bool write(MetadataStructure *structure, const QString &filename);
    static void write(MetadataStructure *structure, QJsonObject &json);
    static MetadataStructure *read(const QString &filename);
    static MetadataStructure *read(QJsonObject &json);
    static void writePartial(MetadataStructure *structure, CorpusObject::Type what, QJsonObject &json);
    static MetadataStructure *readPartial(CorpusObject::Type what, QJsonObject &json);

protected:
    JSONSerialiserMetadataStructure();
    ~JSONSerialiserMetadataStructure();

private:
    static QJsonObject writeSection(CorpusObject::Type what, MetadataStructureSection *section);
    static MetadataStructureSection *readSection(QJsonObject &json);
    static QJsonObject writeAttribute(MetadataStructureAttribute *attribute);
    static MetadataStructureAttribute  *readAttribute(QJsonObject &json);
};

PRAALINE_CORE_END_NAMESPACE

#endif // JSONSERIALISERMETADATASTRUCTURE_H
