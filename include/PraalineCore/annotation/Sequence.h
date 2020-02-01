#ifndef SEQUENCE_H
#define SEQUENCE_H

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

#include <QString>
#include <QVariant>
#include "praaline-core_global.h"
#include "base/RealTime.h"
#include "annotation/AnnotationElement.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT Sequence : public AnnotationElement
{
    friend class SequenceTier;
public:
    Sequence();
    Sequence(int indexFrom, int indexTo,
             const QString &text = QString(), const QHash<QString, QVariant> &attributes = QHash<QString, QVariant>());
    Sequence(const Sequence &copy);
    virtual ~Sequence() override;

    // Create new sequence from existing one
    Sequence *clone();
    Sequence *cloneWithoutAttributes();

    // Properties
    inline int indexFrom () const
        { return m_indexFrom; }
    inline int indexTo() const
        { return m_indexTo; }
    inline int length() const
        { return m_indexFrom - m_indexTo; }

    // Overrides
    virtual QVariant attribute(const QString &name) const override;
    virtual void setAttribute(const QString &name, QVariant value) override;
    inline virtual ElementType elementType() const override {
        return Type_Sequence;
    }

    int compare(const Sequence &other) const;

protected:
    int m_indexFrom;
    int m_indexTo;
};

PRAALINE_CORE_END_NAMESPACE

Q_DECLARE_METATYPE(PRAALINE_CORE_NAMESPACE::Sequence)

#endif // SEQUENCE_H
