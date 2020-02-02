#ifndef SQLSERIALISERANNOTATION_H
#define SQLSERIALISERANNOTATION_H

/*
    Praaline - Core module - SQL Serialisers
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

#include <QSqlDatabase>

#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Base/IDatastore.h"
#include "PraalineCore/Annotation/AnnotationElement.h"
#include "PraalineCore/Annotation/Point.h"
#include "PraalineCore/Annotation/Interval.h"
#include "PraalineCore/Annotation/Sequence.h"
#include "PraalineCore/Annotation/Relation.h"
#include "PraalineCore/Annotation/AnnotationTier.h"
#include "PraalineCore/Annotation/AnnotationTierGroup.h"
#include "PraalineCore/Structure/AnnotationStructure.h"
#include "PraalineCore/Datastore/AnnotationDatastore.h"
#include "PraalineCore/Serialisers/Base/SerialiserAnnotation.h"

#include "Serialisers/SQL/SQLSerialiserBase.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class SQLSerialiserAnnotation : public SerialiserAnnotation, public SQLSerialiserBase, public IDatastore
{
public:
    // ==========================================================================================================================
    // Annotation Elements
    // ==========================================================================================================================
    static QList<AnnotationElement *> getAnnotationElements(
            const AnnotationDatastore::Selection &selection, AnnotationStructure *structure, QSqlDatabase &db);
    static QList<Point *> getPoints(
            const AnnotationDatastore::Selection &selection, AnnotationStructure *structure, QSqlDatabase &db);
    static QList<Interval *> getIntervals(
            const AnnotationDatastore::Selection &selection, AnnotationStructure *structure, QSqlDatabase &db);
    static QList<Sequence *> getSequences(
            const AnnotationDatastore::Selection &selection, AnnotationStructure *structure, QSqlDatabase &db);
    static bool saveAnnotationElements(
            const QList<AnnotationElement *> &elements, const QString &levelID, const QStringList &attributeIDs,
            AnnotationStructure *structure, QSqlDatabase &db);

    // ==========================================================================================================================
    // Annotation Tiers
    // ==========================================================================================================================
    static AnnotationTier *getTier(
            const QString &annotationID, const QString &speakerID, const QString &levelID, const QStringList &attributeIDs,
            AnnotationStructure *structure, QSqlDatabase &db);
    static AnnotationTierGroup *getTiers(
            const QString &annotationID, const QString &speakerID, const QStringList &levelIDs,
            AnnotationStructure *structure, QSqlDatabase &db);
    static SpeakerAnnotationTierGroupMap getTiersAllSpeakers(
            const QString &annotationID, const QStringList &levelIDs, AnnotationStructure *structure, QSqlDatabase &db);
    static bool saveTier(const QString &annotationID, const QString &speakerID, AnnotationTier *tier,
                         AnnotationStructure *structure, QSqlDatabase &db);
    static bool saveTiers(const QString &annotationID, const QString &speakerID, AnnotationTierGroup *tiers,
                          AnnotationStructure *structure, QSqlDatabase &db);
    static bool deleteTier(const QString &annotationID, const QString &speakerID, const QString &levelID,
                           AnnotationStructure *structure, QSqlDatabase &db);
    static bool deleteAllTiersAllSpeakers(const QString &annotationID, AnnotationStructure *structure, QSqlDatabase &db);

    // ==========================================================================================================================
    // Speakers and Timeline
    // ==========================================================================================================================
    static QList<QString> getSpeakersInLevel(
            const QString &annotationID, const QString &levelID,
            AnnotationStructure *structure, QSqlDatabase &db, bool filter = false);
    static QList<QString> getSpeakersActiveInLevel(const QString &annotationID, const QString &levelID,
                                                   AnnotationStructure *structure, QSqlDatabase &db);
    static QList<QString> getSpeakersInAnnotation(const QString &annotationID,
                                                  AnnotationStructure *structure, QSqlDatabase &db);
    static QList<QString> getSpeakersActiveInAnnotation(const QString &annotationID,
                                                        AnnotationStructure *structure, QSqlDatabase &db);
    static IntervalTier *getSpeakerTimeline(const QString &communicationID, const QString &annotationID,
                                            const QString &levelID, bool detailed,
                                            AnnotationStructure *structure, QSqlDatabase &db);

    // ==========================================================================================================================
    // Batch Processing
    // ==========================================================================================================================
    static QList<QPair<QList<QVariant>, long> > getDistinctLabels(const QString &levelID, const QStringList &attributeIDs,
                                                                 AnnotationStructure *structure, QSqlDatabase &db);
    static bool batchUpdate(const QString &levelID, const QString &attributeID, const QVariant &newValue,
                            const QList<QPair<QString, QVariant> > &criteria,
                            AnnotationStructure *structure, QSqlDatabase &db);

    // ==========================================================================================================================
    // Statistics
    // ==========================================================================================================================
    static QList<QPair<QList<QVariant>, long long> > countItems(
            const QString &levelID, const QStringList &groupByAttributeIDs, bool excludeNULL, QStringList excludeValues,
            AnnotationStructure *structure, QSqlDatabase &db);

protected:
    SQLSerialiserAnnotation();
    virtual ~SQLSerialiserAnnotation();
};

PRAALINE_CORE_END_NAMESPACE

#endif // SQLSERIALISERANNOTATION_H
