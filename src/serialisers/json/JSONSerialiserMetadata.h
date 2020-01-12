#ifndef JSONSERIALISERMETADATA_H
#define JSONSERIALISERMETADATA_H

/*
    Praaline - Core module - JSON Serialisers
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

#include <QList>
#include <QJsonObject>

#include "pncore_global.h"
#include "JSONSerialiserBase.h"
#include "serialisers/base/SerialiserMetadata.h"
#include "corpus/Corpus.h"
#include "corpus/CorpusCommunication.h"
#include "corpus/CorpusSpeaker.h"
#include "corpus/CorpusRecording.h"
#include "corpus/CorpusAnnotation.h"
#include "structure/MetadataStructure.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class JSONSerialiserMetadata : public JSONSerialiserBase, public SerialiserMetadata
{
public:
    static bool saveCorpus(Corpus *corpus, MetadataStructure* structure, QJsonObject &json);
    static bool saveCommunication(CorpusCommunication *com, MetadataStructure *structure, QJsonObject &json);
    static bool saveSpeaker(CorpusSpeaker *spk, MetadataStructure *structure, QJsonObject &json);
    static bool saveRecording(CorpusRecording *rec, MetadataStructure *structure, QJsonObject &json);
    static bool saveAnnotation(CorpusAnnotation *annot, MetadataStructure *structure, QJsonObject &json);
    static bool saveParticipation(CorpusParticipation *participation, MetadataStructure *structure, QJsonObject &json);

    static bool saveCorpora(const QList<Corpus *> &list, MetadataStructure *structure, QJsonObject &json);
    static bool saveCommunications(const QList<CorpusCommunication *> &list, MetadataStructure *structure, QJsonObject &json);
    static bool saveSpeakers(const QList<CorpusSpeaker *> &list, MetadataStructure *structure, QJsonObject &json);
    static bool saveRecordings(const QList<CorpusRecording *> &list, MetadataStructure *structure, QJsonObject &json);
    static bool saveAnnotations(const QList<CorpusAnnotation *> &list, MetadataStructure *structure, QJsonObject &json);
    static bool saveParticipations(const QList<CorpusParticipation *> &list, MetadataStructure *structure, QJsonObject &json);

    static bool loadCorpora(QList<Corpus *> &list, MetadataStructure *structure, QJsonObject &json);
    static bool loadCommunications(QList<CorpusCommunication *> &list, MetadataStructure *structure, QJsonObject &json);
    static bool loadSpeakers(QList<CorpusSpeaker *> &list, MetadataStructure *structure, QJsonObject &json);
    static bool loadRecordings(QList<CorpusRecording *> &list, MetadataStructure *structure, QJsonObject &json);
    static bool loadAnnotations(QList<CorpusAnnotation *> &list, MetadataStructure *structure, QJsonObject &json);
   // static bool loadParticipations(QList<CorpusParticipation *> &list, MetadataStructure *structure, QJsonObject &json);

protected:
    JSONSerialiserMetadata();
    ~JSONSerialiserMetadata();

private:
    static Corpus *readCorpus(MetadataStructure *structure, QJsonObject &json);
    static CorpusCommunication *readCommunication(MetadataStructure *structure, QJsonObject &json);
    static CorpusSpeaker *readSpeaker(MetadataStructure *structure, QJsonObject &json);
    static CorpusRecording *readRecording(MetadataStructure *structure, QJsonObject &json);
    static CorpusAnnotation *readAnnotation(MetadataStructure *structure, QJsonObject &json);
   // static CorpusParticipation *readParticipation(MetadataStructure *structure, QJsonObject &json);

    static void readAttributes(CorpusObject::Type what, CorpusObject *obj, MetadataStructure *structure, QJsonObject &json);
};

PRAALINE_CORE_END_NAMESPACE

#endif // JSONSERIALISERMETADATA_H
