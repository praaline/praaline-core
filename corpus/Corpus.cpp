#include <QObject>
#include <QMetaEnum>
#include <QString>
#include <QList>
#include <QMap>
#include <QMultiHash>
#include <QPair>
#include <QDir>
#include "CorpusObject.h"
#include "Corpus.h"
#include "datastore/CorpusRepository.h"
#include "datastore/MetadataDatastore.h"

PRAALINE_CORE_BEGIN_NAMESPACE

Corpus::Corpus(CorpusRepository *repository, QObject *parent) :
    CorpusObject(repository, parent)
{
}

Corpus::Corpus(const QString &ID, CorpusRepository *repository, QObject *parent) :
    CorpusObject(ID, repository, parent)
{
    m_corpusID = ID;
}

Corpus::~Corpus()
{
    qDeleteAll(m_communications);
    qDeleteAll(m_speakers);
}

// ==============================================================================================================================
// Corpus
// ==============================================================================================================================

void Corpus::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;
        m_isDirty = true;
    }
}

void Corpus::setDescription(const QString &description)
{
    if (m_description != description) {
        m_description = description;
        m_isDirty = true;
    }
}

void Corpus::setCorpusID(const QString &corpusID)
{
    if (m_ID != corpusID) {
        m_ID = corpusID;
        m_corpusID = corpusID;
        foreach (CorpusCommunication * com, m_communications)
            if (com) com->setCorpusID(corpusID);
        foreach (CorpusSpeaker * spk, m_speakers)
            if (spk) spk->setCorpusID(corpusID);
        foreach (CorpusParticipation * part, m_participationsByCommunication.values())
            if (part) part->setCorpusID(corpusID);
        m_isDirty = true;
    }
}

void Corpus::clear()
{
    m_name = QString();
    m_description = QString();
    qDeleteAll(m_communications);
    m_communications.clear();
    qDeleteAll(m_speakers);
    m_speakers.clear();
}

bool Corpus::save() {
    if (!m_repository) return false;
    if (!m_repository->metadata()) return false;
    return m_repository->metadata()->saveCorpus(this);
}

// ==============================================================================================================================
// Communications
// ==============================================================================================================================

CorpusCommunication * Corpus::communication(const QString &communicationID) const
{
    return m_communications.value(communicationID, nullptr);
}

int Corpus::communicationsCount() const
{
    return m_communications.count();
}

bool Corpus::hasCommunications() const
{
    return !m_communications.isEmpty();
}

bool Corpus::hasCommunication(const QString &communicationID) const
{
    return m_communications.contains(communicationID);
}

QStringList Corpus::communicationIDs() const
{
    return m_communications.keys();
}

const QMap<QString, CorpusCommunication *> &Corpus::communications() const
{
    return m_communications;
}

void Corpus::addCommunication(CorpusCommunication *communication)
{
    if (!communication) return;
    communication->setParent(this);
    communication->setCorpusID(this->ID());
    m_communications.insert(communication->ID(), communication);
    // connect(communication, SIGNAL(changedID(QString,QString)), this, SLOT(communicationChangedID(QString,QString)));
    m_isDirty = true;
    emit communicationAdded(communication);
}

void Corpus::removeCommunication(const QString &communicationID)
{
    if (!m_communications.contains(communicationID)) return;
    CorpusCommunication * communication = m_communications.value(communicationID);
    // remove related participations before removing speaker
    QList<CorpusParticipation *> participationsToDelete;
    participationsToDelete = m_participationsByCommunication.values(communicationID);
    foreach (CorpusParticipation * participation, participationsToDelete)
        removeParticipation(participation->communicationID(), participation->speakerID());
    // remove communication
    m_communications.remove(communicationID);
    delete communication;
    m_isDirty = true;
    deletedCommunicationIDs << communicationID;
    emit communicationDeleted(communicationID);
}

void Corpus::communicationChangedID(const QString &oldID, const QString &newID)
{
    if (oldID == newID) return;
    CorpusCommunication * com = m_communications.value(oldID);
    if (!com) return;
    m_communications.remove(oldID);
    m_communications.insert(newID, com);
    // participations
    foreach (CorpusParticipation * participation, m_participationsByCommunication.values(oldID)) {
        m_participationsByCommunication.insert(newID, participation);
    }
    m_participationsByCommunication.remove(oldID);
}

