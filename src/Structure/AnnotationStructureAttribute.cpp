#include <QObject>
#include "PraalineCore/Structure/StructureAttributeBase.h"
#include "PraalineCore/Structure/AnnotationStructureAttribute.h"

PRAALINE_CORE_BEGIN_NAMESPACE

AnnotationStructureAttribute::AnnotationStructureAttribute(QObject *parent) :
    StructureAttributeBase(parent)
{
}

AnnotationStructureAttribute::AnnotationStructureAttribute(const QString &ID, const QString &name, const QString &description,
                                                           const DataType &datatype, int order, bool indexed, const QString &nameValueList,
                                                           const QString &statLevelOfMeasurement, QObject *parent) :
    StructureAttributeBase(ID, name, description, datatype, order, indexed, nameValueList, parent),
    m_statLevelOfMeasurement(statLevelOfMeasurement)
{
}

AnnotationStructureAttribute::~AnnotationStructureAttribute()
{
}

AnnotationStructureAttribute *AnnotationStructureAttribute::clone(QObject *parent) const
{
    return new AnnotationStructureAttribute(m_ID, m_name, m_description, m_datatype, m_itemOrder,
                                            m_indexed, m_nameValueList, m_statLevelOfMeasurement, parent);
}

QString AnnotationStructureAttribute::statLevelOfMeasurement() const
{
    return m_statLevelOfMeasurement;
}

void AnnotationStructureAttribute::setStatLevelOfMeasurement(const QString &statLevelOfMeasurement)
{
    m_statLevelOfMeasurement = statLevelOfMeasurement;
}

PRAALINE_CORE_END_NAMESPACE
