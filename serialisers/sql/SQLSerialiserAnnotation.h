#ifndef SQLSERIALISERANNOTATION_H
#define SQLSERIALISERANNOTATION_H

/*
    Praaline - Core module - SQL Serialisers
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

#include <QSqlDatabase>

#include "pncore_global.h"
#include "SQLSerialiserBase.h"
#include "serialisers/base/SerialiserAnnotation.h"
#include "base/IDatastore.h"
#include "annotation/AnnotationElement.h"
#include "annotation/Point.h"
#include "annotation/Interval.h"
#include "annotation/Sequence.h"
#include "annotation/Relation.h"
#include "annotation/AnnotationTier.h"
#include "annotation/AnnotationTierGroup.h"
#include "structure/AnnotationStructure.h"
#include "datastore/AnnotationDatastore.h"

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
    static QMap<QString, QPointer<AnnotationTierGroup> > getTiersAllSpeakers(
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

private:
    SQLSerialiserAnnotation() {}
};

PRAALINE_CORE_END_NAMESPACE

#endif // SQLSERIALISERANNOTATION_H