// ==============================================================================================================================
// Speakers
// ==============================================================================================================================

CorpusSpeaker * Corpus::speaker(const QString &speakerID) const
{
    return m_speakers.value(speakerID, nullptr);
}

int Corpus::speakersCount() const
{
    return m_speakers.count();
}

bool Corpus::hasSpeakers() const
{
    return !m_speakers.isEmpty();
}

bool Corpus::hasSpeaker(const QString &speakerID) const
{
    return m_speakers.contains(speakerID);
}

QStringList Corpus::speakerIDs() const
{
    return m_speakers.keys();
}

const QMap<QString, CorpusSpeaker *> &Corpus::speakers() const
{
    return m_speakers;
}

void Corpus::addSpeaker(CorpusSpeaker *speaker)
{
    if (!speaker) return;
    speaker->setParent(this);
    speaker->setCorpusID(this->ID());
    m_speakers.insert(speaker->ID(), speaker);
    connect(speaker, SIGNAL(changedID(QString,QString)), this, SLOT(speakerChangedID(QString,QString)));
    m_isDirty = true;
    emit speakerAdded(speaker);
}

void Corpus::removeSpeaker(const QString &speakerID)
{
    CorpusSpeaker * speaker = m_speakers.value(speakerID, nullptr);
    if (!speaker) return;
    // remove related participations before removing speaker
    QList<CorpusParticipation *> participationsToDelete;
    participationsToDelete = m_participationsBySpeaker.values(speakerID);
    foreach (CorpusParticipation * participation, participationsToDelete) {
        if (!participation) continue;
        removeParticipation(participation->communicationID(), participation->speakerID());
    }
    // remove speaker
    m_speakers.remove(speakerID);
    delete speaker;
    m_isDirty = true;
    deletedSpeakerIDs << speakerID;
    emit speakerDeleted(speakerID);
}

void Corpus::speakerChangedID(const QString &oldID, const QString &newID)
{
    if (oldID == newID) return;
    CorpusSpeaker * spk = m_speakers.value(oldID);
    if (!spk) return;
    m_speakers.remove(oldID);
    m_speakers.insert(newID, spk);
    // participations
    foreach (CorpusParticipation * participation, m_participationsBySpeaker.values(oldID)) {
        m_participationsBySpeaker.insert(newID, participation);
    }
    m_participationsBySpeaker.remove(oldID);
}

// ==============================================================================================================================
// Participation of Speakers in Communications
// ==============================================================================================================================

CorpusParticipation * Corpus::participation(const QString &communicationID, const QString &speakerID)
{
    foreach (CorpusParticipation * participation, m_participationsByCommunication.values(communicationID)) {
        if (participation && participation->speakerID() == speakerID)
            return participation;
    }
    return nullptr;
}

bool Corpus::hasParticipation(const QString &communicationID, const QString &speakerID)
{
    foreach (CorpusParticipation * participation, m_participationsByCommunication.values(communicationID)) {
        if (participation && participation->speakerID() == speakerID)
            return true;
    }
    return false;
}

QList<CorpusParticipation *> Corpus::participations()
{
    return m_participationsByCommunication.values();
}

QList<CorpusParticipation *> Corpus::participationsForCommunication(const QString &communicationID)
{
    return m_participationsByCommunication.values(communicationID);
}

QList<CorpusParticipation *> Corpus::participationsForSpeaker(const QString &speakerID)
{
    return m_participationsBySpeaker.values(speakerID);
}

CorpusParticipation * Corpus::addParticipation(const QString &communicationID, const QString &speakerID, const QString &role)
{
    CorpusCommunication * com = this->communication(communicationID);
    CorpusSpeaker * spk = this->speaker(speakerID);
    if (!com || !spk) return nullptr;
    CorpusParticipation *participation = new CorpusParticipation(com, spk, role, this);
    participation->setCorpusID(this->ID());
    m_participationsByCommunication.insert(communicationID, participation);
    m_participationsBySpeaker.insert(speakerID, participation);
    return participation;
}

