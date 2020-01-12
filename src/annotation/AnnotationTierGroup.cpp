#include <QObject>
#include <QString>
#include <QList>
#include <QPair>
#include <QStringList>

#include "base/RealTime.h"
#include "annotation/AnnotationTier.h"
#include "annotation/PointTier.h"
#include "annotation/IntervalTier.h"
#include "annotation/SequenceTier.h"
#include "annotation/TreeTier.h"
#include "annotation/RelationTier.h"
#include "annotation/AnnotationTierGroup.h"

PRAALINE_CORE_BEGIN_NAMESPACE

// ==========================================================================================================
// Constructors - destructors
// ==========================================================================================================
AnnotationTierGroup::AnnotationTierGroup(QObject *parent) :
    QObject(parent)
{
    m_ID = QString();
}

AnnotationTierGroup::~AnnotationTierGroup()
{
   // All tiers should be deleted as QObjects having this as their parent.
}

// ==========================================================================================================
// Global tMin and tMax: find it by checking all tiers in this annotation group
// ==========================================================================================================
RealTime AnnotationTierGroup::tMin() const
{
    RealTime tMin = RealTime(0, 0);
    foreach (AnnotationTier *tier, m_tiers) {
        if (tier->tMin() < tMin)
            tMin = tier->tMin();
    }
    return tMin;
}
RealTime AnnotationTierGroup::tMax() const
{
    RealTime tMax = RealTime(0, 0);
    foreach (AnnotationTier *tier, m_tiers) {
        if (tier->tMax() > tMax)
            tMax = tier->tMax();
    }
    return tMax;
}

// ==========================================================================================================
// Tier accessors and modifiers
// ==========================================================================================================
AnnotationTier *AnnotationTierGroup::tier(int index) const
{
    return m_tiers.value(index);
}

AnnotationTier *AnnotationTierGroup::tier(const QString &name) const
{
    foreach (AnnotationTier *tier, m_tiers) {
        if (tier->name() == name) return tier;
    }
    return nullptr;
}

int AnnotationTierGroup::tiersCount() const
{
    return m_tiers.count();
}

bool AnnotationTierGroup::hasTiers() const
{
    return !m_tiers.isEmpty();
}

QList<AnnotationTier *> AnnotationTierGroup::tiers() const
{
    return m_tiers;
}

void AnnotationTierGroup::insertTier(int index, AnnotationTier *tier)
{
    if (!tier) return;
    tier->setParent(this);
    m_tiers.insert(index, tier);
    emit tierInserted(tier);
}

void AnnotationTierGroup::insertTierReplacing(int index, AnnotationTier *tier)
{
    if (!tier) return;
    // if a tier with the same name already exists, it will be replaced
    this->removeTierByName(tier->name());
    tier->setParent(this);
    m_tiers.insert(index, tier);
    emit tierInserted(tier);
}

void AnnotationTierGroup::addTier(AnnotationTier *tier)
{
    if (!tier) return;
    tier->setParent(this);
    m_tiers << tier;
    emit tierInserted(tier);
}

void AnnotationTierGroup::addTierReplacing(AnnotationTier *tier)
{
    if (!tier) return;
    // if a tier with the same name already exists, it will be replaced
    this->removeTierByName(tier->name());
    tier->setParent(this);
    m_tiers << tier;
    emit tierInserted(tier);
}

void AnnotationTierGroup::swapTiers(int oldIndex, int newIndex)
{
    m_tiers.swapItemsAt(oldIndex, newIndex);
}

void AnnotationTierGroup::removeTierAt(int i)
{
    AnnotationTier *tier = m_tiers.at(i);
    if (!tier) return;
    QString name = tier->name();
    m_tiers.removeAt(i);
    delete tier;
    emit tierDeleted(name);
}

void AnnotationTierGroup::removeTierByName(const QString &name)
{
    int i = getTierIndexByName(name);
    if (i < 0) return;
    AnnotationTier *tier = m_tiers.at(i);
    m_tiers.removeAt(i);
    delete tier;
    emit tierDeleted(name);
}

int AnnotationTierGroup::getTierIndexByName(const QString &name) const
{
    for (int i = 0; i < m_tiers.count(); i++ ) {
        if (m_tiers[i]->name() == name)
            return i;
    }
    return -1;
}

IntervalTier *AnnotationTierGroup::getIntervalTierByName(const QString &name) const
{
    foreach (AnnotationTier *tier, m_tiers) {
        if (tier->name() == name && ((tier->tierType() == AnnotationTier::TierType_Intervals) ||
                                     (tier->tierType() == AnnotationTier::TierType_Grouping)))
            return static_cast<IntervalTier *>(tier);
    }
    return nullptr;
}

IntervalTier *AnnotationTierGroup::getIntervalTierByIndex(int index) const
{
    if (index < 0 || index >= m_tiers.count())
        return nullptr;
    AnnotationTier *tier = m_tiers.at(index);
    if ((tier->tierType() == AnnotationTier::TierType_Intervals) || (tier->tierType() == AnnotationTier::TierType_Grouping))
        return static_cast<IntervalTier *>(tier);
    else
        return nullptr;
}

PointTier *AnnotationTierGroup::getPointTierByName(const QString &name) const
{
    foreach (AnnotationTier *tier, m_tiers) {
        if (tier->name() == name && tier->tierType() == AnnotationTier::TierType_Points)
            return static_cast<PointTier *>(tier);
    }
    return nullptr;
}

