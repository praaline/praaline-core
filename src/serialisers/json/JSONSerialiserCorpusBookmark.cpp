#include <QObject>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "serialisers/json/JSONSerialiserCorpusBookmark.h"

PRAALINE_CORE_BEGIN_NAMESPACE

JSONSerialiserCorpusBookmark::JSONSerialiserCorpusBookmark()
{
}

JSONSerialiserCorpusBookmark::~JSONSerialiserCorpusBookmark()
{
}

// public static
bool JSONSerialiserCorpusBookmark::saveCorpusBookmarks(const QList<CorpusBookmark *> &list, const QString &filename)
{
    // Open file for writing
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    // Create JSON object containing data
    QJsonObject json;
    saveCorpusBookmarks(list, json);
    // Write out JSON document
    QJsonDocument jsonDoc(json);
    file.write(jsonDoc.toJson(QJsonDocument::Compact));
    return true;
}

// public static
bool JSONSerialiserCorpusBookmark::saveCorpusBookmarks(const QList<CorpusBookmark *> &list, QJsonObject &json)
{
    QJsonObject jsonBookmarks;
    QJsonArray arrayBookmarks;
    foreach (CorpusBookmark * bookmark, list) {
        QJsonObject jsonBookmark = writeBookmark(bookmark);
        if (!jsonBookmark.isEmpty()) arrayBookmarks.append(jsonBookmark);
    }
    jsonBookmarks.insert("bookmarks", arrayBookmarks);
    json.insert("corpusBookmarks", jsonBookmarks);
    return true;
}

// public static
bool JSONSerialiserCorpusBookmark::loadCorpusBookmarks(QList<CorpusBookmark *> &list, const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    QByteArray data = file.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject json = jsonDoc.object();
    return loadCorpusBookmarks(list, json);
}

// public static
bool JSONSerialiserCorpusBookmark::loadCorpusBookmarks(QList<CorpusBookmark *> &list, QJsonObject &json)
{
    if (json.contains("corpusBookmarks") && json["corpusBookmarks"].isObject()) {
        QJsonObject jsonBookmarks = json["corpusBookmarks"].toObject();
        if (jsonBookmarks.contains("bookmarks") && jsonBookmarks["bookmarks"].isArray()) {
            QJsonArray arrayBookmarks = jsonBookmarks["bookmarks"].toArray();
            for (int i = 0; i < arrayBookmarks.size(); ++i) {
                QJsonObject jsonBookmark = arrayBookmarks[i].toObject();
                CorpusBookmark *bookmark = readBookmark(jsonBookmark);
                if (bookmark) list.append(bookmark);
            }
        }
        return true;
    } // else
    return false;
}

// private static
CorpusBookmark *JSONSerialiserCorpusBookmark::readBookmark(QJsonObject &json)
{
    CorpusBookmark *bookmark = new CorpusBookmark();
    if (json.contains("id") && json["id"].isString())
        bookmark->setID(json["id"].toString());
    if (json.contains("corpusID") && json["corpusID"].isString())
        bookmark->setCorpusID(json["corpusID"].toString());
    if (json.contains("communicationID") && json["communicationID"].isString())
        bookmark->setCommunicationID(json["communicationID"].toString());
    if (json.contains("annotationID") && json["annotationID"].isString())
        bookmark->setAnnotationID(json["annotationID"].toString());
    if (json.contains("time") && json["time"].isString())
        bookmark->setTime(RealTime::fromNanoseconds(json["annotationID"].toString().toLongLong()));
    if (json.contains("timeStart") && json["timeStart"].isString())
        bookmark->setTimeStart(RealTime::fromNanoseconds(json["timeStart"].toString().toLongLong()));
    if (json.contains("timeEnd") && json["timeEnd"].isString())
        bookmark->setTimeEnd(RealTime::fromNanoseconds(json["timeEnd"].toString().toLongLong()));
    if (json.contains("name") && json["name"].isString())
        bookmark->setName(json["name"].toString());
    if (json.contains("notes") && json["notes"].isString())
        bookmark->setNotes(json["notes"].toString());
    return bookmark;
}

// private static
QJsonObject JSONSerialiserCorpusBookmark::writeBookmark(CorpusBookmark *bookmark)
{
    QJsonObject json;
    if (!bookmark) return json;
    json.insert("corpusID", QJsonValue(bookmark->corpusID()));
    json.insert("communicationID", QJsonValue(bookmark->communicationID()));
    json.insert("annotationID", QJsonValue(bookmark->annotationID()));
    if (bookmark->duration() == RealTime::zeroTime) {
        json.insert("time", QJsonValue(QString::number(bookmark->time().toNanoseconds())));
    } else {
        json.insert("timeStart", QJsonValue(QString::number(bookmark->timeStart().toNanoseconds())));
        json.insert("timeEnd", QJsonValue(QString::number(bookmark->timeEnd().toNanoseconds())));
    }
    json.insert("name", QJsonValue(bookmark->name()));
    json.insert("notes", QJsonValue(bookmark->notes()));
    return json;
}

PRAALINE_CORE_END_NAMESPACE
