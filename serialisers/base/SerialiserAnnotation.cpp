#include "SerialiserAnnotation.h"

namespace Praaline {
namespace Core {

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

} // namespace Core
} // namespace Praaline
