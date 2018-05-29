#include <QObject>
#include <QPointer>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "JSONSerialiserQueryDefinition.h"

namespace Praaline {
namespace Core {

JSONSerialiserQueryDefinition::JSONSerialiserQueryDefinition()
{
}

JSONSerialiserQueryDefinition::~JSONSerialiserQueryDefinition()
{
}

// public static
bool JSONSerialiserQueryDefinition::saveQueryDefinition(const QueryDefinition &definition, const QString &filename)
{
    return false;
}

// public static
bool JSONSerialiserQueryDefinition::saveQueryDefinition(const QueryDefinition &definition, QJsonObject &json)
{
    return false;
}

// public static
bool JSONSerialiserQueryDefinition::loadQueryDefinition(QueryDefinition &definition, const QString &filename)
{
    return false;
}

// public static
bool JSONSerialiserQueryDefinition::loadQueryDefinition(QueryDefinition &definition, QJsonObject &json)
{
    return false;
}

} // namespace Core
} // namespace Praaline
