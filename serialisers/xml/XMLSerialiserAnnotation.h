#ifndef XMLSERIALISERANNOTATION_H
#define XMLSERIALISERANNOTATION_H

/*
    Praaline - Core module - XML Serialisers
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

#include <QString>
#include <QMap>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "pncore_global.h"
#include "base/RealTime.h"
#include "base/IDatastore.h"
#include "XMLSerialiserBase.h"
#include "serialisers/base/SerialiserAnnotation.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class AnnotationTier;
class AnnotationTierGroup;
class AnnotationStructure;

class XMLSerialiserAnnotation : public SerialiserAnnotation, public XMLSerialiserBase, public IDatastore
{

public:
    static bool saveTiers(AnnotationTierGroup *tiers, AnnotationStructure *structure, QXmlStreamWriter &xml);
    static bool saveTier(AnnotationTier *tier, AnnotationStructure *structure, QXmlStreamWriter &xml);

    static AnnotationTierGroup *loadTiers(AnnotationStructure *structure, QXmlStreamReader &xml);
    static AnnotationTier *loadTier(AnnotationStructure *structure, QXmlStreamReader &xml);

private:
    XMLSerialiserAnnotation();    
    ~XMLSerialiserAnnotation();
};

PRAALINE_CORE_END_NAMESPACE

#endif // XMLSERIALISERANNOTATION_H
