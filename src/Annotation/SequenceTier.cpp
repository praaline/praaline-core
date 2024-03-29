#include <QString>

#include "PraalineCore/Annotation/Sequence.h"
#include "PraalineCore/Annotation/SequenceTier.h"
#include "PraalineCore/Annotation/PointTier.h"
#include "PraalineCore/Annotation/IntervalTier.h"
#include "PraalineCore/Annotation/AnnotationTier.h"

PRAALINE_CORE_BEGIN_NAMESPACE

// ==========================================================================================================
// Constructors - destructor
// ==========================================================================================================
SequenceTier::SequenceTier(const QString &name, AnnotationTier *baseTier, QObject *parent) :
    AnnotationTier(name, parent), m_baseTier(baseTier)
{
}

SequenceTier::SequenceTier(const QString &name, const QList<Sequence *> &sequences, AnnotationTier *baseTier, QObject *parent) :
    AnnotationTier(name, parent), m_baseTier(baseTier)
{
    m_sequences = sequences;
    if (m_sequences.count() == 0) return;
    std::sort(m_sequences.begin(), m_sequences.end(), SequenceTier::compareSequences);
}

SequenceTier::~SequenceTier()
{
    qDeleteAll(m_sequences);
}

// ==============================================================================================================================
// Implementation of AnnotationTier
// ==============================================================================================================================

RealTime SequenceTier::tMin() const
{
    if (m_baseTier) return m_baseTier->tMin();
    return m_tMin;
}

RealTime SequenceTier::tMax() const
{
    if (m_baseTier) return m_baseTier->tMax();
    return m_tMax;
}

bool SequenceTier::isEmpty() const
{
    return m_sequences.isEmpty();
}

void SequenceTier::clear()
{
    qDeleteAll(m_sequences);
    m_sequences.clear();
}

Sequence *SequenceTier::at(int index) const
{
    return m_sequences.at(index);
}

Sequence *SequenceTier::first() const
{
    if (isEmpty()) return nullptr;
    return m_sequences.first();
}

Sequence *SequenceTier::last() const
{
    if (isEmpty()) return nullptr;
    return m_sequences.last();
}

QStringList SequenceTier::getDistinctLabels() const
{
    QStringList ret;
    foreach (Sequence *sequence, m_sequences) {
        if (!ret.contains(sequence->text())) ret << sequence->text();
    }
    return ret;
}

QList<QVariant> SequenceTier::getDistinctValues(const QString &attributeID) const
{
    QList<QVariant> ret;
    foreach (Sequence *sequence, m_sequences) {
        QVariant value = (attributeID.isEmpty()) ? sequence->text() : sequence->attribute(attributeID);
        if (!ret.contains(value)) ret << value;
    }
    return ret;
}

void SequenceTier::replace(const QString &attributeID, const QString &before, const QString &after, Qt::CaseSensitivity cs)
{
    foreach (Sequence *sequence, m_sequences) {
        if (attributeID.isEmpty())
            sequence->replaceText(before, after, cs);
        else
            sequence->replaceAttributeText(attributeID, before, after, cs);
    }
}

void SequenceTier::fillEmptyWith(const QString &attributeID, const QString &filler)
{
    foreach (Sequence *sequence, m_sequences) {
        if (attributeID.isEmpty()) {
            if (sequence->text().isEmpty())
                sequence->setText(filler);
        } else {
            if (sequence->attribute(attributeID).toString().isEmpty())
                sequence->setAttribute(attributeID, filler);
        }
    }
}

// ==============================================================================================================================
// Base tier
// ==============================================================================================================================

AnnotationTier *SequenceTier::baseTier() const
{
    return m_baseTier;
}

void SequenceTier::setBaseTier(AnnotationTier *tier)
{
    m_baseTier = tier;
}

// ==============================================================================================================================
// Accessors and mutators for Sequences
// ==============================================================================================================================

Sequence *SequenceTier::sequence(int index) const
{
    return m_sequences.value(index);
}

QList<Sequence *> SequenceTier::sequences() const
{
    return m_sequences;
}

bool SequenceTier::compareSequences(Sequence *A, Sequence *B) {
    if (A->indexFrom() == B->indexFrom()) {
        if (A->indexTo() == B->indexTo()) {
            return (A->text() < B->text());
        } else {
            return (A->indexTo() < B->indexTo());
        }
    }
    // else
    return (A->indexFrom() < B->indexFrom());
}

int SequenceTier::indexOfSequence(Sequence *sequence) const
{
    return m_sequences.indexOf(sequence);
}

