#include "datastore/DatastoreFactory.h"
#include "datastore/AnnotationDatastore.h"
#include "datastore/MetadataDatastore.h"
#include "datastore/DatastoreInfo.h"
#include "datastore/CorpusRepository.h"
#include "datastore/SQLAnnotationDatastore.h"
#include "datastore/SQLMetadataDatastore.h"
#include "structure/AnnotationStructure.h"
#include "structure/MetadataStructure.h"

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


