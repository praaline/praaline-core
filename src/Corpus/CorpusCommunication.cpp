#include <QDebug>
#include <QObject>
#include <QString>

#include "PraalineCore/Corpus/CorpusObject.h"
#include "PraalineCore/Corpus/Corpus.h"
#include "PraalineCore/Corpus/CorpusRecording.h"
#include "PraalineCore/Corpus/CorpusAnnotation.h"
#include "PraalineCore/Corpus/CorpusCommunication.h"
#include "PraalineCore/Datastore/CorpusRepository.h"
#include "PraalineCore/Datastore/MetadataDatastore.h"

PRAALINE_CORE_BEGIN_NAMESPACE

CorpusCommunication::CorpusCommunication(CorpusRepository *repository, QObject *parent) :
    CorpusObject(repository, parent)
{
}

CorpusCommunication::CorpusCommunication(const QString &ID, CorpusRepository *repository, QObject *parent) :
    CorpusObject(ID, repository, parent)
{
}

CorpusCommunication::CorpusCommunication(CorpusCommunication *other, QObject *parent) :
    CorpusObject(nullptr, parent)
{
    if (!other) return;
    m_ID = other->m_ID;
    m_originalID = other->m_originalID;
    m_name = other->m_name;
    m_corpusID = other->m_corpusID;
    m_repository = other->m_repository;
    copyPropertiesFrom(other);
}

CorpusCommunication::~CorpusCommunication()
{
    qDeleteAll(m_recordings);
    qDeleteAll(m_annotations);
}

Corpus * CorpusCommunication::corpus() const
{
    return qobject_cast<Corpus *>(this->parent());
}

void CorpusCommunication::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;
        m_isDirty = true;
    }
}

void CorpusCommunication::setCorpusID(const QString &corpusID)
{
    if (m_corpusID != corpusID) {
        m_corpusID = corpusID;
        foreach (CorpusRecording * rec, m_recordings) if (rec) rec->setCorpusID(corpusID);
        foreach (CorpusAnnotation * annot, m_annotations) if (annot) annot->setCorpusID(corpusID);
        m_isDirty = true;
    }
}

// ==========================================================================================================
// ITEM MANAGEMENT
// ==========================================================================================================

// ==========================================================================================================
// Recordings
// ==========================================================================================================

CorpusRecording * CorpusCommunication::recording(const QString &recordingID) const
{
    return m_recordings.value(recordingID, nullptr);
}

int CorpusCommunication::recordingsCount() const
{
    return m_recordings.count();
}

bool CorpusCommunication::hasRecordings() const
{
    return !m_recordings.isEmpty();
}

bool CorpusCommunication::hasRecording(const QString &recordingID) const
{
    return m_recordings.contains(recordingID);
}

const QMap<QString, CorpusRecording *> &CorpusCommunication::recordings() const
{
    return m_recordings;
}

QList<QString> CorpusCommunication::recordingIDs() const
{
    return m_recordings.keys();
}

void CorpusCommunication::addRecording(CorpusRecording *recording)
{
    if (!recording) return;
    recording->setParent(this);
    recording->setCorpusID(this->corpusID());
    m_recordings.insert(recording->ID(), recording);
    connect(recording, &CorpusObject::changedID, this, &CorpusCommunication::recordingChangedID);
    m_isDirty = true;
    emit corpusRecordingAdded(recording);
}

void CorpusCommunication::removeRecording(const QString &recordingID)
{
    if (!m_recordings.contains(recordingID)) return;
    CorpusRecording * recording = m_recordings.value(recordingID);
    // remove recording
    m_recordings.remove(recordingID);
    delete recording;
    m_isDirty = true;
    deletedRecordingIDs << recordingID;
    emit corpusRecordingDeleted(this->ID(), recordingID);
}

//void CorpusCommunication::unlinkRecording(const QString &recordingID)
//{
//    if (!m_recordings.contains(recordingID)) return;
//    CorpusRecording * recording = m_recordings.value(recordingID);
//    m_recordings.remove(recordingID);
//    recording->setNew(true);
//    m_isDirty = true;
//    deletedRecordingIDs << recordingID;
//    emit corpusRecordingDeleted(this->ID(), recordingID);
//}

void CorpusCommunication::recordingChangedID(const QString &oldID, const QString &newID)
{
    if (oldID == newID) return;
    CorpusRecording * recording = m_recordings.value(oldID);
    if (!recording) return;
    m_recordings.remove(oldID);
    m_recordings.insert(newID, recording);
}

double CorpusCommunication::durationSec() const
{
    double duration(0);
    foreach (CorpusRecording * rec, m_recordings) {
        if (!rec) continue;
        if (rec->duration().toDouble() > duration) duration = rec->duration().toDouble();
    }
    return duration;
}

// ==========================================================================================================
// Annotations
// ==========================================================================================================

CorpusAnnotation * CorpusCommunication::annotation(const QString &annotationID) const
{
    return m_annotations.value(annotationID, nullptr);
}

