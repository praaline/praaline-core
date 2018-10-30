#include "SerialiserMetadata.h"
#include "structure/MetadataStructure.h"

namespace Praaline {
namespace Core {

SerialiserMetadata::SerialiserMetadata()
{
}

SerialiserMetadata::~SerialiserMetadata()
{
}

// static
QStringList SerialiserMetadata::getEffectiveAttributeIDs(MetadataStructure *structure,  CorpusObject::Type type, const QStringList &requestedAttributeIDs)
{
    QStringList effectiveAttributeIDs;
    if (!structure) return effectiveAttributeIDs;
    // Basic attributes, based on corpus object type
    effectiveAttributeIDs << MetadataStructure::basicAttributeIDs(type);
    // Extra attributes
    if (requestedAttributeIDs.isEmpty())
        effectiveAttributeIDs << structure->attributeIDs(type);
    else {
        QStringList structureAttributeIDs = structure->attributeIDs(type);
        foreach (QString attributeID, requestedAttributeIDs) {
            if (structureAttributeIDs.contains(attributeID))
                effectiveAttributeIDs << attributeID;
        }
    }
    return effectiveAttributeIDs;
}

} // namespace Core
} // namespace Praaline
