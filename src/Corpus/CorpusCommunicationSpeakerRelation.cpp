#include "PraalineCore/Corpus/CorpusCommunicationSpeakerRelation.h"

PRAALINE_CORE_BEGIN_NAMESPACE

CorpusCommunicationSpeakerRelation::CorpusCommunicationSpeakerRelation(const QString &speakerID_1, const QString &speakerID_2,
                                                                       const QString &relation, const QString &notes) :
    m_speakerID_1(speakerID_1), m_speakerID_2(speakerID_2), m_relation(relation), m_notes(notes)
{
}

QString CorpusCommunicationSpeakerRelation::speakerID_1() const
{
    return m_speakerID_1;
}

QString CorpusCommunicationSpeakerRelation::speakerID_2() const
{
    return m_speakerID_2;
}

QString CorpusCommunicationSpeakerRelation::relation() const
{
    return m_relation;
}

void CorpusCommunicationSpeakerRelation::setRelation(const QString &relation)
{
    m_relation = relation;
}

QString CorpusCommunicationSpeakerRelation::notes() const
{
    return m_notes;
}

void CorpusCommunicationSpeakerRelation::setNotes(const QString &notes)
{
    m_notes = notes;
}

PRAALINE_CORE_END_NAMESPACE