PointTier *AnnotationTierGroup::getPointTierByIndex(int index) const
{
    if (index < 0 || index >= m_tiers.count())
        return nullptr;
    AnnotationTier *tier = m_tiers.at(index);
    if (tier->tierType() == AnnotationTier::TierType_Points)
        return static_cast<PointTier *>(tier);
    else
        return nullptr;
}

SequenceTier *AnnotationTierGroup::getSequenceTierByName(const QString &name) const
{
    foreach (AnnotationTier *tier, m_tiers) {
        if (tier->name() == name && tier->tierType() == AnnotationTier::TierType_Sequences)
            return static_cast<SequenceTier *>(tier);
    }
    return nullptr;
}

SequenceTier *AnnotationTierGroup::getSequenceTierByIndex(int index) const
{
    if (index < 0 || index >= m_tiers.count())
        return nullptr;
    AnnotationTier *tier = m_tiers.at(index);
    if (tier->tierType() == AnnotationTier::TierType_Sequences)
        return static_cast<SequenceTier *>(tier);
    else
        return nullptr;
}

TreeTier *AnnotationTierGroup::getTreeTierByName(const QString &name) const
{
    foreach (AnnotationTier *tier, m_tiers) {
        if (tier->name() == name && tier->tierType() == AnnotationTier::TierType_Tree)
            return static_cast<TreeTier *>(tier);
    }
    return nullptr;
}

TreeTier *AnnotationTierGroup::getTreeTierByIndex(int index) const
{
    if (index < 0 || index >= m_tiers.count())
        return nullptr;
    AnnotationTier *tier = m_tiers.at(index);
    if (tier->tierType() == AnnotationTier::TierType_Tree)
        return static_cast<TreeTier *>(tier);
    else
        return nullptr;
}

RelationTier *AnnotationTierGroup::getRelationTierByName(const QString &name) const
{
    foreach (AnnotationTier *tier, m_tiers) {
        if (tier->name() == name && tier->tierType() == AnnotationTier::TierType_Relations)
            return static_cast<RelationTier *>(tier);
    }
    return nullptr;
}

RelationTier *AnnotationTierGroup::getRelationTierByIndex(int index) const
{
    if (index < 0 || index >= m_tiers.count())
        return nullptr;
    AnnotationTier *tier = m_tiers.at(index);
    if (tier->tierType() == AnnotationTier::TierType_Relations)
        return static_cast<RelationTier *>(tier);
    else
        return nullptr;
}

QStringList AnnotationTierGroup::tierNames() const
{
    QStringList ret;
    for (int i = 0; i < m_tiers.count(); i++ ) {
        if (m_tiers[i])
            ret << m_tiers[i]->name();
    }
    return ret;
}

// Methods
void AnnotationTierGroup::insertTierClone(int index, const AnnotationTier *tier, const QString &newName)
{
    if (!tier) return;
    if ((tier->tierType() == AnnotationTier::TierType_Intervals) || (tier->tierType() == AnnotationTier::TierType_Grouping)) {
        IntervalTier *newTier = static_cast<const IntervalTier *>(tier)->clone(newName, this);
        m_tiers.insert(index, newTier);
        emit tierInserted(newTier);
    }
    else if (tier->tierType() == AnnotationTier::TierType_Points) {
        PointTier *newTier = static_cast<const PointTier *>(tier)->clone(newName, this);
        m_tiers.insert(index, newTier);
        emit tierInserted(newTier);
    }
    else if (tier->tierType() == AnnotationTier::TierType_Sequences) {
        SequenceTier *newTier = static_cast<const SequenceTier *>(tier)->clone(newName, this);
        m_tiers.insert(index, newTier);
        emit tierInserted(newTier);
    }
//    else if (tier->tierType() == AnnotationTier::TierType_Tree) {
//        TreeTier *newTier = new TreeTier((TreeTier *)tier, newName, true, this);
//        newTier->setParent(this);
//        m_tiers.insert(index, newTier);
//        emit tierInserted(newTier);
//    }
    else if (tier->tierType() == AnnotationTier::TierType_Relations) {
        RelationTier *newTier = static_cast<const RelationTier *>(tier)->clone(newName, this);
        m_tiers.insert(index, newTier);
        emit tierInserted(newTier);
    }
}

void AnnotationTierGroup::renameTier(const QString &nameBefore, const QString &nameAfter)
{
    int i = this->getTierIndexByName(nameBefore);
    if (i < 0) return; // not found
    m_tiers[i]->setName(nameAfter);
}

bool AnnotationTierGroup::reorderTiers(QStringList tierNamesInNewOrder) {
    QList<AnnotationTier *> new_tiers;
    foreach (QString tierName, tierNamesInNewOrder) {
        int index = getTierIndexByName(tierName);
        if (index >= 0) {
            new_tiers << m_tiers[index];
        }
    }
    m_tiers = new_tiers;
    return true;
}

void AnnotationTierGroup::mergeSilentPausesOnAllIntervalTiers(const QString &silentPauseText)
{
    foreach (AnnotationTier *annotationTier, m_tiers) {
        IntervalTier *tier = qobject_cast<IntervalTier *>(annotationTier);
        if (!tier) continue;
        tier->fillEmptyWith("", silentPauseText);
        tier->mergeIdenticalAnnotations(silentPauseText);
    }
}

PRAALINE_CORE_END_NAMESPACE
