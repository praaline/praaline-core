#ifndef CORPUSCOMMUNICATION_H
#define CORPUSCOMMUNICATION_H

/*
    Praaline - Core module - Corpus metadata
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
#include <QString>
#include <QMap>
#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Corpus/CorpusObject.h"
#include "PraalineCore/Corpus/CorpusRecording.h"
#include "PraalineCore/Corpus/CorpusAnnotation.h"
#include "PraalineCore/Corpus/CorpusCommunicationSpeakerRelation.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class Corpus;

class PRAALINE_CORE_SHARED_EXPORT CorpusCommunication : public CorpusObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(double durationSec READ durationSec)

public:
    explicit CorpusCommunication(CorpusRepository *repository = nullptr, QObject *parent = nullptr);
    explicit CorpusCommunication(const QString &ID, CorpusRepository *repository = nullptr, QObject *parent = nullptr);
    explicit CorpusCommunication(CorpusCommunication *other, QObject *parent = nullptr);
    ~CorpusCommunication() override;

    CorpusObject::Type type() const override { return CorpusObject::Type_Communication; }
    bool save() override;

    Corpus * corpus() const;

    // Basic data
    QString name() const { return m_name; }
    void setName(const QString &name);

    void setCorpusID(const QString &corpusID) override;

    // ----------------------------------------------------------------------------------------------------------------
    // Recordings
    // ----------------------------------------------------------------------------------------------------------------
    CorpusRecording * recording(const QString &recordingID) const;
    int recordingsCount() const;
    bool hasRecordings() const;
    bool hasRecording(const QString &recordingID) const;
    const QMap<QString, CorpusRecording *> &recordings() const;
    QList<QString> recordingIDs() const;
    void addRecording(CorpusRecording *recording);
    void removeRecording(const QString &recordingID);
    //void unlinkRecording(const QString &recordingID);
    double durationSec() const;

    // ----------------------------------------------------------------------------------------------------------------
    // Annotations
    // ----------------------------------------------------------------------------------------------------------------
    CorpusAnnotation * annotation(const QString &annotationID) const;
    int annotationsCount() const;
    bool hasAnnotations() const;
    bool hasAnnotation(const QString &annotationID) const;
    const QMap<QString, CorpusAnnotation *> &annotations() const;
    QList<QString> annotationIDs() const;
    void addAnnotation(CorpusAnnotation *annotation);
    void removeAnnotation(const QString &annotationID);
    //void unlinkAnnotation(const QString &annotationID);

    // ----------------------------------------------------------------------------------------------------------------
    // Speaker Relations within this Communication
    // ----------------------------------------------------------------------------------------------------------------
    CorpusCommunicationSpeakerRelation speakerRelation(const QString &speakerID_1, const QString &speakerID_2);
    const QList<CorpusCommunicationSpeakerRelation> &speakerRelations() const;
    QList<CorpusCommunicationSpeakerRelation> &speakerRelations();
    bool hasSpeakerRelation(const QString &speakerID_1, const QString &speakerID_2);
    void insertSpeakerRelation(const CorpusCommunicationSpeakerRelation &relation);
    void removeSpeakerRelation(const QString &speakerID_1, const QString &speakerID_2);

    // Database helpers
    QList<QString> deletedAnnotationIDs;
    QList<QString> deletedRecordingIDs;

signals:
    void corpusRecordingAdded(PRAALINE_CORE_NAMESPACE::CorpusRecording *recording);
    void corpusRecordingDeleted(QString communicationID, QString recordingID);
    void corpusAnnotationAdded(PRAALINE_CORE_NAMESPACE::CorpusAnnotation *annotation);
    void corpusAnnotationDeleted(QString communicationID, QString annotationID);

private slots:
    void recordingChangedID(const QString &oldID, const QString &newID);
    void annotationChangedID(const QString &oldID, const QString &newID);
    
private:
    QString m_name;
    QMap<QString, CorpusRecording *> m_recordings;
    QMap<QString, CorpusAnnotation *> m_annotations;
    QList<CorpusCommunicationSpeakerRelation> m_speakerRelations;

    Q_DISABLE_COPY(CorpusCommunication)
};

PRAALINE_CORE_END_NAMESPACE

#endif // CORPUSITEM_H
