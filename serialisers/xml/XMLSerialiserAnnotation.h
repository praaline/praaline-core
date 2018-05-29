#ifndef XMLSERIALISERANNOTATION_H
#define XMLSERIALISERANNOTATION_H

/*
    Praaline - Core module - XML Serialisers
    Copyright (c) 2011-2018 George Christodoulides

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
#include "base/RealTime.h"
#include "XMLSerialiserBase.h"

namespace Praaline {
namespace Core {

class Interval;
class AnnotationTier;
class AnnotationTierGroup;
class AnnotationStructure;

class XMLSerialiserAnnotation : public XMLSerialiserBase
{

public:
    static bool saveTiers(const QString &annotationID, const QString &speakerID,
                          AnnotationTierGroup *tiers, AnnotationStructure *structure, const QString &filename);
    static bool saveTier(const QString &annotationID, const QString &speakerID,
                         AnnotationTier *tier, AnnotationStructure *structure, const QString &filename);

    static AnnotationTierGroup *getTiers(const QString &annotationID, const QString &speakerID,
                                         const AnnotationStructure *structure, const QString &filename,
                                         const QStringList &levelIDs = QStringList());
    static AnnotationTier *getTier(const QString &annotationID, const QString &speakerID,
                                   const AnnotationStructure *structure, const QString &filename,
                                   const QString &levelID, const QStringList &attributeIDs = QStringList());

    static QMap<RealTime, Interval *> getSpeakerTimeline(const QString &annotationID, const QString &levelID);

private:
    XMLSerialiserAnnotation();    
};

} // namespace Core
} // namespace Praaline

#endif // XMLSERIALISERANNOTATION_H
