#include "corpus/CorpusObjectInfo.h"

PRAALINE_CORE_BEGIN_NAMESPACE

CorpusObjectInfo::CorpusObjectInfo() :
    m_type(CorpusObject::Type_Undefined)
{
    m_isNew = true;
    m_isDirty = true;
}

CorpusObjectInfo::CorpusObjectInfo(CorpusObject::Type type) :
    m_type(type)
{
    m_isNew = true;
    m_isDirty = true;
}

CorpusObjectInfo::CorpusObjectInfo(const CorpusObjectInfo &other) :
    m_type(other.m_type), m_attributes(other.m_attributes)
{
    m_isNew = true;
    m_isDirty = true;
}

CorpusObjectInfo::~CorpusObjectInfo()
{
}

PRAALINE_CORE_END_NAMESPACE


