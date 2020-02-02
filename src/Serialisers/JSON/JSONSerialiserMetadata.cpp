#include <QList>
#include <QJsonObject>

#include "PraalineCore/Corpus/Corpus.h"
#include "PraalineCore/Corpus/CorpusCommunication.h"
#include "PraalineCore/Corpus/CorpusSpeaker.h"
#include "PraalineCore/Corpus/CorpusRecording.h"
#include "PraalineCore/Corpus/CorpusAnnotation.h"
#include "PraalineCore/Structure/MetadataStructure.h"
#include "PraalineCore/Serialisers/JSON/JSONSerialiserBase.h"
#include "PraalineCore/Serialisers/JSON/JSONSerialiserMetadata.h"

PRAALINE_CORE_BEGIN_NAMESPACE

JSONSerialiserMetadata::JSONSerialiserMetadata() {}
JSONSerialiserMetadata::~JSONSerialiserMetadata() {}

// public static
bool JSONSerialiserMetadata::saveCorpus(Corpus *corpus, MetadataStructure* structure, QJsonObject &json)
{
    Q_UNUSED(corpus)
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return false;
}

// public static
bool JSONSerialiserMetadata::saveCommunication(CorpusCommunication *com, MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(com)
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return false;
}

// public static
bool JSONSerialiserMetadata::saveSpeaker(CorpusSpeaker *spk, MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(spk)
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return false;
}

// public static
bool JSONSerialiserMetadata::saveRecording(CorpusRecording *rec, MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(rec)
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return false;
}

// public static
bool JSONSerialiserMetadata::saveAnnotation(CorpusAnnotation *annot, MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(annot)
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return false;
}

// public static
bool JSONSerialiserMetadata::saveParticipation(CorpusParticipation *participation, MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(participation)
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return false;
}

// ========================================================================================================================================

// public static
bool JSONSerialiserMetadata::saveCorpora(const QList<Corpus *> &list, MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(list)
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return false;
}

// public static
bool JSONSerialiserMetadata::saveCommunications(const QList<CorpusCommunication *> &list, MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(list)
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return false;
}

// public static
bool JSONSerialiserMetadata::saveSpeakers(const QList<CorpusSpeaker *> &list, MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(list)
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return false;
}

// public static
bool JSONSerialiserMetadata::saveRecordings(const QList<CorpusRecording *> &list, MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(list)
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return false;
}

// public static
bool JSONSerialiserMetadata::saveAnnotations(const QList<CorpusAnnotation *> &list, MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(list)
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return false;
}

// public static
bool JSONSerialiserMetadata::saveParticipations(const QList<CorpusParticipation *> &list, MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(list)
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return false;
}

// ========================================================================================================================================

// public static
bool JSONSerialiserMetadata::loadCorpora(QList<Corpus *> &list, MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(list)
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return false;
}

// public static
bool JSONSerialiserMetadata::loadCommunications(QList<CorpusCommunication *> &list, MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(list)
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return false;
}

// public static
bool JSONSerialiserMetadata::loadSpeakers(QList<CorpusSpeaker *> &list, MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(list)
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return false;
}

// public static
bool JSONSerialiserMetadata::loadRecordings(QList<CorpusRecording *> &list, MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(list)
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return false;
}

// public static
bool JSONSerialiserMetadata::loadAnnotations(QList<CorpusAnnotation *> &list, MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(list)
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return false;
}

// public static
//bool JSONSerialiserMetadata::loadParticipations(QList<CorpusParticipation *> &list, MetadataStructure *structure, QJsonObject &json)
//{

//}

// ========================================================================================================================================

// private static
Corpus *JSONSerialiserMetadata::readCorpus(MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return nullptr;
}

// private static
CorpusCommunication *JSONSerialiserMetadata::readCommunication(MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return nullptr;
}

// private static
CorpusSpeaker *JSONSerialiserMetadata::readSpeaker(MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return nullptr;
}

// private static
CorpusRecording *JSONSerialiserMetadata::readRecording(MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return nullptr;
}

// private static
CorpusAnnotation *JSONSerialiserMetadata::readAnnotation(MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(structure)
    Q_UNUSED(json)
    return nullptr;
}

// private static
//CorpusParticipation *JSONSerialiserMetadata::readParticipation(MetadataStructure *structure, QJsonObject &json)
//{
//    return nullptr;
//}

// private static
void JSONSerialiserMetadata::readAttributes(CorpusObject::Type what, CorpusObject *obj, MetadataStructure *structure, QJsonObject &json)
{
    Q_UNUSED(what)
    Q_UNUSED(obj)
    Q_UNUSED(structure)
    Q_UNUSED(json)
}

PRAALINE_CORE_END_NAMESPACE
