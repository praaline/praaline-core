#include "corpus/CorpusObject.h"
#include "datastore/CorpusRepository.h"
#include "datastore/CorpusDatastore.h"

PRAALINE_CORE_BEGIN_NAMESPACE

CorpusDatastore::CorpusDatastore(CorpusRepository *repository, QObject *parent) :
    QObject(parent), m_repository(repository)
{
}

CorpusDatastore::~CorpusDatastore()
{
}

void CorpusDatastore::setRepository(CorpusObject *object)
{
    object->m_repository = this->m_repository;
}

PRAALINE_CORE_END_NAMESPACE
