#ifndef SQLSERIALISERMETADATA_H
#define SQLSERIALISERMETADATA_H

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
#include "PraalineCore/Corpus/CorpusObjectInfo.h"
#include "PraalineCore/Corpus/Corpus.h"
#include "PraalineCore/Corpus/CorpusCommunication.h"
#include "PraalineCore/Corpus/CorpusSpeaker.h"
#include "PraalineCore/Corpus/CorpusRecording.h"
#include "PraalineCore/Corpus/CorpusAnnotation.h"
#include "PraalineCore/Corpus/CorpusParticipation.h"
#include "PraalineCore/Datastore/MetadataDatastore.h"
#include "PraalineCore/Serialisers/Base/SerialiserMetadata.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class MetadataStructure;
class CorpusDatastore;

class SQLSerialiserMetadata : public SerialiserMetadata, public IDatastore
{
public:
    // Use this function to get the basic information for each corpus object and construct an hierarchical structure
    // of (lazy-loaded) corpus objects
    static QList<CorpusObjectInfo> getCorpusObjectInfoList(
            CorpusObject::Type type, const MetadataDatastore::Selection &selection,
            QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static bool saveCorpusObjectInfo(
            CorpusObject::Type type, const QList<CorpusObjectInfo> &list,
            QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);

    // Load metadata information
    static Corpus *getCorpus(
            const QString &corpusID, QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static QList<CorpusCommunication *> getCommunications(
            const MetadataDatastore::Selection &selection, QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static QList<CorpusSpeaker *> getSpeakers(
            const MetadataDatastore::Selection &selection, QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static QList<CorpusRecording *> getRecordings(
            const MetadataDatastore::Selection &selection, QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static QList<CorpusAnnotation *> getAnnotations(
            const MetadataDatastore::Selection &selection, QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static QMultiMap<QString, CorpusRecording *> getRecordingsByCommunication(
            const MetadataDatastore::Selection &selection, QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static QMultiMap<QString, CorpusAnnotation *> getAnnotationsByCommunication(
            const MetadataDatastore::Selection &selection, QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static QMultiMap<QString, CorpusCommunicationSpeakerRelation> getSpeakerRelationByCommunication(
            const MetadataDatastore::Selection &selection, QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static QList<CorpusParticipation *> getParticipations(
            const MetadataDatastore::Selection &selection, QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);

    // Save means insert or update, appropriately
    static bool saveCorpus(Corpus *corpus,
                           QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static bool saveCommunication(CorpusCommunication *communication,
                                  QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static bool saveSpeaker(CorpusSpeaker *speaker,
                            QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static bool saveRecording(CorpusRecording *recording,
                              QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static bool saveAnnotation(CorpusAnnotation *annotation,
                               QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static bool saveParticipation(CorpusParticipation *participation,
                                  QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);

    // Delete corpus objects
    static bool deleteCorpus(const QString &corpusID,
                             QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static bool deleteCommunication(const QString &communicationID,
                                    QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static bool deleteSpeaker(const QString &speakerID,
                              QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static bool deleteRecording(const QString &recordingID,
                                QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static bool deleteAnnotation(const QString &annotationID,
                                 QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static bool deleteParticipation(const QString &communicationID, const QString &speakerID,
                                    QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);

    // ==========================================================================================================================
    // Batch Processing
    // ==========================================================================================================================
    static QList<QPair<QList<QVariant>, long> > getDistinctValues(CorpusObject::Type type, const QStringList &attributeIDs,
                                                                  QSqlDatabase &db, MetadataStructure *structure);

protected:
    SQLSerialiserMetadata();
    ~SQLSerialiserMetadata();

private:
    // Helper functions
    static QString tableName(CorpusObject::Type type);

    static void readRecording(QSqlQuery &q, CorpusRecording *rec, MetadataStructure *structure);
    static void readAnnotation(QSqlQuery &q, CorpusAnnotation *annot, MetadataStructure *structure);
    static CorpusCommunicationSpeakerRelation readSpeakerRelation(QSqlQuery &q);

    static QString prepareInsertSQL(MetadataStructure *structure, CorpusObject::Type what, QStringList requestedAttributeIDs = QStringList());
    static QString prepareUpdateSQL(MetadataStructure *structure, CorpusObject::Type what, QStringList requestedAttributeIDs = QStringList());

    static bool execSaveCorpus(Corpus *corpus, MetadataStructure *structure, QSqlDatabase &db);
    static bool execSaveCommunication(CorpusCommunication *com, MetadataStructure *structure, QSqlDatabase &db);
    static bool execSaveSpeaker(CorpusSpeaker *spk, MetadataStructure *structure, QSqlDatabase &db);
    static bool execSaveRecording(QString communicationID, CorpusRecording *rec, MetadataStructure *structure, QSqlDatabase &db);
    static bool execSaveAnnotation(QString communicationID, CorpusAnnotation *annot, MetadataStructure *structure, QSqlDatabase &db);
    static bool execSaveParticipation(CorpusParticipation *participation, MetadataStructure *structure, QSqlDatabase &db);
    static bool execCleanUpCommunication(CorpusCommunication *com, QSqlDatabase &db);
    static bool execSaveCommunicationSpeakerRelations(CorpusCommunication *com, QSqlDatabase &db);
};

PRAALINE_CORE_END_NAMESPACE

#endif // SQLSERIALISERMETADATA_H
