#include <QString>
#include <QList>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "serialisers/json/JSONSerialiserAnnotationStructure.h"

PRAALINE_CORE_BEGIN_NAMESPACE

JSONSerialiserAnnotationStructure::JSONSerialiserAnnotationStructure()
{
}

JSONSerialiserAnnotationStructure::~JSONSerialiserAnnotationStructure()
{
}

// public static
bool JSONSerialiserAnnotationStructure::write(AnnotationStructure *structure, const QString &filename)
{
    // Open file for writing
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    // Create JSON object containing data
    QJsonObject json;
    write(structure, json);
    // Write out JSON document
    QJsonDocument jsonDoc(json);
    file.write(jsonDoc.toJson(QJsonDocument::Compact));
    return true;
}

// public static
void JSONSerialiserAnnotationStructure::write(AnnotationStructure *structure, QJsonObject &json)
{
    QJsonObject jsonStructure;
    QJsonArray arrayLevels;
    foreach (AnnotationStructureLevel *level, structure->levels()) {
        QJsonObject jsonLevel = writeLevel(level);
        if (!jsonLevel.isEmpty()) arrayLevels.append(jsonLevel);
    }
    jsonStructure.insert("levels", arrayLevels);
    json.insert("annotationStructure", jsonStructure);
}

// public static
AnnotationStructure *JSONSerialiserAnnotationStructure::read(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return new AnnotationStructure();
    }
    QByteArray data = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject json = jsonDoc.object();
    return read(json);
}

// public static
AnnotationStructure *JSONSerialiserAnnotationStructure::read(QJsonObject &json)
{
    // Create the new corpus annotation structure specification
    AnnotationStructure *structure = new AnnotationStructure();
    if (json.contains("annotationStructure") && json["annotationStructure"].isObject()) {
        QJsonObject jsonStructure = json["annotationStructure"].toObject();
        if (jsonStructure.contains("levels") && jsonStructure["levels"].isArray()) {
            QJsonArray arrayLevels = jsonStructure["levels"].toArray();
            for (int i = 0; i < arrayLevels.size(); ++i) {
                QJsonObject jsonLevel = arrayLevels[i].toObject();
                AnnotationStructureLevel *level = readLevel(jsonLevel);
                if (level) {
                    level->setParent(structure);
                    structure->addLevel(level);
                }
            }
        }
    }
    return structure;
}

// private static
QJsonObject JSONSerialiserAnnotationStructure::writeLevel(AnnotationStructureLevel *level)
{
    QJsonObject json;
    if (!level) return json;
    json.insert("id", QJsonValue(level->ID()));
    json.insert("levelType", QJsonValue(convertLevelTypeToString(level->levelType())));
    json.insert("parentLevelID", QJsonValue(level->parentLevelID()));
    json.insert("name", QJsonValue(level->name()));
    json.insert("description", QJsonValue(level->description()));
    json.insert("datatype", QJsonValue(level->datatypeString()));
    json.insert("datalength", QJsonValue(QString::number(level->datatypePrecision())));
    json.insert("indexed", (level->indexed()) ? true : false);
    json.insert("nameValueList", QJsonValue(level->nameValueList()));
    QJsonArray arrayAttributes;
    foreach (AnnotationStructureAttribute *attribute, level->attributes()) {
        QJsonObject jsonAttribute = writeAttribute(attribute);
        if (!jsonAttribute.isEmpty()) arrayAttributes.append(jsonAttribute);
    }
    json.insert("attributes", arrayAttributes);
    return json;
}

// private static
AnnotationStructureLevel *JSONSerialiserAnnotationStructure::readLevel(QJsonObject &json)
{
    // Create the new corpus annotation level specification
    AnnotationStructureLevel *level = new AnnotationStructureLevel();
    if (json.contains("id") && json["id"].isString())
        level->setID(json["id"].toString());
    if (json.contains("levelType") && json["levelType"].isString())
        level->setLevelType(convertStringToLevelType(json["levelType"].toString()));
    if (json.contains("parentLevelID") && json["parentLevelID"].isString())
        level->setParentLevelID(json["parentLevelID"].toString());
    if (json.contains("name") && json["name"].isString())
        level->setName(json["name"].toString());
    if (json.contains("description") && json["description"].isString())
        level->setDescription(json["description"].toString());
    if (json.contains("datatype") && json["datatype"].isString())
        level->setDatatype(DataType(json["datatype"].toString()));
    if (json.contains("datalength") && json["datalength"].isString())
        level->setDatatype(DataType(level->datatype().base(), json["datalength"].toString().toUInt()));
    if (json.contains("indexed") && json["indexed"].isBool())
        level->setIndexed(json["indexed"].toBool());
    if (json.contains("nameValueList") && json["nameValueList"].isString())
        level->setNameValueList(json["nameValueList"].toString());
    if (json.contains("attributes") && json["attributes"].isArray()) {
        QJsonArray arrayAttributes = json["attributes"].toArray();
        for (int i = 0; i < arrayAttributes.size(); ++i) {
            QJsonObject jsonAttribute = arrayAttributes[i].toObject();
            AnnotationStructureAttribute *attribute = readAttribute(jsonAttribute);
            if (attribute) {
                attribute->setParent(level);
                level->addAttribute(attribute);
            }
        }
    }
    return level;
}

// private static
QJsonObject JSONSerialiserAnnotationStructure::writeAttribute(AnnotationStructureAttribute *attribute)
{
    QJsonObject json;
    if (!attribute) return json;
    json.insert("id", QJsonValue(attribute->ID()));
    json.insert("name", QJsonValue(attribute->name()));
    json.insert("description", QJsonValue(attribute->description()));
    json.insert("datatype", QJsonValue(attribute->datatypeString()));
    json.insert("datalength", QJsonValue(QString::number(attribute->datatypePrecision())));
    json.insert("indexed", (attribute->indexed()) ? true : false);
    json.insert("nameValueList", QJsonValue(attribute->nameValueList()));
    json.insert("statLevelOfMeasurement", QJsonValue(attribute->statLevelOfMeasurement()));
    return json;
}

// private static
AnnotationStructureAttribute *JSONSerialiserAnnotationStructure::readAttribute(QJsonObject &json)
{
    // Create the new corpus annotation attribute specification
    AnnotationStructureAttribute *attribute = new AnnotationStructureAttribute();
    if (json.contains("id") && json["id"].isString())
        attribute->setID(json["id"].toString());
    if (json.contains("name") && json["name"].isString())
        attribute->setName(json["name"].toString());
    if (json.contains("description") && json["description"].isString())
        attribute->setDescription(json["description"].toString());
    if (json.contains("datatype") && json["datatype"].isString())
        attribute->setDatatype(DataType(json["datatype"].toString()));
    if (json.contains("datalength") && json["datalength"].isString())
        attribute->setDatatype(DataType(attribute->datatype().base(), json["datalength"].toString().toUInt()));
    if (json.contains("indexed") && json["indexed"].isBool())
        attribute->setIndexed(json["indexed"].toBool());
    if (json.contains("nameValueList") && json["nameValueList"].isString())
        attribute->setNameValueList(json["nameValueList"].toString());
    if (json.contains("statLevelOfMeasurement") && json["statLevelOfMeasurement"].isString())
        attribute->setStatLevelOfMeasurement(json["statLevelOfMeasurement"].toString());
    return attribute;
}

PRAALINE_CORE_END_NAMESPACE
