#include "structure/StructureAttributeBase.h"

PRAALINE_CORE_BEGIN_NAMESPACE

StructureAttributeBase::StructureAttributeBase(QObject *parent) :
    QObject(parent), m_datatype(DataType::Invalid), m_itemOrder(0), m_indexed(false)
{
}

StructureAttributeBase::StructureAttributeBase(const QString &ID, const QString &name, const QString &description,
                                               const DataType &datatype, int itemOrder, bool indexed, const QString &nameValueList,
                                               QObject *parent) :
    QObject(parent), m_ID(ID), m_name(name), m_description(description), m_datatype(datatype),
    m_itemOrder(itemOrder), m_indexed(indexed), m_nameValueList(nameValueList)
{
    if (name.isEmpty()) m_name = ID;
}

StructureAttributeBase::~StructureAttributeBase()
{
}

StructureAttributeBase *StructureAttributeBase::clone(QObject *parent) const
{
    return new StructureAttributeBase(m_ID, m_name, m_description,
                                      m_datatype, m_itemOrder, m_indexed, m_nameValueList, parent);
}

PRAALINE_CORE_END_NAMESPACE
