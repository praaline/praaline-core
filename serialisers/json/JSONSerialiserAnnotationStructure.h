#ifndef JSONSERIALISERANNOTATIONSTRUCTURE_H
#define JSONSERIALISERANNOTATIONSTRUCTURE_H

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

#include <QJsonObject>

#include "pncore_global.h"
#include "structure/AnnotationStructure.h"
#include "serialisers/base/SerialiserAnnotationStructure.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT JSONSerialiserAnnotationStructure : public SerialiserAnnotationStructure
{
public:
    static bool write(AnnotationStructure *structure, const QString &filename);
    static void write(AnnotationStructure *structure, QJsonObject &json);
    static AnnotationStructure *read(const QString &filename);
    static AnnotationStructure *read(QJsonObject &json);

private:
    JSONSerialiserAnnotationStructure();
    ~JSONSerialiserAnnotationStructure();

    static QJsonObject writeLevel(AnnotationStructureLevel *level);
    static AnnotationStructureLevel *readLevel(QJsonObject &json);
    static QJsonObject writeAttribute(AnnotationStructureAttribute *attribute);
    static AnnotationStructureAttribute *readAttribute(QJsonObject &json);
};

PRAALINE_CORE_END_NAMESPACE

#endif // JSONSERIALISERANNOTATIONSTRUCTURE_H
