#ifndef XMLSERIALISERMETADATASTRUCTURE_H
#define XMLSERIALISERMETADATASTRUCTURE_H

/*
    Praaline - Core module - XML Serialisers
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
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Structure/MetadataStructure.h"
#include "PraalineCore/Structure/MetadataStructureSection.h"
#include "PraalineCore/Structure/MetadataStructureAttribute.h"
#include "PraalineCore/Serialisers/Base/SerialiserMetadataStructure.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT XMLSerialiserMetadataStructure
{
public:
    static bool write(MetadataStructure *structure, const QString &filename);
    static void write(MetadataStructure *structure, QXmlStreamWriter &xml);
    static MetadataStructure *read(const QString &filename);
    static MetadataStructure *read(QXmlStreamReader &xml);
    static void writePartial(MetadataStructure *structure, CorpusObject::Type what, QXmlStreamWriter &xml);
    static MetadataStructure *readPartial(CorpusObject::Type what, QXmlStreamReader &xml);

protected:
    XMLSerialiserMetadataStructure();
    ~XMLSerialiserMetadataStructure();

private:
    static void writeSection(CorpusObject::Type what, MetadataStructureSection *section, QXmlStreamWriter &xml);
    static MetadataStructureSection *readSection(QXmlStreamReader &xml);
    static void writeAttribute(MetadataStructureAttribute *attribute, QXmlStreamWriter &xml);
    static MetadataStructureAttribute  *readAttribute(QXmlStreamReader &xml);

    static QString xmlElementName_Structure;
    static QString xmlElementName_Section;
    static QString xmlElementName_Attribute;
};

PRAALINE_CORE_END_NAMESPACE

#endif // XMLSERIALISERMETADATASTRUCTURE_H
