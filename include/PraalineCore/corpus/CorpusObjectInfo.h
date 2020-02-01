#ifndef CORPUSOBJECTINFO_H
#define CORPUSOBJECTINFO_H

/*
    Praaline - Core module - Corpus metadata
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
#include "base/ISaveable.h"
#include "corpus/CorpusObject.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT CorpusObjectInfo : public ISaveable
{
    friend class MetadataDatastore;

public:
    explicit CorpusObjectInfo();
    explicit CorpusObjectInfo(CorpusObject::Type type);
    CorpusObjectInfo(const CorpusObjectInfo &other);
    virtual ~CorpusObjectInfo();
    // Notes: Requirements for QVariant are a public default constructor, a public copy constructor, and a public destructor.
    // All constructors set isNew and isDirty to true. If the object is retrieved from the database, the datastore will set
    // its state to Clean.

    inline virtual CorpusObject::Type type() const {
        return m_type;
    }

    inline virtual QVariant attribute(const QString &name) const {
        return m_attributes.value(name, QVariant());
    }

    inline virtual void setAttribute(const QString &name, QVariant value) {
        m_attributes.insert(name, value);
        m_isDirty = true;
    }

    inline virtual const QVariantHash attributes() const {
        return m_attributes;
    }

private:
    CorpusObject::Type m_type;
    QVariantHash m_attributes;
};

PRAALINE_CORE_END_NAMESPACE

Q_DECLARE_METATYPE(PRAALINE_CORE_NAMESPACE::CorpusObjectInfo)

#endif // CORPUSOBJECTINFO_H
