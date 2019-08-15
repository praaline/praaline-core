#include "QueryFilterGroup.h"

PRAALINE_CORE_BEGIN_NAMESPACE

QueryFilterGroup::QueryFilterGroup()
{
}

QueryFilterGroup::~QueryFilterGroup()
{

}

int QueryFilterGroup::longestSequenceLength() const
{
    int length = 0;
    foreach (QueryFilterSequence filterSequence, filterSequences) {
        if (length < filterSequence.sequenceLength())
            length = filterSequence.sequenceLength();
    }
    return length;
}

PRAALINE_CORE_END_NAMESPACE
