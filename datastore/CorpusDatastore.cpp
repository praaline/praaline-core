#include "corpus/CorpusObject.h"
#include "CorpusRepository.h"
#include "CorpusDatastore.h"

PRAALINE_CORE_BEGIN_NAMESPACE

CorpusDatastore::CorpusDatastore(CorpusRepository *repository, QObject *parent) :
    QObject(parent), m_repository(repository)
{
}


void CorpusDatastore::setRepository(CorpusObject *object)
{
    object->m_repository = this->m_repository;
}

PRAALINE_CORE_END_NAMESPACE
