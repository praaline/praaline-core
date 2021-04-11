#include "PraalineCore/Corpus/Corpus.h"
#include "PraalineCore/Corpus/CorpusSpeakerRelation.h"
#include "PraalineCore/Datastore/CorpusRepository.h"
#include "PraalineCore/Datastore/MetadataDatastore.h"

PRAALINE_CORE_BEGIN_NAMESPACE

CorpusSpeakerRelation::CorpusSpeakerRelation(const QString &relation,
                                             CorpusCommunication * com, CorpusSpeaker * spk1, CorpusSpeaker * spk2,
                                             QObject *parent) :
    CorpusObject(nullptr, parent), m_relation(relation), m_communication(com), m_speaker_1(spk1), m_speaker_2(spk2)
{
    if (com && spk1 && spk2) {
        m_ID = QString("%1::%2::%3::%4").arg(m_relation, m_communication->ID(), m_speaker_1->ID(), m_speaker_2->ID());
        m_repository = com->repository();
    }
    else {
        m_ID = "(deleted)";
    }
}

void CorpusSpeakerRelation::copyProperties(CorpusSpeakerRelation *other)
{
    if (!other) return;
    copyPropertiesFrom(other);
}

// override CorpusObject ID methods
QString CorpusSpeakerRelation::ID() const
{
    if (m_communication && m_speaker_1 && m_speaker_2)
        return QString("%1::%2::%3::%4").arg(m_relation, m_communication->ID(), m_speaker_1->ID(), m_speaker_2->ID());
    return "(deleted)";
}

void CorpusSpeakerRelation::setID(const QString &ID)
{
    Q_UNUSED(ID)
}

Corpus * CorpusSpeakerRelation::corpus() const
{
    return qobject_cast<Corpus *>(this->parent());
}

// read-only properties
QString CorpusSpeakerRelation::relation() const
{
    return m_relation;
}

CorpusCommunication * CorpusSpeakerRelation::communication() const
{
    return m_communication;
}

CorpusSpeaker * CorpusSpeakerRelation::speaker_1() const
{
    return m_speaker_1;
}

CorpusSpeaker * CorpusSpeakerRelation::speaker_2() const
{
    return m_speaker_2;
}

QString CorpusSpeakerRelation::communicationID() const
{
    if (m_communication) return m_communication->ID();
    return "(deleted)";
}

QString CorpusSpeakerRelation::speakerID_1() const
{
    if (m_speaker_1) return m_speaker_1->ID();
    return "(deleted)";
}

QString CorpusSpeakerRelation::speakerID_2() const
{
    if (m_speaker_2) return m_speaker_2->ID();
    return "(deleted)";
}

bool CorpusSpeakerRelation::save() {
    if (!m_repository) return false;
    if (!m_repository->metadata()) return false;
    //return m_repository->metadata()->saveParticipations(QList<CorpusParticipation *>() << this);
    return false;
}

PRAALINE_CORE_END_NAMESPACE
