#include "DatasetDefinition.h"

PRAALINE_CORE_BEGIN_NAMESPACE

struct DatasetDefinitionData {
    QString minimalLevelID;

};

DatasetDefinition::DatasetDefinition() :
    d(new DatasetDefinitionData())
{
}

DatasetDefinition::~DatasetDefinition()
{
}

PRAALINE_CORE_END_NAMESPACE
