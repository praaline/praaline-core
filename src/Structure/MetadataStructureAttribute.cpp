#include <QObject>
#include "PraalineCore/Structure/StructureAttributeBase.h"
#include "PraalineCore/Structure/MetadataStructureSection.h"
#include "PraalineCore/Structure/MetadataStructureAttribute.h"

PRAALINE_CORE_BEGIN_NAMESPACE

MetadataStructureAttribute::MetadataStructureAttribute(QObject *parent) :
    StructureAttributeBase(parent)
{
}

MetadataStructureAttribute::MetadataStructureAttribute(const QString &ID, const QString &name, const QString &description,
                                                       const DataType &datatype, int order, bool indexed, const QString &nameValueList,
                                                       bool mandatory, QVariant defaultValue, QObject *parent) :
    StructureAttributeBase(ID, name, description, datatype, order, indexed, nameValueList, parent),
    m_mandatory(mandatory), m_defaultValue(defaultValue)
{
}

MetadataStructureAttribute::~MetadataStructureAttribute()
{
}

MetadataStructureAttribute *MetadataStructureAttribute::clone(QObject *parent) const
{
    return new MetadataStructureAttribute(m_ID, m_name, m_description, m_datatype, m_itemOrder, m_indexed, m_nameValueList,
                                          m_mandatory, m_defaultValue, parent);
}

bool MetadataStructureAttribute::mandatory() const
{
    return m_mandatory;
}

void MetadataStructureAttribute::setMandatory(bool mandatory)
{
    m_mandatory = mandatory;
}

QVariant MetadataStructureAttribute::defaultValue() const
{
    return m_defaultValue;
}

void MetadataStructureAttribute::setDefaultValue(const QVariant &defaultValue)
{
    m_defaultValue = defaultValue;
}

QString MetadataStructureAttribute::sectionID() const
{
    MetadataStructureSection *section = qobject_cast<MetadataStructureSection *>(this->parent());
    if (section) return section->ID();
    return QString();
}

PRAALINE_CORE_END_NAMESPACE
