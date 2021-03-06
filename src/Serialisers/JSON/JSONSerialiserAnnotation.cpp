#include "PraalineCore/Structure/AnnotationStructure.h"
#include "PraalineCore/Annotation/AnnotationTierGroup.h"
#include "PraalineCore/Annotation/AnnotationTier.h"
#include "PraalineCore/Annotation/PointTier.h"
#include "PraalineCore/Annotation/IntervalTier.h"
#include "PraalineCore/Serialisers/JSON/JSONSerialiserAnnotation.h"

PRAALINE_CORE_BEGIN_NAMESPACE

JSONSerialiserAnnotation::JSONSerialiserAnnotation()
{
}

JSONSerialiserAnnotation::~JSONSerialiserAnnotation()
{
}

// public static
QJsonObject JSONSerialiserAnnotation::saveTiers(AnnotationTierGroup *tiers, AnnotationStructure *structure)
{
    Q_UNUSED(tiers)
    Q_UNUSED(structure)
    return QJsonObject();
}

// public static
QJsonObject JSONSerialiserAnnotation::saveTier(AnnotationTier *tier, AnnotationStructure *structure)
{
    Q_UNUSED(tier)
    Q_UNUSED(structure)
    return QJsonObject();
}

// public static
AnnotationTierGroup *JSONSerialiserAnnotation::loadTiers(AnnotationStructure *structure, QJsonObject &json)
{
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return nullptr;
}

// public static
AnnotationTier *JSONSerialiserAnnotation::loadTier(AnnotationStructure *structure, QJsonObject &json)
{
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return nullptr;
}

PRAALINE_CORE_END_NAMESPACE