void Corpus::removeParticipation(const QString &communicationID, const QString &speakerID)
{
    QList<CorpusParticipation *> participationsToDelete;
    foreach (CorpusParticipation * participation, m_participationsByCommunication.values(communicationID)) {
        if (participation && participation->speakerID() == speakerID) {
            m_participationsByCommunication.remove(communicationID, participation);
            participationsToDelete << participation;
        }
    }
    foreach (CorpusParticipation * participation, m_participationsBySpeaker.values(speakerID)) {
        if (participation && participation->communicationID() == communicationID) {
            m_participationsBySpeaker.remove(speakerID, participation);
        }
    }
    foreach (CorpusParticipation * participation, participationsToDelete) {
        if (participation) delete participation;
    }
    deletedParticipationIDs << QPair<QString, QString>(communicationID, speakerID);
}

// ==============================================================================================================================
// Other convenience methods
// ==============================================================================================================================

QStringList Corpus::recordingIDs() const
{
    QStringList list;
    foreach(CorpusCommunication * com, m_communications) {
        foreach(CorpusRecording * rec, com->recordings())
            if (rec) list << rec->ID();
    }
    return list;
}

QStringList Corpus::annotationIDs() const
{
    QStringList list;
    foreach(CorpusCommunication * com, m_communications) {
        foreach(CorpusAnnotation * annot, com->annotations())
            if (annot) list << annot->ID();
    }
    return list;
}

QList<CorpusCommunication *> Corpus::communicationsList() const
{
    return m_communications.values();
}

QList<CorpusSpeaker *> Corpus::speakersList() const
{
    return m_speakers.values();
}

QList<CorpusRecording *> Corpus::recordingsList() const
{
    QList<CorpusRecording *> list;
    foreach(CorpusCommunication * com, m_communications) {
        foreach(CorpusRecording * rec, com->recordings())
            if (rec) list << rec;
    }
    return list;
}

QList<CorpusAnnotation *> Corpus::annotationsList() const
{
    QList<CorpusAnnotation *> list;
    foreach(CorpusCommunication * com, m_communications) {
        foreach(CorpusAnnotation * annot, com->annotations())
            if (annot) list << annot;
    }
    return list;
}

QMap<QString, QPair<CorpusRecording *, CorpusAnnotation *> > Corpus::getRecordings_x_Annotations() const
{
    QMap<QString, QPair<CorpusRecording *, CorpusAnnotation *> > list;
    foreach(CorpusCommunication * com, m_communications) {
        if (!com) continue;
        foreach(CorpusRecording * rec, com->recordings()) {
            foreach(CorpusAnnotation * annot, com->annotations()) {
                if (!rec || !annot) continue;
                QPair<CorpusRecording *, CorpusAnnotation *> item(rec, annot);
                list.insert(rec->ID(), item);
            }
        }
    }
    return list;
}

QMap<QString, QPair<CorpusAnnotation *, CorpusRecording *> > Corpus::getAnnotations_x_Recordings() const
{
    QMap<QString, QPair<CorpusAnnotation *, CorpusRecording *> > list;
    foreach(CorpusCommunication * com, m_communications) {
        if (!com) continue;
        foreach(CorpusAnnotation * annot, com->annotations()) {
            foreach(CorpusRecording * rec, com->recordings()) {
                if (!rec || !annot) continue;
                QPair<CorpusAnnotation *, CorpusRecording *> item(annot, rec);
                list.insert(annot->ID(), item);
            }
        }
    }
    return list;
}

QList<QPair<QString, QString> > Corpus::getCommunicationsAnnotationsIDs() const
{
    QList<QPair<QString, QString> > list;
    foreach(CorpusCommunication * com, m_communications) {
        if (!com) continue;
        foreach (CorpusAnnotation * annot, com->annotations()) {
            if (!annot) continue;
            list << QPair<QString, QString>(com->ID(), annot->ID());
        }
    }
    return list;
}

QList<QPair<QString, QString> > Corpus::getCommunicationsRecordingsIDs() const
{
    QList<QPair<QString, QString> > list;
    foreach(CorpusCommunication * com, m_communications) {
        if (!com) continue;
        foreach (CorpusRecording * rec, com->recordings()) {
            if (!rec) continue;
            list << QPair<QString, QString>(com->ID(), rec->ID());
        }
    }
    return list;
}

PRAALINE_CORE_END_NAMESPACE

