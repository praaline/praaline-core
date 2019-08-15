#include <QString>
#include <QList>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "JSONSerialiserMetadataStructure.h"

PRAALINE_CORE_BEGIN_NAMESPACE

// public static
bool JSONSerialiserMetadataStructure::write(MetadataStructure *structure, const QString &filename)
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
void JSONSerialiserMetadataStructure::write(MetadataStructure *structure, QJsonObject &json)
{
    QJsonObject jsonStructure;
    QJsonArray arraySections;
    QList<CorpusObject::Type> corpusObjectTypes;
    corpusObjectTypes << CorpusObject::Type_Corpus << CorpusObject::Type_Communication << CorpusObject::Type_Speaker
                      << CorpusObject::Type_Recording << CorpusObject::Type_Annotation << CorpusObject::Type_Participation;
    foreach (CorpusObject::Type corpusObjectType, corpusObjectTypes) {
        foreach (MetadataStructureSection *section, structure->sections(corpusObjectType)) {
            QJsonObject jsonSection = writeSection(corpusObjectType, section);
            if (!jsonSection.isEmpty()) arraySections.append(jsonSection);
        }
    }
    jsonStructure.insert("sections", arraySections);
    json.insert("metadataStructure", jsonStructure);
}

// public static
void JSONSerialiserMetadataStructure::writePartial(MetadataStructure *structure, CorpusObject::Type what, QJsonObject &json)
{
    QJsonObject jsonStructure;
    QJsonArray arraySections;
    foreach (MetadataStructureSection *section, structure->sections(what)) {
        QJsonObject jsonSection = writeSection(what, section);
        if (!jsonSection.isEmpty()) arraySections.append(jsonSection);
    }
    jsonStructure.insert("sections", arraySections);
    json.insert("metadataStructure", jsonStructure);
}

// public static
MetadataStructure *JSONSerialiserMetadataStructure::read(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return new MetadataStructure();
    }
    QByteArray data = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject json = jsonDoc.object();
    return read(json);
}

// public static
MetadataStructure *JSONSerialiserMetadataStructure::read(QJsonObject &json)
{
    // Create the new corpus annotation structure specification
    MetadataStructure *structure = new MetadataStructure();
    if (json.contains("metadataStructure") && json["metadataStructure"].isObject()) {
        QJsonObject jsonStructure = json["metadataStructure"].toObject();
        if (jsonStructure.contains("sections") && jsonStructure["sections"].isArray()) {
            QJsonArray arraySections = jsonStructure["sections"].toArray();
            for (int i = 0; i < arraySections.size(); ++i) {
                QJsonObject jsonSection = arraySections[i].toObject();
                if (jsonSection.contains("object") && jsonSection["object"].isString()) {
                    CorpusObject::Type object = CorpusObject::stringToType(jsonSection["object"].toString());
                    MetadataStructureSection *section = readSection(jsonSection);
                    if (section) {
                        section->setParent(structure);
                        structure->addSection(object, section);
                    }
                }
            }
        }
    }
    return structure;
}

// public static
MetadataStructure *JSONSerialiserMetadataStructure::readPartial(CorpusObject::Type what, QJsonObject &json)
{
    // Create the new corpus annotation structure specification
    MetadataStructure *structure = new MetadataStructure();
    if (json.contains("metadataStructure") && json["metadataStructure"].isObject()) {
        QJsonObject jsonStructure = json["metadataStructure"].toObject();
        if (jsonStructure.contains("sections") && jsonStructure["sections"].isArray()) {
            QJsonArray arraySections = jsonStructure["sections"].toArray();
            for (int i = 0; i < arraySections.size(); ++i) {
                QJsonObject jsonSection = arraySections[i].toObject();
                if (jsonSection.contains("object") && jsonSection["object"].isString()) {
                    CorpusObject::Type object = CorpusObject::stringToType(jsonSection["object"].toString());
                    // PARTIAL READ: if the section is about a different type of object, ignore
                    if (object == what) {
                        MetadataStructureSection *section = readSection(jsonSection);
                        if (section) {
                            section->setParent(structure);
                            structure->addSection(object, section);
                        }
                    }
                }
            }
        }
    }
    return structure;
}

// private static
QJsonObject JSONSerialiserMetadataStructure::writeSection(CorpusObject::Type what, MetadataStructureSection *section)
{
    QJsonObject json;
    if (!section) return json;
    json.insert("object", QJsonValue(CorpusObject::typeToString(what)));
    json.insert("id", QJsonValue(section->ID()));
    json.insert("name", QJsonValue(section->name()));
    json.insert("description", QJsonValue(section->description()));
    QJsonArray arrayAttributes;
    foreach (MetadataStructureAttribute *attribute, section->attributes()) {
        QJsonObject jsonAttribute = writeAttribute(attribute);
        if (!jsonAttribute.isEmpty()) arrayAttributes.append(jsonAttribute);
    }
    json.insert("attributes", arrayAttributes);
    return json;
}

// private static
MetadataStructureSection *JSONSerialiserMetadataStructure::readSection(QJsonObject &json)
{
    // Create the new corpus metadata section specification
    MetadataStructureSection *section = new MetadataStructureSection();
    if (json.contains("id") && json["id"].isString())
        section->setID(json["id"].toString());
    if (json.contains("name") && json["name"].isString())
        section->setName(json["name"].toString());
    if (json.contains("description") && json["description"].isString())
        section->setDescription(json["description"].toString());
    if (json.contains("attributes") && json["attributes"].isArray()) {
        QJsonArray arrayAttributes = json["attributes"].toArray();
        for (int i = 0; i < arrayAttributes.size(); ++i) {
            QJsonObject jsonAttribute = arrayAttributes[i].toObject();
            MetadataStructureAttribute *attribute = readAttribute(jsonAttribute);
            if (attribute) {
                attribute->setParent(section);
                section->addAttribute(attribute);
            }
        }
    }
    return section;
}

// private static
QJsonObject JSONSerialiserMetadataStructure::writeAttribute(MetadataStructureAttribute *attribute)
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
    return json;
}

// private static
MetadataStructureAttribute *JSONSerialiserMetadataStructure::readAttribute(QJsonObject &json)
{
    // Create the new corpus metadata attribute
    MetadataStructureAttribute *attribute = new MetadataStructureAttribute();
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
    return attribute;
}

PRAALINE_CORE_END_NAMESPACE
