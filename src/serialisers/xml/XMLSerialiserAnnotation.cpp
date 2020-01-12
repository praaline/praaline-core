#include "annotation/AnnotationTierGroup.h"
#include "annotation/AnnotationTier.h"
#include "annotation/PointTier.h"
#include "annotation/IntervalTier.h"
#include "annotation/SequenceTier.h"
#include "annotation/TreeTier.h"
#include "annotation/RelationTier.h"
#include "structure/AnnotationStructure.h"

#include "serialisers/xml/XMLSerialiserAnnotation.h"

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
