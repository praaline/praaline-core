#ifndef SERIALISERMETADATA_H
#define SERIALISERMETADATA_H

/*
    Praaline - Core module - Serialisers
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

#include <QStringList>
#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Corpus/CorpusObjectInfo.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class MetadataStructure;

class SerialiserMetadata
{
protected:
    SerialiserMetadata();
    virtual ~SerialiserMetadata();

    /// The default value of requestedAttributeIDs is an empty QStringList, in which case only the basic attributes of the
    /// requested Corpus Object will be returned.
    static QStringList getEffectiveAttributeIDs(MetadataStructure *structure, CorpusObject::Type type,
                                                const QStringList &requestedAttributeIDs = QStringList());
};

PRAALINE_CORE_END_NAMESPACE

#endif // SERIALISERMETADATA_H
