#include <QObject>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "serialisers/json/JSONSerialiserNameValueList.h"

PRAALINE_CORE_BEGIN_NAMESPACE

JSONSerialiserNameValueList::JSONSerialiserNameValueList()
{
}

JSONSerialiserNameValueList::~JSONSerialiserNameValueList()
{
}

// public static
bool JSONSerialiserNameValueList::saveNameValueLists(const QList<NameValueList *> &NVLs, const QString &filename)
{
    // Open file for writing
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    // Create JSON object containing data
    QJsonObject json;
    saveNameValueLists(NVLs, json);
    // Write out JSON document
    QJsonDocument jsonDoc(json);
    file.write(jsonDoc.toJson(QJsonDocument::Compact));
    return true;
}

// public static
bool JSONSerialiserNameValueList::saveNameValueLists(const QList<NameValueList *> &NVLs, QJsonObject &json)
{
    QJsonObject jsonNameValueLists;
    QJsonArray arrayNameValueLists;
    foreach (NameValueList * nvl, NVLs) {
        QJsonObject jsonNameValueList = writeNameValueList(nvl);
        if (!jsonNameValueList.isEmpty()) arrayNameValueLists.append(jsonNameValueList);
    }
    jsonNameValueLists.insert("lists", arrayNameValueLists);
    json.insert("nameValueLists", jsonNameValueLists);
    return true;
}

// public static
bool JSONSerialiserNameValueList::loadNameValueLists(QList<NameValueList *> &NVLs, const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    QByteArray data = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject json = jsonDoc.object();
    return loadNameValueLists(NVLs, json);
}

// public static
bool JSONSerialiserNameValueList::loadNameValueLists(QList<NameValueList *> &NVLs, QJsonObject &json)
{
    if (json.contains("nameValueLists") && json["nameValueLists"].isObject()) {
        QJsonObject jsonNameValueLists = json["nameValueLists"].toObject();
        if (jsonNameValueLists.contains("lists") && jsonNameValueLists["lists"].isArray()) {
            QJsonArray arrayNameValueLists = jsonNameValueLists["lists"].toArray();
            for (int i = 0; i < arrayNameValueLists.size(); ++i) {
                QJsonObject jsonNameValueList = arrayNameValueLists[i].toObject();
                NameValueList *nvl = readNameValueList(jsonNameValueList);
                if (nvl) NVLs.append(nvl);
            }
        }
        return true;
    } // else
    return false;
}

// private static
NameValueList *JSONSerialiserNameValueList::readNameValueList(QJsonObject &json)
{
    Q_UNUSED(json)
    NameValueList *nvl = new NameValueList();
//    if (json.contains("id") && json["id"].isString())
//        bookmark->setID(json["id"].toString());
//    if (json.contains("corpusID") && json["corpusID"].isString())
//        bookmark->setCorpusID(json["corpusID"].toString());
//    if (json.contains("communicationID") && json["communicationID"].isString())
//        bookmark->setCommunicationID(json["communicationID"].toString());
//    if (json.contains("annotationID") && json["annotationID"].isString())
//        bookmark->setAnnotationID(json["annotationID"].toString());
//    if (json.contains("time") && json["time"].isString())
//        bookmark->setTime(RealTime::fromNanoseconds(json["annotationID"].toString().toLongLong()));
//    if (json.contains("timeStart") && json["timeStart"].isString())
//        bookmark->setTimeStart(RealTime::fromNanoseconds(json["timeStart"].toString().toLongLong()));
//    if (json.contains("timeEnd") && json["timeEnd"].isString())
//        bookmark->setTimeEnd(RealTime::fromNanoseconds(json["timeEnd"].toString().toLongLong()));
//    if (json.contains("name") && json["name"].isString())
//        bookmark->setName(json["name"].toString());
//    if (json.contains("notes") && json["notes"].isString())
//        bookmark->setNotes(json["notes"].toString());
    return nvl;
}

// private static
QJsonObject JSONSerialiserNameValueList::writeNameValueList(NameValueList *nvl)
{
    QJsonObject json;
    if (!nvl) return json;
//    json.insert("corpusID", QJsonValue(bookmark->corpusID()));
//    json.insert("communicationID", QJsonValue(bookmark->communicationID()));
//    json.insert("annotationID", QJsonValue(bookmark->annotationID()));
//    if (bookmark->duration() == RealTime::zeroTime) {
//        json.insert("time", QJsonValue(QString::number(bookmark->time().toNanoseconds())));
//    } else {
//        json.insert("timeStart", QJsonValue(QString::number(bookmark->timeStart().toNanoseconds())));
//        json.insert("timeEnd", QJsonValue(QString::number(bookmark->timeEnd().toNanoseconds())));
//    }
//    json.insert("name", QJsonValue(bookmark->name()));
//    json.insert("notes", QJsonValue(bookmark->notes()));
    return json;
}

PRAALINE_CORE_END_NAMESPACE
