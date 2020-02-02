#ifndef JSONSERIALISERANNOTATION_H
#define JSONSERIALISERANNOTATION_H

/*
    Praaline - Core module - JSON Serialisers
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
#include <QMap>
#include <QJsonObject>

#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Base/RealTime.h"
#include "PraalineCore/Serialisers/Base/SerialiserAnnotation.h"
#include "PraalineCore/Serialisers/JSON/JSONSerialiserBase.h"

PRAALINE_CORE_BEGIN_NAMESPACE

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

protected:
    JSONSerialiserAnnotation();
    ~JSONSerialiserAnnotation();
};

PRAALINE_CORE_END_NAMESPACE

#endif // JSONSERIALISERANNOTATION_H
