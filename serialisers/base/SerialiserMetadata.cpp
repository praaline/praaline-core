#include "SerialiserMetadata.h"
#include "structure/MetadataStructure.h"

PRAALINE_CORE_BEGIN_NAMESPACE

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

PRAALINE_CORE_END_NAMESPACE
