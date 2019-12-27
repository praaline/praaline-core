#ifndef DIFFPOINTS_H
#define DIFFPOINTS_H

/*
    Praaline - Core module - Diff
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
#include "annotation/Point.h"
#include "dtl/dtl.h"

using dtl::Diff;

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT ComparePoint : dtl::Compare<Point *>
{
public:
    ComparePoint(bool compareTimes, const QString &attributeID_A, const QString &attributeID_B);
    ComparePoint(const ComparePoint &other);
    virtual ~ComparePoint() override;

    bool compareTimes() const { return m_compareTimes; }
    QString attributeID_A() const { return m_attributeID_A; }
    QString attributeID_B() const { return m_attributeID_B; }

    virtual inline bool impl (PRAALINE_CORE_NAMESPACE::Point * const& e1, PRAALINE_CORE_NAMESPACE::Point * const& e2) const override;

private:
    const bool m_compareTimes;
    const QString m_attributeID_A;
    const QString m_attributeID_B;
};

class PRAALINE_CORE_SHARED_EXPORT DiffPoints
{
public:
    DiffPoints();
    ~DiffPoints();

    static Diff<std::string> stringDiff(QList<Praaline::Core::Point *> listA, QList<Praaline::Core::Point *> listB,
                                        QString attributeID_A = QString(), QString attributeID_B = QString());
    static Diff<PRAALINE_CORE_NAMESPACE::Point *, std::vector<PRAALINE_CORE_NAMESPACE::Point *>, ComparePoint>

    PointDiff(QList<PRAALINE_CORE_NAMESPACE::Point *> listA, QList<PRAALINE_CORE_NAMESPACE::Point *> listB,
              bool compareTimes = false,
              QString attributeID_A = QString(), QString attributeID_B = QString());

    static QString diffTable(Diff<PRAALINE_CORE_NAMESPACE::Point *, std::vector<PRAALINE_CORE_NAMESPACE::Point *>, ComparePoint> &diff);
};

PRAALINE_CORE_END_NAMESPACE

#endif // DIFFPOINTS_H
