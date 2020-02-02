#include "PraalineCore/Annotation/AnnotationTierGroup.h"
#include "PraalineCore/Annotation/AnnotationTier.h"
#include "PraalineCore/Annotation/PointTier.h"
#include "PraalineCore/Annotation/IntervalTier.h"
#include "PraalineCore/Annotation/SequenceTier.h"
#include "PraalineCore/Annotation/TreeTier.h"
#include "PraalineCore/Annotation/RelationTier.h"
#include "PraalineCore/Structure/AnnotationStructure.h"
#include "PraalineCore/Serialisers/XML/XMLSerialiserAnnotation.h"

PRAALINE_CORE_BEGIN_NAMESPACE

XMLSerialiserAnnotation::XMLSerialiserAnnotation()
{
}

XMLSerialiserAnnotation::~XMLSerialiserAnnotation()
{
}

// public static
bool XMLSerialiserAnnotation::saveTier(AnnotationTier *tier, AnnotationStructure *structure, QXmlStreamWriter &xml)
{
    Q_UNUSED(tier)
    Q_UNUSED(structure)
    Q_UNUSED(xml)
    return false;
}

// public static
bool XMLSerialiserAnnotation::saveTiers(AnnotationTierGroup *tiers, AnnotationStructure *structure, QXmlStreamWriter &xml)
{
    Q_UNUSED(tiers)
    Q_UNUSED(structure)
    Q_UNUSED(xml)
    return false;
}

// public static
AnnotationTier *XMLSerialiserAnnotation::loadTier(AnnotationStructure *structure, QXmlStreamReader &xml)
{
    Q_UNUSED(structure)
    Q_UNUSED(xml)
    return nullptr;
}

// public static
AnnotationTierGroup *XMLSerialiserAnnotation::loadTiers(AnnotationStructure *structure, QXmlStreamReader &xml)
{
    Q_UNUSED(structure)
    Q_UNUSED(xml)
    return nullptr;
}

PRAALINE_CORE_END_NAMESPACE