int CorpusCommunication::annotationsCount() const
{
    return m_annotations.count();
}

bool CorpusCommunication::hasAnnotations() const
{
    return !m_annotations.isEmpty();
}

bool CorpusCommunication::hasAnnotation(const QString &annotationID) const
{
    return m_annotations.contains(annotationID);
}

const QMap<QString, CorpusAnnotation *> &CorpusCommunication::annotations() const
{
    return m_annotations;
}

QList<QString> CorpusCommunication::annotationIDs() const
{
    return m_annotations.keys();
}

void CorpusCommunication::addAnnotation(CorpusAnnotation *annotation)
{
    if (!annotation) return;
    annotation->setParent(this);
    annotation->setCorpusID(this->corpusID());
    m_annotations.insert(annotation->ID(), annotation);
    connect(annotation, &CorpusObject::changedID, this, &CorpusCommunication::annotationChangedID);
    m_isDirty = true;
    emit corpusAnnotationAdded(annotation);
}

void CorpusCommunication::removeAnnotation(const QString &annotationID)
{
    if (!m_annotations.contains(annotationID)) return;
    CorpusAnnotation * annotation = m_annotations.value(annotationID);
    // remove annotation
    m_annotations.remove(annotationID);
    delete annotation;
    m_isDirty = true;
    deletedAnnotationIDs << annotationID;
    emit corpusAnnotationDeleted(this->ID(), annotationID);
}

//void CorpusCommunication::unlinkAnnotation(const QString &annotationID)
//{
//    if (!m_annotations.contains(annotationID)) return;
//    CorpusAnnotation * annotation = m_annotations.value(annotationID);
//    m_annotations.remove(annotationID);
//    annotation->setNew(true);
//    m_isDirty = true;
//    deletedAnnotationIDs << annotationID;
//    emit corpusAnnotationDeleted(this->ID(), annotationID);
//}

void CorpusCommunication::annotationChangedID(const QString &oldID, const QString &newID)
{
    if (oldID == newID) return;
    CorpusAnnotation * annotation = m_annotations.value(oldID);
    if (!annotation) return;
    m_annotations.remove(oldID);
    m_annotations.insert(newID, annotation);
}

// ----------------------------------------------------------------------------------------------------------------
// Speaker Relations within this Communication
// ----------------------------------------------------------------------------------------------------------------

void removeSpeakerRelation(const QString &speakerID_1, const QString &speakerID_2);


CorpusCommunicationSpeakerRelation CorpusCommunication::speakerRelation(const QString &speakerID_1, const QString &speakerID_2)
{
    for (const auto &rel : m_speakerRelations) {
        if ((rel.speakerID_1() == speakerID_1) && (rel.speakerID_2() == speakerID_2)) {
            return rel;
        }
    }
    return CorpusCommunicationSpeakerRelation(speakerID_1, speakerID_2);
}

const QList<CorpusCommunicationSpeakerRelation> &CorpusCommunication::speakerRelations() const
{
    return m_speakerRelations;
}

QList<CorpusCommunicationSpeakerRelation> &CorpusCommunication::speakerRelations()
{
    return m_speakerRelations;
}

bool CorpusCommunication::hasSpeakerRelation(const QString &speakerID_1, const QString &speakerID_2)
{
    for (const auto &rel : m_speakerRelations) {
        if ((rel.speakerID_1() == speakerID_1) && (rel.speakerID_2() == speakerID_2)) {
            return true;
        }
    }
    return false;
}

void CorpusCommunication::insertSpeakerRelation(const CorpusCommunicationSpeakerRelation &relation)
{
    if (relation.speakerID_1().isEmpty()) return;
    if (relation.speakerID_2().isEmpty()) return;
    // search for existing relation between these two speakers
    for (auto &existingRelation : m_speakerRelations) {
        if ((existingRelation.speakerID_1() == relation.speakerID_1()) && (existingRelation.speakerID_2() == relation.speakerID_2())) {
            // found existing relation, update
            existingRelation.setRelation(relation.relation());
            existingRelation.setNotes(relation.notes());
            return;
        }
    }
    // otherwise, add new relation
    m_speakerRelations << relation;
}

void CorpusCommunication::removeSpeakerRelation(const QString &speakerID_1, const QString &speakerID_2)
{
    int i { 0 }, found { -1 };
    for (auto &rel: m_speakerRelations) {
        if ((rel.speakerID_1() == speakerID_1) && (rel.speakerID_2() == speakerID_2)) {
            found = i;
            break;
        }
        i++;
    }
    if (found < 0) return;
    m_speakerRelations.removeAt(found);
}

// ----------------------------------------------------------------------------------------------------------------

bool CorpusCommunication::save() {
    if (!m_repository) return false;
    if (!m_repository->metadata()) return false;
    return m_repository->metadata()->saveCommunications(QList<CorpusCommunication *>() << this);
}

PRAALINE_CORE_END_NAMESPACE
