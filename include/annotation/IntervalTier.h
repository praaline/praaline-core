#ifndef INTERVALTIER_H
#define INTERVALTIER_H

/*
    Praaline - Core module - Annotation
    Copyright (c) 2011-2019 George Christodoulides

    This program or module is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version. It is provided
    for educational purposes and is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
    the GNU General Public License for more details.
*/

#include "pncore_global.h"
#include <QObject>
#include <QString>
#include <QList>
#include <QHash>
#include <QVariant>
#include "base/RealTime.h"
#include "annotation/AnnotationTier.h"
#include "annotation/Interval.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class Point;
class PointTier;

class PRAALINE_CORE_SHARED_EXPORT IntervalTier : public AnnotationTier
{
    Q_OBJECT

public:
    // Constructors, destructor
    IntervalTier(const QString &name = QString(),
                 const RealTime tMin = RealTime(0, 0), const RealTime tMax = RealTime(0, 0), QObject *parent = nullptr);
    IntervalTier(const QString &name, const QList<Interval *> &intervals,
                 const RealTime tMin = RealTime(0, 0), const RealTime tMax = RealTime(0, 0), QObject *parent = nullptr);
    virtual ~IntervalTier() override;

    // Implementation of AnnotationTier
    AnnotationTier::TierType tierType() const override
        { return AnnotationTier::TierType_Intervals; }
    int count() const override
        { return m_intervals.count(); }
    bool isEmpty() const override;
    void clear() override;
    Interval *at(int index) const override;
    Interval *first() const override;
    Interval *last() const override;
    QStringList getDistinctLabels() const override;
    QList<QVariant> getDistinctValues(const QString &attributeID) const override;
    void replace(const QString &attributeID, const QString &before, const QString &after, Qt::CaseSensitivity cs = Qt::CaseSensitive) override;
    void fillEmptyWith(const QString &attributeID,const QString &filler) override;

    // Accessors for Intervals
    Interval *interval(int index) const;
    QList<Interval *> intervals() const;

    Interval *intervalAtTime(RealTime t, bool preferIntervalToTheLeftOfBoundary = false);
    int intervalIndexAtTime(RealTime t, bool preferIntervalToTheLeftOfBoundary = false) const;

    // Mutators for Intervals
    Interval *addToEnd(RealTime tMax, const QString &text);
    Interval *split(RealTime at);
    Interval *split(int index, RealTime at, bool moveOriginalDataToSecondInterval = false);
    QList<Interval *> splitToEqual(int index, int numberOfIntervals);
    QList<Interval *> splitToProportions(int index, const QList<int> &proportions);
    Interval *merge(int indexFrom, int indexTo, const QString &separator = QString());
    void copyIntervalsFrom(const IntervalTier *copy, bool copyData = true);
    void replaceAllIntervals(QList<Interval *> &newIntervals);
    bool patchIntervals(QList<Interval *> &newIntervals, RealTime from, RealTime to);
    QList<Interval *> patchTextToIntervalsEqual(const QStringList &newIntervalsText, RealTime from, RealTime to);
    QList<Interval *> patchTextToIntervalsProportional(const QStringList &newIntervalsText, RealTime from, RealTime to);
    bool moveBoundary(int index, RealTime time);
    bool realignIntervals(int indexFrom, QList<RealTime> &newBoundaries);
    // Mutators that affect the total length of the tier
    bool modifyIntervalDuration(int index, RealTime delta);
    bool insertInterval(int index, Interval *interval);
    bool removeInterval(int index);

    // Methods
    QList<RealTime> times() const;
    QList<RealTime> timesMin() const;
    QList<RealTime> timesCenter() const;
    QList<RealTime> timesMax() const;
    void timeShift(const RealTime delta);
    bool moveTierEnd(const RealTime time);

    RealTime getBoundaryClosestTo(const RealTime timePoint) const;
    void fixBoundariesBasedOnTier(const IntervalTier *correctBoundariesTier,
                                  RealTime threshold = RealTime(0, 100000000));
    void mergeIdenticalAnnotations(const QString &text = QString(), const QStringList &ignoreIntervening = QStringList());
    void mergeContiguousAnnotations(const QStringList &separatorsOfIntervals, const QString &separatorWhenMerging);

    QPair<int, int> getIntervalIndexesContainedIn(const RealTime &timeStart, const RealTime &timeEnd) const;
    QPair<int, int> getIntervalIndexesContainedIn(const Interval *container) const;
    QList<Interval *> getIntervalsContainedIn(const RealTime &timeStart, const RealTime &timeEnd) const;
    QList<Interval *> getIntervalsContainedIn(const Interval *container) const;
    QString getIntervalsTextContainedIn(const RealTime &timeStart, const RealTime &timeEnd, const QString &separator = " ") const;
    QString getIntervalsTextContainedIn(const Interval *container, const QString &separator = " ") const;

    QPair<int, int> getIntervalIndexesOverlappingWith(const RealTime &timeStart, const RealTime &timeEnd, const RealTime &threshold = RealTime()) const;
    QPair<int, int> getIntervalIndexesOverlappingWith(const Interval *contained, const RealTime &threshold = RealTime()) const;
    QList<Interval *> getIntervalsOverlappingWith(const RealTime &timeStart, const RealTime &timeEnd, const RealTime &threshold = RealTime()) const;
    QList<Interval *> getIntervalsOverlappingWith(const Interval *contained, const RealTime &threshold = RealTime()) const;
    QString getIntervalsTextOverlappingWith(const RealTime &timeStart, const RealTime &timeEnd, const RealTime &threshold = RealTime(),
                                            const QString &separator = " ") const;
    QString getIntervalsTextOverlappingWith(const Interval *contained, const RealTime &threshold = RealTime(),
                                            const QString &separator = " ") const;

    IntervalTier *getIntervalTierWithAttributeAsText(const QString &attributeID) const;
    IntervalTier *getIntervalTierSubset(const RealTime &timeStart, const RealTime &timeEnd) const;

    PointTier *getPointsMin(const QString &name, QObject *parent = nullptr);
    PointTier *getPointsMax(const QString &name, QObject *parent = nullptr);

    void setIOBAnnotationAttribute(const QString &attribute, const IntervalTier *tierAnnotation);
    QString getIntervalsText(int indexStart, int indexEnd, const QString &separator = " ") const;
    QString getIntervalsText(RealTime timeStart, RealTime timeEnd, const QString &separator = " ") const;
    QList<Interval *> getContext(int index, int delta) const;
    QList<Interval *> getContext(int index, RealTime delta) const;
    QString getContextSymmetricFormated(int index, int delta, const QString &sep = " ", const QString &left = "<", const QString &right = ">") const;

    // Clone
    IntervalTier *clone(const QString &name = QString(), QObject *parent = nullptr) const;
    IntervalTier *cloneWithoutAttributes(const QString &name = QString(), QObject *parent = nullptr) const;

    // Multiplex
    static IntervalTier *multiplex(const QString &name, const IntervalTier *tierA, const IntervalTier *tierB,
                                   const QString &textA, const QString &textB, const QString &textAB, QObject *parent = nullptr);

protected:
    QList<Interval *> m_intervals;

private:
    void fixEmptyIntervals();
    static bool compareIntervals(Interval *A, Interval *B);
    QList<Interval *> createIntervalsToProportions(RealTime timeStart, RealTime duration, const QList<int> &proportions) const;
};

PRAALINE_CORE_END_NAMESPACE

#endif // INTERVALTIER_H
