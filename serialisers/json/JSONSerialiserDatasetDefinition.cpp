#include <QObject>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "JSONSerialiserDatasetDefinition.h"

PRAALINE_CORE_BEGIN_NAMESPACE

JSONSerialiserDatasetDefinition::JSONSerialiserDatasetDefinition()
{
}

JSONSerialiserDatasetDefinition::~JSONSerialiserDatasetDefinition()
{
}

// public static
bool JSONSerialiserDatasetDefinition::saveDatasetDefinition(const DatasetDefinition &definition, const QString &filename)
{
    Q_UNUSED(definition)
    Q_UNUSED(filename)
    return false;
}

// public static
bool JSONSerialiserDatasetDefinition::saveDatasetDefinition(const DatasetDefinition &definition, QJsonObject &json)
{
    Q_UNUSED(definition)
    Q_UNUSED(json)
    return false;
}

// public static
bool JSONSerialiserDatasetDefinition::loadDatasetDefinition(DatasetDefinition &definition, const QString &filename)
{
    Q_UNUSED(definition)
    Q_UNUSED(filename)
    return false;
}

// public static
bool JSONSerialiserDatasetDefinition::loadDatasetDefinition(DatasetDefinition &definition, QJsonObject &json)
{
    Q_UNUSED(definition)
    Q_UNUSED(json)
    return false;
}

PRAALINE_CORE_END_NAMESPACE
