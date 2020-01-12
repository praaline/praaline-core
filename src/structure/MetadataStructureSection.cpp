#include <QObject>
#include <QString>
#include <QList>
#include "structure/MetadataStructureAttribute.h"
#include "structure/MetadataStructureSection.h"

PRAALINE_CORE_BEGIN_NAMESPACE

MetadataStructureSection::MetadataStructureSection(QObject *parent) :
    QObject(parent), m_itemOrder(0)
{
}

MetadataStructureSection::MetadataStructureSection(const QString &ID, const QString &name,
                                                   const QString &description, int itemOrder,
                                                   QObject *parent) :
    QObject(parent), m_ID(ID), m_name(name), m_description(description), m_itemOrder(itemOrder)
{
    if (name.isEmpty()) m_name = ID;
}

MetadataStructureSection::~MetadataStructureSection()
{
}

// ==========================================================================================================
// Data
// ==========================================================================================================

QString MetadataStructureSection::ID() const
{
    return m_ID;
}

void MetadataStructureSection::setID(const QString &ID)
{
    m_ID = ID;
}

QString MetadataStructureSection::name() const
{
    return m_name;
}

void MetadataStructureSection::setName(const QString &name)
{
    m_name = name;
}

QString MetadataStructureSection::description() const
{
    return m_description;
}

void MetadataStructureSection::setDescription(const QString &description) {
    m_description = description;
}

int MetadataStructureSection::itemOrder() const
{
    return m_itemOrder;
}

void MetadataStructureSection::setItemOrder(int itemOrder) {
    m_itemOrder = itemOrder;
}

// ==========================================================================================================
// Metadata attributes
// ==========================================================================================================

MetadataStructureAttribute *MetadataStructureSection::attribute(int index) const
{
    return m_attributes.value(index, nullptr);
}

MetadataStructureAttribute *MetadataStructureSection::attribute(const QString &ID) const
{
    foreach (MetadataStructureAttribute *attribute, m_attributes) {
        if ((attribute) && (attribute->ID() == ID))
            return attribute;
    }
    return nullptr;
}

int MetadataStructureSection::attributeIndexByID(const QString &ID) const
{
    for (int i = 0; i < m_attributes.count(); i++ ) {
        if ((m_attributes[i]) && (m_attributes[i]->ID() == ID))
            return i;
    }
    return -1;
}

int MetadataStructureSection::attributesCount() const
{
    return m_attributes.count();
}

bool MetadataStructureSection::hasAttributes() const
{
    return !m_attributes.isEmpty();
}

bool MetadataStructureSection::hasAttribute(const QString &ID) const
{
    return (attributeIndexByID(ID) != -1);
}

QStringList MetadataStructureSection::attributeIDs() const
{
    QStringList ret;
    foreach (MetadataStructureAttribute *attribute, m_attributes)
        if (attribute) ret << attribute->ID();
    return ret;
}

QStringList MetadataStructureSection::attributeNames() const
{
    QStringList ret;
    foreach (MetadataStructureAttribute *attribute, m_attributes)
        if (attribute) ret << attribute->name();
    return ret;
}

QList<MetadataStructureAttribute *> MetadataStructureSection::attributes() const
{
    return m_attributes;
}

bool MetadataStructureSection::insertAttribute(int index, MetadataStructureAttribute *attribute)
{
    if (!attribute) return false;
    if (hasAttribute(attribute->ID())) return false;
    attribute->setParent(this);
    m_attributes.insert(index, attribute);
    emit attributeAdded(this, attribute);
    return true;
}

bool MetadataStructureSection::addAttribute(MetadataStructureAttribute *attribute)
{
    if (!attribute) return false;
    if (hasAttribute(attribute->ID())) return false;
    attribute->setParent(this);
    m_attributes << attribute;
    emit attributeAdded(this, attribute);
    return true;
}

void MetadataStructureSection::swapAttribute(int oldIndex, int newIndex)
{
    m_attributes.swapItemsAt(oldIndex, newIndex);
}

void MetadataStructureSection::removeAttributeAt(int i)
{
    if ((i < 0) || (i >= m_attributes.count())) return;
    MetadataStructureAttribute *attribute = m_attributes.at(i);
    m_attributes.removeAt(i);
    if (attribute) {
        QString attributeID = attribute->ID();
        delete attribute;
        emit attributeDeleted(this, attributeID);
    }
}

void MetadataStructureSection::removeAttributeByID(const QString &ID)
{
    int i = attributeIndexByID(ID);
    if (i != -1) {
        removeAttributeAt(i);
    }
}

void MetadataStructureSection::clear()
{
    for (int i = attributesCount() - 1; i >= 0; i--) {
        removeAttributeAt(attributesCount() - 1);
    }
}

PRAALINE_CORE_END_NAMESPACE
