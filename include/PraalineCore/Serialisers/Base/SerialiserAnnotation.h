#ifndef SERIALISERANNOTATION_H
#define SERIALISERANNOTATION_H

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
#include "PraalineCore/Structure/AnnotationStructure.h"
#include "PraalineCore/Structure/AnnotationStructureLevel.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class SerialiserAnnotation
{
protected:
    SerialiserAnnotation();
    virtual ~SerialiserAnnotation();

    /// Derives the list of levels that will be retrieved from the datastore, based on a list of user-requested
    /// level IDs and the relationship between levels: derived levels (sequences, trees, relations) should be
    /// retrieved along with their parent levels.
    static QStringList getEffectiveLevelIDs(AnnotationStructure *structure, const QStringList &levelIDs);

    /// Derives the list of attributes that will be requested from the datastore, based on the
    /// user-requested attribute IDs and the attribute IDs actually in the datastore's structure.
    static QStringList getEffectiveAttributeIDs(AnnotationStructureLevel *level, const QStringList &attributeIDs);

};

PRAALINE_CORE_END_NAMESPACE

#endif // SERIALISERANNOTATION_H
