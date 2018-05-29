#ifndef XMLMETADATADATASTORE_H
#define XMLMETADATADATASTORE_H

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

#include <QObject>
#include "datastore/MetadataDatastore.h"

namespace Praaline {
namespace Core {

class MetadataStructure;

class XMLMetadataDatastore : public MetadataDatastore
{
    Q_OBJECT
public:
    XMLMetadataDatastore(MetadataStructure *structure, CorpusRepository *repository, QObject *parent = 0);
    ~XMLMetadataDatastore();

    // ==========================================================================================================================
    // Datastore
    // ==========================================================================================================================
    bool createDatastore(const DatastoreInfo &info) override;
    bool openDatastore(const DatastoreInfo &info) override;
    bool closeDatastore() override;

    // ==========================================================================================================================
    // Metadata Structure
    // ==========================================================================================================================
    bool loadMetadataStructure() override;
    bool saveMetadataStructure() override;
    bool createMetadataAttribute(CorpusObject::Type type, QPointer<MetadataStructureAttribute> newAttribute) override;
    bool renameMetadataAttribute(CorpusObject::Type type, const QString &attributeID, const QString &newAttributeID) override;
    bool deleteMetadataAttribute(CorpusObject::Type type, const QString &attributeID) override;
    bool retypeMetadataAttribute(CorpusObject::Type type, const QString &attributeID, const DataType &newDatatype) override;

    // ==========================================================================================================================
    // Name-value lists
    // ==========================================================================================================================
    NameValueList *getNameValueList(const QString &listID) override;
    QStringList getAllNameValueListIDs() override;
    QMap<QString, QPointer<NameValueList> > getAllNameValueLists() override;
    bool createNameValueList(NameValueList *list) override;
    bool updateNameValueList(NameValueList *list) override;
    bool deleteNameValueList(const QString &listID) override;

    // ==========================================================================================================================
    // Corpus object info lists
    // ==========================================================================================================================
    QList<CorpusObjectInfo> getCorpusObjectInfoList(CorpusObject::Type type, const Selection &selection) override;

    // ==========================================================================================================================
    // Corpus
    // ==========================================================================================================================
    // Load metadata information
    Corpus *getCorpus(const QString &corpusID) override;
    QList<QPointer<CorpusCommunication> > getCommunications(const Selection &selection) override;
    QList<QPointer<CorpusSpeaker> > getSpeakers(const Selection &selection) override;
    QList<QPointer<CorpusRecording> > getRecordings(const Selection &selection) override;
    QList<QPointer<CorpusAnnotation> > getAnnotations(const Selection &selection) override;
    QList<QPointer<CorpusParticipation> > getParticipations(const Selection &selection) override;

    // Save (insert or update) corpus objects
    bool saveCorpus(Corpus *corpus) override;
    bool saveCommunication(CorpusCommunication *communication) override;
    bool saveCommunications(QList<QPointer<CorpusCommunication> > &communications) override;
    bool saveSpeaker(CorpusSpeaker *speaker) override;
    bool saveSpeakers(QList<QPointer<CorpusSpeaker> > &speakers) override;
    bool saveRecordings(QList<QPointer<CorpusRecording> > &recordings) override;
    bool saveAnnotations(QList<QPointer<CorpusAnnotation> >  &annotations) override;
    bool saveParticipations(QList<QPointer<CorpusParticipation> >  &participations) override;

    // Delete corpus objects
    bool deleteCorpus(const QString &corpusID) override;
    bool deleteCommunication(const QString &communicationID) override;
    bool deleteSpeaker(const QString &speakerID) override;
    bool deleteRecording(const QString &recordingID) override;
    bool deleteAnnotation(const QString &annotationID) override;
    bool deleteParticipation(const QString &communicationID, const QString &speakerID) override;

private:
    QString m_filename;
    QPointer<MetadataStructure> m_structure;
};

} // namespace Core
} // namespace Praaline

#endif // XMLMETADATADATASTORE_H