void SequenceTier::addSequence(Sequence *sequence)
{
    m_sequences << sequence;
    std::sort(m_sequences.begin(), m_sequences.end(), SequenceTier::compareSequences);
}

void SequenceTier::addSequences(QList<Sequence *> sequences)
{
    m_sequences << sequences;
    std::sort(m_sequences.begin(), m_sequences.end(), SequenceTier::compareSequences);
}

void SequenceTier::removeSequenceAt(int i)
{
    m_sequences.removeAt(i);
}

// Access to base annotation elements

QList<AnnotationElement *> SequenceTier::sequenceElements(int sequenceIndex) const
{
    QList<AnnotationElement *> elements;
    if (!m_baseTier) return elements;
    if ((sequenceIndex < 0) || (sequenceIndex >= m_sequences.count())) return elements;
    int from = m_sequences.at(sequenceIndex)->indexFrom();
    int to = m_sequences.at(sequenceIndex)->indexTo();
    for (int i = from; i <= to; ++i) {
        if (i > 0 && i < m_baseTier->count()) elements << m_baseTier->at(i);
    }
    return elements;
}

QString SequenceTier::sequenceBaseTierText(int sequenceIndex, const QString &delimiter) const
{
    QList<AnnotationElement *> elements = sequenceElements(sequenceIndex);
    QString ret;
    foreach (AnnotationElement *element, elements) {
        ret.append(element->text()).append(delimiter);
    }
    if (ret.length() >= delimiter.length()) ret.chop(delimiter.length());
    return ret;
}

RealTime SequenceTier::sequenceTimeMin(int sequenceIndex) const
{
    if (!m_baseTier) return RealTime();
    if ((sequenceIndex < 0) || (sequenceIndex >= m_sequences.count())) return RealTime();
    int from = m_sequences.at(sequenceIndex)->indexFrom();
    if (m_baseTier->tierType() == AnnotationTier::TierType_Points)
        return static_cast<PointTier *>(m_baseTier)->point(from)->time();
    else if (m_baseTier->tierType() == AnnotationTier::TierType_Intervals)
        return static_cast<IntervalTier *>(m_baseTier)->interval(from)->tMin();
    return RealTime();
}

RealTime SequenceTier::sequenceTimeMax(int sequenceIndex) const
{
    if (!m_baseTier) return RealTime();
    if ((sequenceIndex < 0) || (sequenceIndex >= m_sequences.count())) return RealTime();
    int to = m_sequences.at(sequenceIndex)->indexTo();
    if (m_baseTier->tierType() == AnnotationTier::TierType_Points)
        return static_cast<PointTier *>(m_baseTier)->point(to)->time();
    else if (m_baseTier->tierType() == AnnotationTier::TierType_Intervals)
        return static_cast<IntervalTier *>(m_baseTier)->interval(to)->tMax();
    return RealTime();
}

RealTime SequenceTier::sequenceDuration(int sequenceIndex) const
{
    return sequenceTimeMax(sequenceIndex) - sequenceTimeMin(sequenceIndex);
}

// Sequences annotating a given element of the base tier

QString SequenceTier::sequencesTextForBaseElement(int baseElementIndex, const QString &delimiter) const
{
    QString ret;
    for (int sequenceIndex = 0; sequenceIndex < m_sequences.count(); ++sequenceIndex) {
        if ((m_sequences.at(sequenceIndex)->indexFrom() <= baseElementIndex) &&
            (m_sequences.at(sequenceIndex)->indexTo()   >= baseElementIndex)) {
            ret.append(m_sequences.at(sequenceIndex)->text()).append(delimiter);
        }
    }
    if (ret.length() >= delimiter.length()) ret.chop(delimiter.length());
    return ret;
}

// ==============================================================================================================================
// Clone
// ==============================================================================================================================

SequenceTier *SequenceTier::clone(const QString &name, QObject *parent) const
{
    QString cloneName = (name.isEmpty()) ? m_name : name;
    QList<Sequence *> cloneSequences;
    foreach (Sequence *seq, m_sequences)
        cloneSequences << seq->clone();
    return new SequenceTier(cloneName, cloneSequences, m_baseTier, parent);
}

SequenceTier *SequenceTier::cloneWithoutAttributes(const QString &name, QObject *parent) const
{
    QString cloneName = (name.isEmpty()) ? m_name : name;
    QList<Sequence *> cloneSequences;
    foreach (Sequence *seq, m_sequences)
        cloneSequences << seq->cloneWithoutAttributes();
    return new SequenceTier(cloneName, cloneSequences, m_baseTier, parent);
}

PRAALINE_CORE_END_NAMESPACE
