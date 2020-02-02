#include <QObject>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "PraalineCore/Serialisers/JSON/JSONSerialiserQueryDefinition.h"

PRAALINE_CORE_BEGIN_NAMESPACE

JSONSerialiserQueryDefinition::JSONSerialiserQueryDefinition()
{
}

JSONSerialiserQueryDefinition::~JSONSerialiserQueryDefinition()
{
}

// public static
bool JSONSerialiserQueryDefinition::saveQueryDefinition(const QueryDefinition &definition, const QString &filename)
{
    Q_UNUSED(definition)
    Q_UNUSED(filename)
    return false;
}

// public static
bool JSONSerialiserQueryDefinition::saveQueryDefinition(const QueryDefinition &definition, QJsonObject &json)
{
    Q_UNUSED(definition)
    Q_UNUSED(json)
    return false;
}

// public static
bool JSONSerialiserQueryDefinition::loadQueryDefinition(QueryDefinition &definition, const QString &filename)
{
    Q_UNUSED(definition)
    Q_UNUSED(filename)
    return false;
}

// public static
bool JSONSerialiserQueryDefinition::loadQueryDefinition(QueryDefinition &definition, QJsonObject &json)
{
    Q_UNUSED(definition)
    Q_UNUSED(json)
    return false;
}

PRAALINE_CORE_END_NAMESPACE
