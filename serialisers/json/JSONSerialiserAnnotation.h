#ifndef JSONSERIALISERANNOTATION_H
#define JSONSERIALISERANNOTATION_H

/*
    Praaline - Core module - JSON Serialisers
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

#include <QString>
#include <QMap>
#include "base/RealTime.h"
#include "JSONSerialiserBase.h"
#include "serialisers/base/SerialiserAnnotation.h"
#include <QJsonObject>

namespace Praaline {
namespace Core {

class AnnotationTier;
class AnnotationTierGroup;
class AnnotationStructure;

class JSONSerialiserAnnotation : public SerialiserAnnotation, public JSONSerialiserBase
{

public:
    static QJsonObject saveTiers(AnnotationTierGroup *tiers, AnnotationStructure *structure);
    static QJsonObject saveTier(AnnotationTier *tier, AnnotationStructure *structure);

    static AnnotationTierGroup *loadTiers(AnnotationStructure *structure, QJsonObject &json);
    static AnnotationTier *loadTier(AnnotationStructure *structure, QJsonObject &json);

private:
    JSONSerialiserAnnotation() {}
    ~JSONSerialiserAnnotation() {}
};

} // namespace Core
} // namespace Praaline

#endif // JSONSERIALISERANNOTATION_H
