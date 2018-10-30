#include "structure/AnnotationStructure.h"
#include "annotation/AnnotationTierGroup.h"
#include "annotation/AnnotationTier.h"
#include "annotation/PointTier.h"
#include "annotation/IntervalTier.h"

#include "JSONSerialiserAnnotation.h"

namespace Praaline {
namespace Core {

// public static
QJsonObject JSONSerialiserAnnotation::saveTiers(AnnotationTierGroup *tiers, AnnotationStructure *structure)
{
    return QJsonObject();
}

// public static
QJsonObject JSONSerialiserAnnotation::saveTier(AnnotationTier *tier, AnnotationStructure *structure)
{
    return QJsonObject();
}

// public static
AnnotationTierGroup *JSONSerialiserAnnotation::loadTiers(AnnotationStructure *structure, QJsonObject &xml)
{
    return nullptr;
}

// public static
AnnotationTier *JSONSerialiserAnnotation::loadTier(AnnotationStructure *structure, QJsonObject &xml)
{
    return nullptr;
}


} // namespace Core
} // namespace Praaline
