#ifndef INTERVAL_H
#define INTERVAL_H

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
#include <QString>
#include <QVariant>
#include "base/RealTime.h"
#include "AnnotationElement.h"

PRAALINE_CORE_BEGIN_NAMESPACE

/**
 * @brief The Interval class represents an annotation element that spans an interval on the timeline, i.e. has a
 * start time and an end time, as well as a label and attributes. An IntervalTier contains Intervals.
 */

class PRAALINE_CORE_SHARED_EXPORT Interval : public AnnotationElement
{
    friend class IntervalTier;

public:
    /**
     * @brief Default constructor.
     */
    Interval();
    /**
     * @brief Constructor.
     * @param tMin The start of the interval (RealTime value).
     * @param tMax The end of the interval (RealTime value). Must be tMax > tMin.
     * @param text The initial label of the interval. Empty by default.
     * @param attributes A QVariantHash of initial values for the interval attributes.
     */
    Interval(const RealTime tMin, const RealTime tMax,
             const QString &text = QString(), const QHash<QString, QVariant> &attributes = QHash<QString, QVariant>());
    /**
     * @brief Copy constructor.
     * @param copy The interval to copy.
     */
    Interval(const Interval &copy);
    /**
     * @brief Destructor (virtual).
     */
    virtual ~Interval() override;

    // Properties
    /**
     * @brief tMin property
     * @return The start of the interval (RealTime value).
     */
    inline RealTime tMin() const
        { return m_tMin; }
    /**
     * @brief tMax property
     * @return The end of the interval (RealTime value).
     */
    inline RealTime tMax() const
        { return m_tMax; }
    /**
     * @brief tCenter property
     * @return The middle (center) point of the interval, i.e. (tMin + Max) / 2 (RealTime value).
     */
    inline RealTime tCenter() const
        { return (m_tMin + m_tMax) / 2.0; }
    /**
     * @brief duration property
     * @return The duration of the interval, i.e. tMax - tMin (RealTime value).
     */
    inline RealTime duration() const
        { return (m_tMax - m_tMin); }

    // Overrides
    virtual QVariant attribute(const QString &name) const override ;
    virtual void setAttribute(const QString &name, QVariant value) override;
    inline virtual ElementType elementType() const override {
        return Type_Interval;
    }

    // Methods for Intervals
    bool overlaps(const Interval &other, const RealTime threshold = RealTime(0, 0)) const;
    bool covers(const Interval &other, const RealTime threshold = RealTime(0, 0)) const;
    bool isCovered(const Interval &other, const RealTime threshold = RealTime(0, 0)) const;
    bool contains(const RealTime timePoint) const;
    bool isPauseSilent() const;
    int compare(const Interval &other) const;

    // Create new interval from existing one(s)
    /**
     * @brief clone
     * @return
     */
    Interval *clone();
    Interval *cloneWithoutAttributes();
    /**
     * @brief cloneReposition test
     * @param tMin test test
     * @param tMax test
     * @return
     */
    Interval *cloneReposition(const RealTime tMin, const RealTime tMax);
    Interval *cloneRepositionWithoutAttributes(const RealTime tMin, const RealTime tMax);


    static Interval *fromList(const QList<Interval *> &intervals, const QString &separator = QString());

protected:
    RealTime m_tMin;
    RealTime m_tMax;
};

PRAALINE_CORE_END_NAMESPACE

Q_DECLARE_METATYPE(PRAALINE_CORE_NAMESPACE::Interval)
Q_DECLARE_METATYPE(PRAALINE_CORE_NAMESPACE::Interval *)

#endif // INTERVAL_H
