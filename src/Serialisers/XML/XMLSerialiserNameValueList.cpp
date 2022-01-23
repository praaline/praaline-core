#include <QObject>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "PraalineCore/Structure/NameValueList.h"
#include "PraalineCore/Serialisers/XML/XMLSerialiserNameValueList.h"

PRAALINE_CORE_BEGIN_NAMESPACE

QString XMLSerialiserNameValueList::xmlElementName_NameValueList("NameValueList");
QString XMLSerialiserNameValueList::xmlElementName_NameValueListItem("NameValueListItem");

XMLSerialiserNameValueList::XMLSerialiserNameValueList()
{
}

XMLSerialiserNameValueList::~XMLSerialiserNameValueList()
{
}

// private static
NameValueList *XMLSerialiserNameValueList::readNameValueList(QXmlStreamReader &xml)
{
    // Check that we're really reading a name-value list
    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == xmlElementName_NameValueList) {
        return nullptr;
    }
    NameValueList *nvl = new NameValueList();
    QXmlStreamAttributes xmlAttributes = xml.attributes();
    if (xmlAttributes.hasAttribute("id"))               nvl->setID(xmlAttributes.value("id").toString());
    if (xmlAttributes.hasAttribute("name"))             nvl->setName(xmlAttributes.value("name").toString());
    if (xmlAttributes.hasAttribute("description"))      nvl->setDescription(xmlAttributes.value("description").toString());
    if (xmlAttributes.hasAttribute("datatype")) {
        nvl->setDatatype(DataType(xmlAttributes.value("datatype").toString()));
    }
    if (xmlAttributes.hasAttribute("datalength")) {
        nvl->setDatatype(DataType(nvl->datatype().base(), xmlAttributes.value("datalength").toInt()));
    }
    xml.readNext(); // next element
    // Read data items (until reaching the end of this name-value list
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == xmlElementName_NameValueList)) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (xml.name() == xmlElementName_NameValueListItem) {
                QXmlStreamAttributes xmlAttributes_Item = xml.attributes();
                if (xmlAttributes_Item.hasAttribute("value") && xmlAttributes_Item.hasAttribute("displayString")) {
                    QVariant value = xmlAttributes_Item.value("value").toString(); // FIX ME: use datatype
                    QString displayString = xmlAttributes_Item.value("displayString").toString();
                    nvl->append(displayString, value);
                }
            }
        }
        xml.readNext(); // next element
    }
    return nvl;
}

// private static
bool XMLSerialiserNameValueList::writeNameValueList(NameValueList *nvl, QXmlStreamWriter &xml)
{
    if (!nvl) return false;
    xml.writeStartElement(xmlElementName_NameValueList);
    xml.writeAttribute("id", nvl->ID());
    xml.writeAttribute("name", nvl->name());
    xml.writeAttribute("description", nvl->description());
    xml.writeAttribute("datatype", nvl->datatypeString());
    xml.writeAttribute("datalength", QString::number(nvl->datatypePrecision()));
        for (int i = 0; i < nvl->count(); i++) {
        xml.writeStartElement(xmlElementName_NameValueListItem);
        xml.writeAttribute("value", nvl->value(i).toString());
        xml.writeAttribute("displayString", nvl->displayString(i));
        xml.writeEndElement(); // NameValueListItem
    }
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
