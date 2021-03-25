#include <QObject>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "PraalineCore/Serialisers/XML/XMLSerialiserNameValueList.h"

PRAALINE_CORE_BEGIN_NAMESPACE

QString XMLSerialiserNameValueList::xmlElementName_NameValueList("NameValueList");

XMLSerialiserNameValueList::XMLSerialiserNameValueList()
{
}

XMLSerialiserNameValueList::~XMLSerialiserNameValueList()
{
}

// private static
NameValueList *XMLSerialiserNameValueList::readNameValueList(QXmlStreamReader &xml)
{
    // Check that we're really reading a bookmark
    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == xmlElementName_NameValueList) {
        return nullptr;
    }
    NameValueList *nvl = new NameValueList();
    QXmlStreamAttributes xmlAttributes = xml.attributes();
//    if (xmlAttributes.hasAttribute("id"))               bookmark->setID(xmlAttributes.value("id").toString());
//    if (xmlAttributes.hasAttribute("corpusID"))         bookmark->setCorpusID(xmlAttributes.value("corpusID").toString());
//    if (xmlAttributes.hasAttribute("communicationID"))  bookmark->setCommunicationID(xmlAttributes.value("communicationID").toString());
//    if (xmlAttributes.hasAttribute("annotationID"))     bookmark->setAnnotationID(xmlAttributes.value("annotationID").toString());
//    if (xmlAttributes.hasAttribute("time"))             bookmark->setTime(RealTime::fromNanoseconds((xmlAttributes.value("time").toLongLong())));
//    if (xmlAttributes.hasAttribute("timeStart"))        bookmark->setTimeStart(RealTime::fromNanoseconds((xmlAttributes.value("timeStart").toLongLong())));
//    if (xmlAttributes.hasAttribute("timeEnd"))          bookmark->setTimeEnd(RealTime::fromNanoseconds((xmlAttributes.value("timeEnd").toLongLong())));
//    if (xmlAttributes.hasAttribute("name"))             bookmark->setName(xmlAttributes.value("name").toString());
//    if (xmlAttributes.hasAttribute("notes"))            bookmark->setNotes(xmlAttributes.value("notes").toString());
    return nvl;
}

// private static
bool XMLSerialiserNameValueList::writeNameValueList(NameValueList *nvl, QXmlStreamWriter &xml)
{
    if (!nvl) return false;
    xml.writeStartElement(xmlElementName_NameValueList);
//    xml.writeAttribute("corpusID", bookmark->corpusID());
//    xml.writeAttribute("communicationID", bookmark->communicationID());
//    xml.writeAttribute("annotationID", bookmark->annotationID());
//    if (bookmark->duration() == RealTime::zeroTime) {
//        xml.writeAttribute("time", QString::number(bookmark->time().toNanoseconds()));
//    } else {
//        xml.writeAttribute("timeStart", QString::number(bookmark->timeStart().toNanoseconds()));
//        xml.writeAttribute("timeEnd", QString::number(bookmark->timeEnd().toNanoseconds()));
//    }
//    xml.writeAttribute("name", bookmark->name());
//    xml.writeAttribute("notes", bookmark->notes());
    xml.writeEndElement(); // NameValueList
    return true;
}

// static
bool XMLSerialiserNameValueList::saveNameValueLists(const QList<NameValueList *> &NVLs, QXmlStreamWriter &xml)
{
    xml.writeStartElement("NameValueLists");
    foreach (NameValueList *nvl, NVLs) {
        if (!nvl) continue;
        writeNameValueList(nvl, xml);
    }
    xml.writeEndElement(); // NameValueLists
    return true;
}

// static
bool XMLSerialiserNameValueList::loadNameValueLists(QList<NameValueList *> &NVLs, QXmlStreamReader &xml)
{
    NVLs.clear();
    while (!xml.atEnd() && !xml.hasError()) {
        // If token is StartElement, we'll see if we can read it.
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == QLatin1String("NameValueLists")) {
            xml.readNext();
            while (!xml.atEnd() && !xml.hasError() &&
                   !(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QLatin1String("NameValueLists"))) {
                if (xml.tokenType() == QXmlStreamReader::StartElement) {
                    if (xml.name() == QLatin1String("NameValueList")) {
                        NameValueList *nvl = readNameValueList(xml);
                        if (nvl) NVLs << nvl;
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
bool XMLSerialiserNameValueList::saveNameValueLists(const QList<NameValueList *> &NVLs, const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    bool ret = saveNameValueLists(NVLs, xml);
    xml.writeEndDocument();
    file.close();
    return ret;
}

// static
bool XMLSerialiserNameValueList::loadNameValueLists(QList<NameValueList *> &NVLs, const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
    QXmlStreamReader xml(&file);
    bool ret = loadNameValueLists(NVLs, xml);
    xml.clear();
    file.close();
    return ret;
}

PRAALINE_CORE_END_NAMESPACE
