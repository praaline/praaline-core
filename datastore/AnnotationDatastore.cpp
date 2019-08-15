#include "AnnotationDatastore.h"

PRAALINE_CORE_BEGIN_NAMESPACE

AnnotationDatastore::AnnotationDatastore(CorpusRepository *repository, QObject *parent) :
    CorpusDatastore(repository, parent)
{
}

AnnotationDatastore::~AnnotationDatastore()
{
}

PRAALINE_CORE_END_NAMESPACE
