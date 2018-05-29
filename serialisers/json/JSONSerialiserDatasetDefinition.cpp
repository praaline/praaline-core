#include <QObject>
#include <QPointer>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "JSONSerialiserDatasetDefinition.h"

namespace Praaline {
namespace Core {

JSONSerialiserDatasetDefinition::JSONSerialiserDatasetDefinition()
{
}

JSONSerialiserDatasetDefinition::~JSONSerialiserDatasetDefinition()
{
}

// public static
bool JSONSerialiserDatasetDefinition::saveDatasetDefinition(const DatasetDefinition &definition, const QString &filename)
{
    return false;
}

// public static
bool JSONSerialiserDatasetDefinition::saveDatasetDefinition(const DatasetDefinition &definition, QJsonObject &json)
{
    return false;
}

// public static
bool JSONSerialiserDatasetDefinition::loadDatasetDefinition(DatasetDefinition &definition, const QString &filename)
{
    return false;
}

// public static
bool JSONSerialiserDatasetDefinition::loadDatasetDefinition(DatasetDefinition &definition, QJsonObject &json)
{
    return false;
}

} // namespace Core
} // namespace Praaline
