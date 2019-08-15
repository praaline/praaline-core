#ifndef POINT_H
#define POINT_H

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
#include "base/RealTime.h"
#include "AnnotationElement.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT Point : public AnnotationElement
{
    friend class PointTier;

public:
    Point();
    explicit Point(const RealTime time,
                   const QString &text = QString(), const QHash<QString, QVariant> &attributes = QHash<QString, QVariant>());
    Point(const Point &copy);
    virtual ~Point() override;

    // Properties
    inline RealTime time() const { return m_time; }
    inline double test(RealTime a) const { return a.toDouble(); }

    // Overrides
    virtual QVariant attribute(const QString &name) const override;
    virtual void setAttribute(const QString &name, QVariant value) override;
    inline virtual ElementType elementType() const override {
        return Type_Point;
    }

    // Create new point from existing one
    Point *clone() const;
    Point *cloneWithoutAttributes() const;
    Point *cloneReposition(const RealTime time) const;
    Point *cloneRepositionWithoutAttributes(const RealTime time) const;

protected:
    RealTime m_time;    
};

PRAALINE_CORE_END_NAMESPACE

Q_DECLARE_METATYPE(PRAALINE_CORE_NAMESPACE::Point)

#endif // POINT_H
