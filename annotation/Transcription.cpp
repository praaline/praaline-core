#include <QString>
#include <QPointer>
#include <QList>
#include <QMap>

#include "corpus/Corpus.h"
#include "annotation/IntervalTier.h"

#include "Transcription.h"

namespace Praaline {
namespace Core {

struct TranscriptionData {
    QString annotationID;
    QString levelTranscription;
    QString levelEvent;
    QPointer<Corpus> corpus;
    QMap<QString, QPointer<IntervalTier> > tiers;
    QPointer<IntervalTier> tierEvent;
};


Transcription::Transcription(QObject *parent) :
    QObject(parent), d(new TranscriptionData)
{

}

Transcription::~Transcription()
{
    // Tiers will be deleted because their parent is this Transcription object.
    delete d;
}

int Transcription::speakerCount() const
{
    return 0;
}

QStringList Transcription::speakerIDs() const
{
    return QStringList();
}

QList<CorpusSpeaker> Transcription::speakers() const
{
    QList<CorpusSpeaker> ret;
    return ret;
}

} // namespace Core
} // namespace Praaline
