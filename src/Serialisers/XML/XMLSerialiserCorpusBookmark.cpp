#include <QObject>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "PraalineCore/Serialisers/XML/XMLSerialiserCorpusBookmark.h"

PRAALINE_CORE_BEGIN_NAMESPACE

QString XMLSerialiserCorpusBookmark::xmlElementName_CorpusBookmark("CorpusBookmark");

XMLSerialiserCorpusBookmark::XMLSerialiserCorpusBookmark()
{
}

XMLSerialiserCorpusBookmark::~XMLSerialiserCorpusBookmark()
{
}

// private static
CorpusBookmark *XMLSerialiserCorpusBookmark::readBookmark(QXmlStreamReader &xml)
{
    // Check that we're really reading a bookmark
    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == xmlElementName_CorpusBookmark) {
        return nullptr;
    }
    CorpusBookmark *bookmark = new CorpusBookmark();
    QXmlStreamAttributes xmlAttributes = xml.attributes();
    if (xmlAttributes.hasAttribute("id"))               bookmark->setID(xmlAttributes.value("id").toString());
    if (xmlAttributes.hasAttribute("corpusID"))         bookmark->setCorpusID(xmlAttributes.value("corpusID").toString());
    if (xmlAttributes.hasAttribute("communicationID"))  bookmark->setCommunicationID(xmlAttributes.value("communicationID").toString());
    if (xmlAttributes.hasAttribute("annotationID"))     bookmark->setAnnotationID(xmlAttributes.value("annotationID").toString());
    if (xmlAttributes.hasAttribute("time"))             bookmark->setTime(RealTime::fromNanoseconds((xmlAttributes.value("time").toLongLong())));
    if (xmlAttributes.hasAttribute("timeStart"))        bookmark->setTimeStart(RealTime::fromNanoseconds((xmlAttributes.value("timeStart").toLongLong())));
    if (xmlAttributes.hasAttribute("timeEnd"))          bookmark->setTimeEnd(RealTime::fromNanoseconds((xmlAttributes.value("timeEnd").toLongLong())));
    if (xmlAttributes.hasAttribute("name"))             bookmark->setName(xmlAttributes.value("name").toString());
    if (xmlAttributes.hasAttribute("notes"))            bookmark->setNotes(xmlAttributes.value("notes").toString());
    return bookmark;
}

// private static
bool XMLSerialiserCorpusBookmark::writeBookmark(CorpusBookmark *bookmark, QXmlStreamWriter &xml)
{
    if (!bookmark) return false;
    xml.writeStartElement(xmlElementName_CorpusBookmark);
    xml.writeAttribute("corpusID", bookmark->corpusID());
    xml.writeAttribute("communicationID", bookmark->communicationID());
    xml.writeAttribute("annotationID", bookmark->annotationID());
    if (bookmark->duration() == RealTime::zeroTime) {
        xml.writeAttribute("time", QString::number(bookmark->time().toNanoseconds()));
    } else {
        xml.writeAttribute("timeStart", QString::number(bookmark->timeStart().toNanoseconds()));
        xml.writeAttribute("timeEnd", QString::number(bookmark->timeEnd().toNanoseconds()));
    }
    xml.writeAttribute("name", bookmark->name());
    xml.writeAttribute("notes", bookmark->notes());
    xml.writeEndElement(); // CorpusBookmark
    return true;
}

// static
bool XMLSerialiserCorpusBookmark::saveCorpusBookmarks(const QList<CorpusBookmark *> &list, QXmlStreamWriter &xml)
{
    xml.writeStartElement("CorpusBookmarks");
    foreach (CorpusBookmark *bookmark, list) {
        if (!bookmark) continue;
        writeBookmark(bookmark, xml);
    }
    xml.writeEndElement(); // CorpusBookmarks
    return true;
}

// static
bool XMLSerialiserCorpusBookmark::loadCorpusBookmarks(QList<CorpusBookmark *> &list, QXmlStreamReader &xml)
{
    list.clear();
    while (!xml.atEnd() && !xml.hasError()) {
        // If token is StartElement, we'll see if we can read it.
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == QLatin1String("CorpusBookmarks")) {
            xml.readNext();
            while (!xml.atEnd() && !xml.hasError() &&
                   !(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QLatin1String("CorpusBookmarks"))) {
                if (xml.tokenType() == QXmlStreamReader::StartElement) {
                    if (xml.name() == QLatin1String("CorpusBookmark")) {
                        CorpusBookmark *bookmark = readBookmark(xml);
                        if (bookmark) list << bookmark;
                    }
                }
                xml.readNext();
            }
        }
        xml.readNext(); // next element
    }
    // Error handling
    if(xml.hasError()) return false;
    return true;
}

// static
bool XMLSerialiserCorpusBookmark::saveCorpusBookmarks(const QList<CorpusBookmark *> &list, const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    bool ret = saveCorpusBookmarks(list, xml);
    xml.writeEndDocument();
    file.close();
    return ret;
}

// static
bool XMLSerialiserCorpusBookmark::loadCorpusBookmarks(QList<CorpusBookmark *> &list, const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
    QXmlStreamReader xml(&file);
    bool ret = loadCorpusBookmarks(list, xml);
    xml.clear();
    file.close();
    return ret;
}

PRAALINE_CORE_END_NAMESPACE
