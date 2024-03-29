#ifndef SEQUENCETIER_H
#define SEQUENCETIER_H

/*
    Praaline - Core module - Annotation
    Copyright (c) 2011-2020 George Christodoulides

    This program or module is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version. It is provided
    for educational purposes and is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
    the GNU General Public License for more details.
*/

#include <QObject>
#include <QString>
#include <QList>
#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Annotation/AnnotationTier.h"
#include "PraalineCore/Annotation/Sequence.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT SequenceTier : public AnnotationTier
{
    Q_OBJECT
public:
    // Constructors, destructor
    SequenceTier(const QString &name = QString(), AnnotationTier *baseTier = nullptr, QObject *parent = nullptr);
    SequenceTier(const QString &name, const QList<Sequence *> &sequences, AnnotationTier *baseTier = nullptr, QObject *parent = nullptr);
    virtual ~SequenceTier() override;

    // Implementation of AnnotationTier
    AnnotationTier::TierType tierType() const override
        { return AnnotationTier::TierType_Sequences; }
    int count() const override
        { return m_sequences.count(); }
    RealTime tMin() const override;
    RealTime tMax() const override;
    bool isEmpty() const override;
    void clear() override;
    Sequence *at(int index) const override;
    Sequence *first() const override;
    Sequence *last() const override;
    QStringList getDistinctLabels() const override;
    QList<QVariant> getDistinctValues(const QString &attributeID) const override;
    void replace(const QString &attributeID, const QString &before, const QString &after, Qt::CaseSensitivity cs = Qt::CaseSensitive) override;
    void fillEmptyWith(const QString &attributeID,const QString &filler) override;

    // Base tier
    AnnotationTier *baseTier() const;
    void setBaseTier(AnnotationTier *tier);

    // Accessors for Sequences
    Sequence* sequence(int index) const;
    QList<Sequence *> sequences() const;

    int indexOfSequence(Sequence *sequence) const;

    // Mutators for Sequences
    void addSequence(Sequence *sequence);
    void addSequences(QList<Sequence *> sequences);
    void removeSequenceAt(int i);

    // Access to base annotation elements
    QList<AnnotationElement *> sequenceElements(int sequenceIndex) const;
    QString sequenceBaseTierText(int sequenceIndex, const QString &delimiter = " ") const;
    RealTime sequenceTimeMin(int sequenceIndex) const;
    RealTime sequenceTimeMax(int sequenceIndex) const;
    RealTime sequenceDuration(int sequenceIndex) const;

    // Sequences annotating a given element of the base tier
    QString sequencesTextForBaseElement(int baseElementIndex, const QString &delimiter = " ") const;

    // Clone
    SequenceTier *clone(const QString &name = QString(), QObject *parent = nullptr) const;
    SequenceTier *cloneWithoutAttributes(const QString &name = QString(), QObject *parent = nullptr) const;

protected:
    AnnotationTier *m_baseTier;
    QList<Sequence *> m_sequences;

private:
    static bool compareSequences(Sequence *A, Sequence *B);
};

PRAALINE_CORE_END_NAMESPACE

#endif // SEQUENCETIER_H
