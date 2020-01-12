#include "base/ISaveable.h"

PRAALINE_CORE_BEGIN_NAMESPACE

ISaveable::ISaveable() :
    m_isNew(true), m_isDirty(true)
{
}

ISaveable::~ISaveable()
{
}

PRAALINE_CORE_END_NAMESPACE
