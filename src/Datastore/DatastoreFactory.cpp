#include "PraalineCore/Datastore/DatastoreFactory.h"
#include "PraalineCore/Datastore/AnnotationDatastore.h"
#include "PraalineCore/Datastore/MetadataDatastore.h"
#include "PraalineCore/Datastore/DatastoreInfo.h"
#include "PraalineCore/Datastore/CorpusRepository.h"
#include "PraalineCore/Structure/AnnotationStructure.h"
#include "PraalineCore/Structure/MetadataStructure.h"

#include "Datastore/SQLAnnotationDatastore.h"
#include "Datastore/SQLMetadataDatastore.h"

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


