#include <QString>
#include <QPointer>
#include <QList>
#include <QMap>

#include "corpus/Corpus.h"
#include "annotation/IntervalTier.h"

#include "Transcription.h"

PRAALINE_CORE_BEGIN_NAMESPACE


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

PRAALINE_CORE_END_NAMESPACE

