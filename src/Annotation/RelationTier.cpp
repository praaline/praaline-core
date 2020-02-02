#include <QString>

#include "PraalineCore/Annotation/Relation.h"
#include "PraalineCore/Annotation/RelationTier.h"
#include "PraalineCore/Annotation/IntervalTier.h"
#include "PraalineCore/Annotation/AnnotationTier.h"

PRAALINE_CORE_BEGIN_NAMESPACE

// ==========================================================================================================
// Constructors - destructor
// ==========================================================================================================
RelationTier::RelationTier(const QString &name, AnnotationTier *baseTier, QObject *parent) :
    AnnotationTier(name, parent), m_baseTier(baseTier)
{
}

RelationTier::RelationTier(const QString &name, const QList<Relation *> &relations, AnnotationTier *baseTier, QObject *parent) :
    AnnotationTier(name, parent), m_baseTier(baseTier)
{
    m_relations = relations;
    if (m_relations.count() == 0) return;
    std::sort(m_relations.begin(), m_relations.end(), RelationTier::compareRelations);
}

RelationTier::~RelationTier()
{
    qDeleteAll(m_relations);
}

// ==============================================================================================================================
// Implementation of AnnotationTier
// ==============================================================================================================================

RealTime RelationTier::tMin() const
{
    if (m_baseTier) return m_baseTier->tMin();
    return m_tMin;
}

RealTime RelationTier::tMax() const
{
    if (m_baseTier) return m_baseTier->tMax();
    return m_tMax;
}

bool RelationTier::isEmpty() const
{
    return m_relations.isEmpty();
}

void RelationTier::clear()
{
    qDeleteAll(m_relations);
    m_relations.clear();
}

Relation *RelationTier::at(int index) const
{
    return m_relations.at(index);
}

Relation *RelationTier::first() const
{
    if (isEmpty()) return nullptr;
    return m_relations.first();
}

Relation *RelationTier::last() const
{
    if (isEmpty()) return nullptr;
    return m_relations.last();
}

QStringList RelationTier::getDistinctLabels() const
{
    QStringList ret;
    foreach (Relation *relation, m_relations) {
        if (!ret.contains(relation->text())) ret << relation->text();
    }
    return ret;
}

QList<QVariant> RelationTier::getDistinctValues(const QString &attributeID) const
{
    QList<QVariant> ret;
    foreach (Relation *relation, m_relations) {
        QVariant value = (attributeID.isEmpty()) ? relation->text() : relation->attribute(attributeID);
        if (!ret.contains(value)) ret << value;
    }
    return ret;
}

void RelationTier::replace(const QString &attributeID, const QString &before, const QString &after, Qt::CaseSensitivity cs)
{
    foreach (Relation *relation, m_relations) {
        if (attributeID.isEmpty())
            relation->replaceText(before, after, cs);
        else
            relation->replaceAttributeText(attributeID, before, after, cs);
    }
}

void RelationTier::fillEmptyWith(const QString &attributeID, const QString &filler)
{
    foreach (Relation *relation, m_relations) {
        if (attributeID.isEmpty()) {
            if (relation->text().isEmpty())
                relation->setText(filler);
        } else {
            if (relation->attribute(attributeID).toString().isEmpty())
                relation->setAttribute(attributeID, filler);
        }
    }
}

// ==============================================================================================================================
// Base tier
// ==============================================================================================================================

AnnotationTier *RelationTier::baseTier() const
{
    return m_baseTier;
}

void RelationTier::setBaseTier(AnnotationTier *tier)
{
    m_baseTier = tier;
}

// ==============================================================================================================================
// Accessors and mutators for Relations
// ==============================================================================================================================

Relation *RelationTier::relation(int index) const
{
    return m_relations.value(index);
}

QList<Relation *> RelationTier::relations() const
{
    return m_relations;
}

bool RelationTier::compareRelations(Relation *A, Relation *B) {
    if (A->indexFrom() == B->indexFrom())
        return (A->indexTo() < B->indexTo());
    // else
    return (A->indexFrom() < B->indexFrom());
}

void RelationTier::addRelation(Relation *relation)
{
    m_relations << relation;
    std::sort(m_relations.begin(), m_relations.end(), RelationTier::compareRelations);
}

void RelationTier::addRelations(QList<Relation *> relations)
{
    m_relations << relations;
    std::sort(m_relations.begin(), m_relations.end(), RelationTier::compareRelations);
}

void RelationTier::removeRelationAt(int i)
{
    m_relations.removeAt(i);
}

QPair<AnnotationElement *, AnnotationElement *> RelationTier::relationElements(int relationIndex) const
{
    QPair<AnnotationElement *, AnnotationElement *> pair = QPair<AnnotationElement *, AnnotationElement *>(nullptr, nullptr);
    if (!m_baseTier) return pair;
    if ((relationIndex < 0) || (relationIndex >= m_relations.count())) return pair;
    int from = m_relations.at(relationIndex)->indexFrom();
    int to = m_relations.at(relationIndex)->indexTo();
    pair.first = m_baseTier->at(from);
    pair.second = m_baseTier->at(to);
    return pair;
}

// ==============================================================================================================================
// Clone
// ==============================================================================================================================
RelationTier *RelationTier::clone(const QString &name, QObject *parent) const
{
    QString cloneName = (name.isEmpty()) ? m_name : name;
    QList<Relation *> cloneRelations;
    foreach (Relation *rel, m_relations)
        cloneRelations << rel->clone();
    return new RelationTier(cloneName, cloneRelations, m_baseTier, parent);
}

RelationTier *RelationTier::cloneWithoutAttributes(const QString &name, QObject *parent) const
{
    QString cloneName = (name.isEmpty()) ? m_name : name;
    QList<Relation *> cloneRelations;
    foreach (Relation *rel, m_relations)
        cloneRelations << rel->cloneWithoutAttributes();
    return new RelationTier(cloneName, cloneRelations, m_baseTier, parent);
}


PRAALINE_CORE_END_NAMESPACE
