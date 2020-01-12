#include "datastore/MetadataDatastore.h"

PRAALINE_CORE_BEGIN_NAMESPACE

MetadataDatastore::MetadataDatastore(CorpusRepository *repository, QObject *parent) :
    CorpusDatastore(repository, parent)
{
}

MetadataDatastore::~MetadataDatastore()
{
}

PRAALINE_CORE_END_NAMESPACE
