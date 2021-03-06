#ifndef XMLSERIALISERANNOTATIONSTRUCTURE_H
#define XMLSERIALISERANNOTATIONSTRUCTURE_H

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
#include "PraalineCore/Structure/AnnotationStructure.h"
#include "PraalineCore/Structure/AnnotationStructureLevel.h"
#include "PraalineCore/Structure/AnnotationStructureAttribute.h"
#include "PraalineCore/Serialisers/Base/SerialiserAnnotationStructure.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT XMLSerialiserAnnotationStructure : public SerialiserAnnotationStructure
{
public:
    static bool write(AnnotationStructure *data, const QString &filename);
    static void write(AnnotationStructure *data, QXmlStreamWriter &xml);
    static AnnotationStructure *read(const QString &filename);
    static AnnotationStructure *read(QXmlStreamReader &xml);

protected:
    XMLSerialiserAnnotationStructure();
    ~XMLSerialiserAnnotationStructure() override;

private:
    static void writeLevel(AnnotationStructureLevel *level, QXmlStreamWriter &xml);
    static AnnotationStructureLevel *readLevel(QXmlStreamReader &xml);
    static void writeAttribute(AnnotationStructureAttribute *attribute, QXmlStreamWriter &xml);
    static AnnotationStructureAttribute *readAttribute(QXmlStreamReader &xml);

    static QString xmlElementName_Structure;
    static QString xmlElementName_Level;
    static QString xmlElementName_Attribute;
};

PRAALINE_CORE_END_NAMESPACE

#endif // XMLSERIALISERANNOTATIONSTRUCTURE_H
