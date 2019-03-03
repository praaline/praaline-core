#include "DatasetDefinition.h"

namespace Praaline {
namespace Core {

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

} // namespace Core
} // namespace Praaline
