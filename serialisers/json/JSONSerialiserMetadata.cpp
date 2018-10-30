#include <QList>
#include <QPointer>
#include <QJsonObject>
#include "JSONSerialiserBase.h"
#include "corpus/Corpus.h"
#include "corpus/CorpusCommunication.h"
#include "corpus/CorpusSpeaker.h"
#include "corpus/CorpusRecording.h"
#include "corpus/CorpusAnnotation.h"
#include "structure/MetadataStructure.h"
#include "JSONSerialiserMetadata.h"

namespace Praaline {
namespace Core {

// public static
bool JSONSerialiserMetadata::saveCorpus(Corpus *corpus, MetadataStructure* structure, QJsonObject &json)
{
    return false;
}

// public static
bool JSONSerialiserMetadata::saveCommunication(CorpusCommunication *com, MetadataStructure *structure, QJsonObject &json)
{
    return false;
}

// public static
bool JSONSerialiserMetadata::saveSpeaker(CorpusSpeaker *spk, MetadataStructure *structure, QJsonObject &json)
{
    return false;
}

// public static
bool JSONSerialiserMetadata::saveRecording(CorpusRecording *rec, MetadataStructure *structure, QJsonObject &json)
{
    return false;
}

// public static
bool JSONSerialiserMetadata::saveAnnotation(CorpusAnnotation *annot, MetadataStructure *structure, QJsonObject &json)
{
    return false;
}

// public static
bool JSONSerialiserMetadata::saveParticipation(CorpusParticipation *participation, MetadataStructure *structure, QJsonObject &json)
{
    return false;
}

// ========================================================================================================================================

// public static
bool JSONSerialiserMetadata::saveCorpora(const QList<QPointer<Corpus> > &list, MetadataStructure *structure, QJsonObject &json)
{
    return false;
}

// public static
bool JSONSerialiserMetadata::saveCommunications(const QList<QPointer<CorpusCommunication> > &list, MetadataStructure *structure, QJsonObject &json)
{
    return false;
}

// public static
bool JSONSerialiserMetadata::saveSpeakers(const QList<QPointer<CorpusSpeaker> > &list, MetadataStructure *structure, QJsonObject &json)
{
    return false;
}

// public static
bool JSONSerialiserMetadata::saveRecordings(const QList<QPointer<CorpusRecording> > &list, MetadataStructure *structure, QJsonObject &json)
{
    return false;
}

// public static
bool JSONSerialiserMetadata::saveAnnotations(const QList<QPointer<CorpusAnnotation> > &list, MetadataStructure *structure, QJsonObject &json)
{
    return false;
}

// public static
bool JSONSerialiserMetadata::saveParticipations(const QList<QPointer<CorpusParticipation> > &list, MetadataStructure *structure, QJsonObject &json)
{
    return false;
}

// ========================================================================================================================================

// public static
bool JSONSerialiserMetadata::loadCorpora(QList<QPointer<Corpus> > &list, MetadataStructure *structure, QJsonObject &json)
{
    return false;
}

// public static
bool JSONSerialiserMetadata::loadCommunications(QList<QPointer<CorpusCommunication> > &list, MetadataStructure *structure, QJsonObject &json)
{
    return false;
}

// public static
bool JSONSerialiserMetadata::loadSpeakers(QList<QPointer<CorpusSpeaker> > &list, MetadataStructure *structure, QJsonObject &json)
{
    return false;
}

// public static
bool JSONSerialiserMetadata::loadRecordings(QList<QPointer<CorpusRecording> > &list, MetadataStructure *structure, QJsonObject &json)
{
    return false;
}

// public static
bool JSONSerialiserMetadata::loadAnnotations(QList<QPointer<CorpusAnnotation> > &list, MetadataStructure *structure, QJsonObject &json)
{
    return false;
}

// public static
//bool JSONSerialiserMetadata::loadParticipations(QList<QPointer<CorpusParticipation> > &list, MetadataStructure *structure, QJsonObject &json)
//{

//}

// ========================================================================================================================================

// private static
Corpus *JSONSerialiserMetadata::readCorpus(MetadataStructure *structure, QJsonObject &json)
{
    return nullptr;
}

// private static
CorpusCommunication *JSONSerialiserMetadata::readCommunication(MetadataStructure *structure, QJsonObject &json)
{
    return nullptr;
}

// private static
CorpusSpeaker *JSONSerialiserMetadata::readSpeaker(MetadataStructure *structure, QJsonObject &json)
{
    return nullptr;
}

// private static
CorpusRecording *JSONSerialiserMetadata::readRecording(MetadataStructure *structure, QJsonObject &json)
{
    return nullptr;
}

// private static
CorpusAnnotation *JSONSerialiserMetadata::readAnnotation(MetadataStructure *structure, QJsonObject &json)
{
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

}

} // namespace Core
} // namespace Praaline
