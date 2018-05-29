#ifndef SQLSERIALISERMETADATA_H
#define SQLSERIALISERMETADATA_H

/*
    Praaline - Core module - SQL Serialisers
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

#include <QPointer>
#include <QSqlDatabase>
#include "base/IDatastore.h"
#include "corpus/CorpusObjectInfo.h"
#include "corpus/Corpus.h"
#include "corpus/CorpusCommunication.h"
#include "corpus/CorpusSpeaker.h"
#include "corpus/CorpusRecording.h"
#include "corpus/CorpusAnnotation.h"
#include "corpus/CorpusParticipation.h"
#include "datastore/MetadataDatastore.h"

namespace Praaline {
namespace Core {

class MetadataStructure;
class CorpusDatastore;

class SQLSerialiserMetadata : public IDatastore
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
    static QList<QPointer<CorpusCommunication> > getCommunications(
            const MetadataDatastore::Selection &selection, QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static QList<QPointer<CorpusSpeaker> > getSpeakers(
            const MetadataDatastore::Selection &selection, QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static QList<QPointer<CorpusRecording> > getRecordings(
            const MetadataDatastore::Selection &selection, QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static QList<QPointer<CorpusAnnotation> > getAnnotations(
            const MetadataDatastore::Selection &selection, QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static QMultiMap<QString, QPointer<CorpusRecording> > getRecordingsByCommunication(
            const MetadataDatastore::Selection &selection, QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static QMultiMap<QString, QPointer<CorpusAnnotation> > getAnnotationsByCommunication(
            const MetadataDatastore::Selection &selection, QSqlDatabase &db, MetadataStructure *structure, CorpusDatastore *datastore);
    static QList<QPointer<CorpusParticipation> > getParticipations(
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

private:
    SQLSerialiserMetadata() {}

    // Helper functions
    static QString tableName(CorpusObject::Type type);
    static QStringList getEffectiveAttributeIDs(MetadataStructure *structure, CorpusObject::Type type,
                                                const QStringList &requestedAttributeIDs = QStringList());

    static void readRecording(QSqlQuery &q, CorpusRecording *rec, MetadataStructure *structure);
    static void readAnnotation(QSqlQuery &q, CorpusAnnotation *annot, MetadataStructure *structure);

    static QString prepareInsertSQL(MetadataStructure *structure, CorpusObject::Type what, QStringList requestedAttributeIDs = QStringList());
    static QString prepareUpdateSQL(MetadataStructure *structure, CorpusObject::Type what, QStringList requestedAttributeIDs = QStringList());

    static bool execSaveCorpus(Corpus *corpus, MetadataStructure *structure, QSqlDatabase &db);
    static bool execSaveCommunication(CorpusCommunication *com, MetadataStructure *structure, QSqlDatabase &db);
    static bool execSaveSpeaker(CorpusSpeaker *spk, MetadataStructure *structure, QSqlDatabase &db);
    static bool execSaveRecording(QString communicationID, CorpusRecording *rec, MetadataStructure *structure, QSqlDatabase &db);
    static bool execSaveAnnotation(QString communicationID, CorpusAnnotation *annot, MetadataStructure *structure, QSqlDatabase &db);
    static bool execSaveParticipation(CorpusParticipation *participation, MetadataStructure *structure, QSqlDatabase &db);
    static bool execCleanUpCommunication(CorpusCommunication *com, QSqlDatabase &db);
};

} // namespace Core
} // namespace Praaline

#endif // SQLSERIALISERMETADATA_H
