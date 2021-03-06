#include <QObject>
#include <QString>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "PraalineCore/Corpus/Corpus.h"
#include "PraalineCore/Corpus/CorpusObject.h"
#include "PraalineCore/Corpus/CorpusSpeaker.h"
#include "PraalineCore/Datastore/CorpusRepository.h"
#include "PraalineCore/Datastore/MetadataDatastore.h"

PRAALINE_CORE_BEGIN_NAMESPACE

CorpusSpeaker::CorpusSpeaker(CorpusRepository *repository, QObject *parent) :
    CorpusObject(repository, parent)
{
}

CorpusSpeaker::CorpusSpeaker(const QString &ID, CorpusRepository *repository, QObject *parent) :
    CorpusObject(ID, repository, parent)
{
}

CorpusSpeaker::CorpusSpeaker(CorpusSpeaker *other, QObject *parent) :
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

Corpus *CorpusSpeaker::corpus() const
{
    return qobject_cast<Corpus *>(this->parent());
}

void CorpusSpeaker::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;
        m_isDirty = true;
    }
}

bool CorpusSpeaker::save() {
    if (!m_repository) return false;
    if (!m_repository->metadata()) return false;
    return m_repository->metadata()->saveSpeakers(QList<CorpusSpeaker *>() << this);
}

PRAALINE_CORE_END_NAMESPACE
