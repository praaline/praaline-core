#include "PraalineCore/Serialisers/Base/SerialiserAnnotation.h"
#include "PraalineCore/Structure/AnnotationStructure.h"
#include "PraalineCore/Structure/AnnotationStructureLevel.h"
#include "PraalineCore/Structure/AnnotationStructureAttribute.h"

PRAALINE_CORE_BEGIN_NAMESPACE

SerialiserAnnotation::SerialiserAnnotation()
{
}

SerialiserAnnotation::~SerialiserAnnotation()
{
}

// static
QStringList SerialiserAnnotation::getEffectiveAttributeIDs(AnnotationStructureLevel *level, const QStringList &attributeIDs)
{
    QStringList effectiveAttributeIDs;
    if (!level) return effectiveAttributeIDs;
    if (attributeIDs.isEmpty())
        effectiveAttributeIDs = level->attributeIDs();
    else {
        foreach (QString attributeID, attributeIDs) {
            if (level->hasAttribute(attributeID))
                effectiveAttributeIDs << attributeID;
        }
    }
    return effectiveAttributeIDs;
}

// static
QStringList SerialiserAnnotation::getEffectiveLevelIDs(AnnotationStructure *structure, const QStringList &levelIDs)
{
    // Check which levels exist in the database (out of those requested)
    // If no specific levels were specified, then retrieve all levels (get this information from the structure object).
    if (levelIDs.isEmpty())
        return structure->levelIDs();
    // Otherwise, we need to check that the levels specified exist and that their parent levels are also retrieved.
    QStringList correctLevelIDs, parentLevelIDs, effectiveLevelIDs;
    foreach (QString levelID, levelIDs) {
        if (structure->hasLevel(levelID)) {
            correctLevelIDs << levelID;
            if (structure->level(levelID)->isLevelTypeDerived()) {
                // Derived levels have a parent level
                parentLevelIDs << structure->level(levelID)->parentLevelID();
            }
        }
    }
    // Start by retrieving the parent levels
    effectiveLevelIDs << parentLevelIDs;
    // Then continue by retrieving the user-specified levels (that really exist), without duplicates
    foreach (QString levelID, correctLevelIDs)
        if (!effectiveLevelIDs.contains(levelID)) effectiveLevelIDs << levelID;
    return effectiveLevelIDs;
}


PRAALINE_CORE_END_NAMESPACE
