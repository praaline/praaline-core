#include "SerialiserAnnotation.h"

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

PRAALINE_CORE_END_NAMESPACE
