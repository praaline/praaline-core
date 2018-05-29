#include <QObject>
#include <QPointer>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "JSONSerialiserCorpusBookmark.h"

namespace Praaline {
namespace Core {

JSONSerialiserCorpusBookmark::JSONSerialiserCorpusBookmark()
{
}

JSONSerialiserCorpusBookmark::~JSONSerialiserCorpusBookmark()
{
}

// public static
bool JSONSerialiserCorpusBookmark::saveCorpusBookmarks(const QList<QPointer<CorpusBookmark> > &list, const QString &filename)
{
    return false;
}

// public static
bool JSONSerialiserCorpusBookmark::saveCorpusBookmarks(const QList<QPointer<CorpusBookmark> > &list, QJsonObject &json)
{
    return false;
}

// public static
bool JSONSerialiserCorpusBookmark::loadCorpusBookmarks(QList<QPointer<CorpusBookmark> > &list, const QString &filename)
{
    return false;
}

// public static
bool JSONSerialiserCorpusBookmark::loadCorpusBookmarks(QList<QPointer<CorpusBookmark> > &list, QJsonObject &json)
{
    return false;
}

} // namespace Core
} // namespace Praaline
