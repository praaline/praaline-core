#include "PraalineCore/Query/QueryDefinition.h"

PRAALINE_CORE_BEGIN_NAMESPACE

QueryDefinition::QueryDefinition()
{
    lengthContextLeft = 10;
    lengthContextRight = 10;
}

QueryDefinition::~QueryDefinition()
{
}

int QueryDefinition::longestSequenceLength() const
{
    int length = 0;
    foreach (QueryFilterGroup filterGroup, filterGroups) {
        if (length < filterGroup.longestSequenceLength())
            length = filterGroup.longestSequenceLength();
    }
    return length;
}

PRAALINE_CORE_END_NAMESPACE
