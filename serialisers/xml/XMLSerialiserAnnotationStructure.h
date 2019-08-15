#ifndef XMLSERIALISERANNOTATIONSTRUCTURE_H
#define XMLSERIALISERANNOTATIONSTRUCTURE_H

/*
    Praaline - Core module - XML Serialisers
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
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "pncore_global.h"
#include "structure/AnnotationStructure.h"
#include "serialisers/base/SerialiserAnnotationStructure.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT XMLSerialiserAnnotationStructure : public SerialiserAnnotationStructure
{
public:
    static bool write(AnnotationStructure *data, const QString &filename);
    static void write(AnnotationStructure *data, QXmlStreamWriter &xml);
    static AnnotationStructure *read(const QString &filename);
    static AnnotationStructure *read(QXmlStreamReader &xml);

private:
    XMLSerialiserAnnotationStructure() {}
    ~XMLSerialiserAnnotationStructure() {}

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
