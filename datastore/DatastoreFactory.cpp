#include "DatastoreFactory.h"
#include "AnnotationDatastore.h"
#include "MetadataDatastore.h"
#include "DatastoreInfo.h"
#include "CorpusRepository.h"
#include "structure/AnnotationStructure.h"
#include "structure/MetadataStructure.h"
#include "datastore/SQLAnnotationDatastore.h"
#include "datastore/SQLMetadataDatastore.h"

PRAALINE_CORE_BEGIN_NAMESPACE

// static
AnnotationDatastore *DatastoreFactory::getAnnotationDatastore(const DatastoreInfo &dsi, AnnotationStructure *structure, CorpusRepository *repository)
{
    if (dsi.type == DatastoreInfo::SQL) {
        return new SQLAnnotationDatastore(structure, repository, repository);
    }
    return nullptr;
}

// static
MetadataDatastore *DatastoreFactory::getMetadataDatastore(const DatastoreInfo &dsi, MetadataStructure *structure, CorpusRepository *repository)
{
    if (dsi.type == DatastoreInfo::SQL) {
        return new SQLMetadataDatastore(structure, repository, repository);
    }
    return nullptr;
}

PRAALINE_CORE_END_NAMESPACE


