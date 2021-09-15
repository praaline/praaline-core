#include <QObject>
#include <QString>
#include <QList>
#include "PraalineCore/Structure/StructureAttributeBase.h"
#include "PraalineCore/Structure/AnnotationStructureAttribute.h"
#include "PraalineCore/Structure/AnnotationStructureLevel.h"

PRAALINE_CORE_BEGIN_NAMESPACE

AnnotationStructureLevel::AnnotationStructureLevel(QObject *parent) :
    StructureAttributeBase(parent),
    m_levelType(AnnotationStructureLevel::IndependentIntervalsLevel)
{
}

AnnotationStructureLevel::AnnotationStructureLevel(const QString &ID, AnnotationStructureLevel::LevelType levelType,
                                                   const QString &name, const QString &description,
                                                   const QString &parentLevelID,
                                                   const DataType &datatype, int order, bool indexed, const QString &nameValueList,
                                                   QObject *parent) :
    StructureAttributeBase(ID, name, description, datatype, order, indexed, nameValueList, parent),
    m_levelType(levelType), m_parentLevelID(parentLevelID)
{
}

AnnotationStructureLevel::~AnnotationStructureLevel()
{
    // Attributes are QObjects, they are deleted as children of this QObject.
}

// ==========================================================================================================
// Data
// ==========================================================================================================

AnnotationStructureLevel::LevelType AnnotationStructureLevel::levelType() const
{
    return m_levelType;
}

bool AnnotationStructureLevel::isLevelTypePrimary() const
{
    if ((m_levelType == AnnotationStructureLevel::IndependentPointsLevel) ||
        (m_levelType == AnnotationStructureLevel::IndependentIntervalsLevel) ||
        (m_levelType == AnnotationStructureLevel::GroupingLevel)) {
        return true;
    }
    // else
    return false;
}

bool AnnotationStructureLevel::isLevelTypeDerived() const
{
    return !isLevelTypePrimary();
}

void AnnotationStructureLevel::setLevelType(LevelType type)
{
    m_levelType = type;
}

QString AnnotationStructureLevel::parentLevelID() const
{
    return m_parentLevelID;
}

void AnnotationStructureLevel::setParentLevelID(const QString &parentLevelID)
{
    m_parentLevelID = parentLevelID;
}

// ==========================================================================================================
// Annotation Attributes
// ==========================================================================================================

AnnotationStructureAttribute *AnnotationStructureLevel::attribute(int index) const
{
    return m_attributes.value(index, nullptr);
}

AnnotationStructureAttribute *AnnotationStructureLevel::attribute(const QString &ID) const
{
    foreach (AnnotationStructureAttribute *attribute, m_attributes) {
        if ((attribute) && (attribute->ID() == ID))
            return attribute;
    }
    return nullptr;
}

int AnnotationStructureLevel::attributeIndexByID(const QString &ID) const
{
    for (int i = 0; i < m_attributes.count(); i++ ) {
        if ((m_attributes[i]) && (m_attributes[i]->ID() == ID))
            return i;
    }
    return -1;
}

int AnnotationStructureLevel::attributesCount() const
{
    return m_attributes.count();
}

bool AnnotationStructureLevel::hasAttributes() const
{
    return !m_attributes.isEmpty();
}

bool AnnotationStructureLevel::hasAttribute(const QString &ID) const
{
    return (attributeIndexByID(ID) != -1);
}

QStringList AnnotationStructureLevel::attributeIDs() const
{
    QStringList ret;
    foreach (AnnotationStructureAttribute *attribute, m_attributes)
        if (attribute) ret << attribute->ID();
    return ret;
}

QStringList AnnotationStructureLevel::attributeNames() const
{
    QStringList ret;
    foreach (AnnotationStructureAttribute *attribute, m_attributes)
        if (attribute) ret << attribute->name();
    return ret;
}

QList<AnnotationStructureAttribute *> AnnotationStructureLevel::attributes() const
{
    return m_attributes;
}

bool AnnotationStructureLevel::insertAttribute(int index, AnnotationStructureAttribute *attribute)
{
    if (!attribute) return false;
    if (hasAttribute(attribute->ID())) return false;
    attribute->setParent(this);
    m_attributes.insert(index, attribute);
    emit attributeAdded(this, attribute);
    return true;
}

bool AnnotationStructureLevel::addAttribute(AnnotationStructureAttribute *attribute)
{
    if (!attribute) return false;
    if (hasAttribute(attribute->ID())) return false;
    attribute->setParent(this);
    m_attributes << attribute;
    emit attributeAdded(this, attribute);
    return true;
}

void AnnotationStructureLevel::swapAttribute(int oldIndex, int newIndex)
{
    m_attributes.swapItemsAt(oldIndex, newIndex);
}

void AnnotationStructureLevel::removeAttributeAt(int i)
{
    if ((i < 0) || (i >= m_attributes.count())) return;
    AnnotationStructureAttribute *attribute = m_attributes.at(i);
    m_attributes.removeAt(i);
    if (attribute) {
        QString attributeID = attribute->ID();
        delete attribute;
        emit attributeDeleted(this, attributeID);
    }
}

void AnnotationStructureLevel::removeAttributeByID(const QString &ID)
{
    int i = attributeIndexByID(ID);
    if (i != -1)
        removeAttributeAt(i);
}

void AnnotationStructureLevel::clear()
{
    for (int i = attributesCount() - 1; i >= 0; i--) {
        removeAttributeAt(attributesCount() - 1);
    }
}

PRAALINE_CORE_END_NAMESPACE
