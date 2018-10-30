#include "structure/AnnotationStructure.h"
#include "annotation/AnnotationTierGroup.h"
#include "annotation/AnnotationTier.h"
#include "annotation/PointTier.h"
#include "annotation/IntervalTier.h"
#include "annotation/SequenceTier.h"
#include "annotation/TreeTier.h"
#include "annotation/RelationTier.h"

#include "XMLSerialiserAnnotation.h"

namespace Praaline {
namespace Core {

XMLSerialiserAnnotation::XMLSerialiserAnnotation()
{
}

XMLSerialiserAnnotation::~XMLSerialiserAnnotation()
{
}

// public static
bool XMLSerialiserAnnotation::saveTier(AnnotationTier *tier, AnnotationStructure *structure, QXmlStreamWriter &xml)
{

    return false;
}

// public static
bool XMLSerialiserAnnotation::saveTiers(AnnotationTierGroup *tiers, AnnotationStructure *structure, QXmlStreamWriter &xml)
{
    return false;
}

// public static
AnnotationTier *XMLSerialiserAnnotation::loadTier(AnnotationStructure *structure, QXmlStreamReader &xml)
{
    return nullptr;
}

// public static
AnnotationTierGroup *XMLSerialiserAnnotation::loadTiers(AnnotationStructure *structure, QXmlStreamReader &xml)
{
    return nullptr;
}

} // namespace Core
} // namespace Praaline
