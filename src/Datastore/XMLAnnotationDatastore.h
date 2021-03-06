#ifndef XMLANNOTATIONDATASTORE_H
#define XMLANNOTATIONDATASTORE_H

/*
    Praaline - Core module - XML Serialisers
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

#include <QObject>
#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Structure/AnnotationStructure.h"
#include "PraalineCore/Datastore/AnnotationDatastore.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class CorpusRepository;

class XMLAnnotationDatastore : public AnnotationDatastore
{
    Q_OBJECT
public:
    explicit XMLAnnotationDatastore(AnnotationStructure *structure, CorpusRepository *repository, QObject *parent = nullptr);
    ~XMLAnnotationDatastore() override;

    // ==========================================================================================================================
    // Datastore
    // ==========================================================================================================================
    bool createDatastore(const DatastoreInfo &info) override;
    bool openDatastore(const DatastoreInfo &info) override;
    bool closeDatastore() override;

    // ==========================================================================================================================
    // Annotation Structure
    // ==========================================================================================================================
    bool loadAnnotationStructure() override;
    bool saveAnnotationStructure() override;
    bool createAnnotationLevel(AnnotationStructureLevel *newLevel) override;
    bool renameAnnotationLevel(const QString &levelID, const QString &newLevelID) override;
    bool deleteAnnotationLevel(const QString &levelID) override;
    bool createAnnotationAttribute(const QString &levelID, AnnotationStructureAttribute *newAttribute) override;
    bool renameAnnotationAttribute(const QString &levelID, const QString &attributeID, const QString &newAttributeID) override;
    bool deleteAnnotationAttribute(const QString &levelID, const QString &attributeID) override;
    bool retypeAnnotationAttribute(const QString &levelID, const QString &attributeID, const DataType &newDatatype) override;

    // ==========================================================================================================================
    // Name-value lists
    // ==========================================================================================================================
    NameValueList *getNameValueList(const QString &listID) override;
    QStringList getAllNameValueListIDs() override;
    QMap<QString, NameValueList *> getAllNameValueLists() override;
    bool createNameValueList(NameValueList *list) override;
    bool updateNameValueList(NameValueList *list) override;
    bool deleteNameValueList(const QString &listID) override;

    // ==========================================================================================================================
    // Annotation Tiers
    // ==========================================================================================================================
    AnnotationTier *getTier(const QString &annotationID, const QString &speakerID,
                            const QString &levelID, const QStringList &attributeIDs = QStringList()) override;
    AnnotationTierGroup *getTiers(const QString &annotationID, const QString &speakerID,
                                  const QStringList &levelIDs = QStringList()) override;
    QMap<QString, AnnotationTierGroup *> getTiersAllSpeakers(const QString &annotationID,
                                                             const QStringList &levelIDs = QStringList()) override;
    bool saveTier(const QString &annotationID, const QString &speakerID, AnnotationTier *tier) override;
    bool saveTiers(const QString &annotationID, const QString &speakerID, AnnotationTierGroup *tiers) override;
    bool saveTiersAllSpeakers(const QString &annotationID, QMap<QString, AnnotationTierGroup *> &tiersAllSpeakers) override;
    bool deleteTier(const QString &annotationID, const QString &speakerID, const QString &levelID) override;
    bool deleteTiers(const QString &annotationID, const QString &speakerID, const QStringList &levelIDs = QStringList()) override;
    bool deleteAllTiersAllSpeakers(const QString &annotationID) override;

    // ==========================================================================================================================
    // Annotation Elements
    // ==========================================================================================================================
    QList<AnnotationElement *> getAnnotationElements(const Selection &selection) override;
    QList<Point *> getPoints(const Selection &selection) override;
    QList<Interval *> getIntervals(const Selection &selection) override;
    QList<Sequence *> getSequences(const Selection &selection) override;
    bool saveAnnotationElements(const QList<AnnotationElement *> &elements, const QString &levelID,
                                const QStringList &attributeIDs) override;

    // ==========================================================================================================================
    // Speakers and Timeline
    // ==========================================================================================================================
    QStringList getSpeakersInLevel(const QString &annotationID, const QString &levelID) override;
    QStringList getSpeakersActiveInLevel(const QString &annotationID, const QString &levelID) override;
    QStringList getSpeakersInAnnotation(const QString &annotationID) override;
    QStringList getSpeakersActiveInAnnotation(const QString &annotationID) override;
    IntervalTier *getSpeakerTimeline(const QString &communicationID,const QString &annotationID,
                                     const QString &levelID, bool detailed = false) override;

    // ==========================================================================================================================
    // Queries
    // ==========================================================================================================================
    QList<QueryOccurrencePointer *> runQuery(QueryDefinition *qdef) override;
    QueryOccurrence *getOccurrence(QueryOccurrencePointer *pointer, QueryDefinition *qdef,
                                   int lengthContextLeft = 10, int lengthContextRight = 10) override;
    bool updateAnnotationsFromQueryOccurrences(const QList<QueryOccurrence *> &occurrences) override;

    // ==========================================================================================================================
    // Batch Processing
    // ==========================================================================================================================
    QList<QPair<QList<QVariant>, long> > getDistinctLabels(const QString &levelID, const QStringList &attributeIDs) override;
    bool batchUpdate(const QString &levelID, const QString &attributeID, const QVariant &newValue,
                     const QList<QPair<QString, QVariant> > &criteria) override;

    // ==========================================================================================================================
    // Statistics
    // ==========================================================================================================================
    QList<QPair<QList<QVariant>, long long> > countItems(const QString &levelID, const QStringList &groupByAttributeIDs,
                                                         bool excludeNULL, QStringList excludeValues) override;

private:
    QString m_path;
    AnnotationStructure *m_structure;
};

PRAALINE_CORE_END_NAMESPACE

#endif // XMLANNOTATIONDATASTORE_H
