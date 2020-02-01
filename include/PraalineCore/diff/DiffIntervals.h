#ifndef DIFFINTERVALS_H
#define DIFFINTERVALS_H

/*
    Praaline - Core module - Diff
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

#include <QString>

#include "praaline-core_global.h"
#include "annotation/Interval.h"
#include "diff/dtl/dtl.h"

using dtl::Diff;

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT CompareInterval : dtl::Compare<Interval *>
{
public:
    CompareInterval(bool compareBoundaries, const QString &attributeID_A, const QString &attributeID_B);
    CompareInterval(const CompareInterval &other);
    virtual ~CompareInterval() override;

    bool compareBoundaries() const { return m_compareBoundaries; }
    QString attributeID_A() const { return m_attributeID_A; }
    QString attributeID_B() const { return m_attributeID_B; }

    virtual inline bool impl (PRAALINE_CORE_NAMESPACE::Interval * const& e1, PRAALINE_CORE_NAMESPACE::Interval * const& e2) const override;

private:
    const bool m_compareBoundaries;
    const QString m_attributeID_A;
    const QString m_attributeID_B;
};

class PRAALINE_CORE_SHARED_EXPORT DiffIntervals
{
public:
    DiffIntervals();
    ~DiffIntervals();

    static Diff<std::string> stringDiff(QList<PRAALINE_CORE_NAMESPACE::Interval *> listA, QList<PRAALINE_CORE_NAMESPACE::Interval *> listB,
                                        QString attributeID_A = QString(), QString attributeID_B = QString());
    static Diff<PRAALINE_CORE_NAMESPACE::Interval *, std::vector<PRAALINE_CORE_NAMESPACE::Interval *>, CompareInterval>

    intervalDiff(QList<PRAALINE_CORE_NAMESPACE::Interval *> listA, QList<PRAALINE_CORE_NAMESPACE::Interval *> listB,
                 bool compareBoundaries = false,
                 QString attributeID_A = QString(), QString attributeID_B = QString());

    static QString diffTable(Diff<PRAALINE_CORE_NAMESPACE::Interval *, std::vector<PRAALINE_CORE_NAMESPACE::Interval *>, CompareInterval> &diff);
};

PRAALINE_CORE_END_NAMESPACE

#endif // DIFFINTERVALS_H
