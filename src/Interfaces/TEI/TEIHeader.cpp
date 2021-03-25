#include <QDebug>
#include <QXmlStreamReader>
#include "PraalineCore/Interfaces/TEI/TEIHeader.h"

PRAALINE_CORE_BEGIN_NAMESPACE

TEIHeader::TEIHeader()
{
}

// private static
bool TEIHeader::readCatRef(QXmlStreamReader &xml, CatRef &catRef)
{
    // Check that we're really reading a catRef
    if ((xml.tokenType() != QXmlStreamReader::StartElement) || (xml.name() != QLatin1String("catRef"))) {
        return false;
    }
    QXmlStreamAttributes xmlAttributes = xml.attributes();
    if (xmlAttributes.hasAttribute("target"))   catRef.target = xmlAttributes.value("target").toString();
    if (xmlAttributes.hasAttribute("corresp"))  catRef.corresp = xmlAttributes.value("corresp").toString();
    // qDebug() << catRef.target << catRef.corresp;
    return true;
}

bool TEIHeader::readProfileDesc(QXmlStreamReader &xml, ProfileDesc &profileDesc)
{
    // Check that we're really reading a profileDesc
    if ((xml.tokenType() != QXmlStreamReader::StartElement) || (xml.name() != QLatin1String("profileDesc"))) {
        return false;
    }
//    QXmlStreamAttributes xmlAttributes = xml.attributes();
//    if (xmlAttributes.hasAttribute("type"))         section->type = xmlAttributes.value("type").toString();
//    // qDebug() << section->type << section->startTime.toDouble() << section->endTime.toDouble() << section->topicID;
    // textCat
    xml.readNext();
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QLatin1String("profileDesc"))) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (xml.name() == QLatin1String("textClass")) {
                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QLatin1String("textClass"))) {
                    if ((xml.tokenType() == QXmlStreamReader::StartElement) && (xml.name() == QLatin1String("catRef"))) {
                        CatRef catRef;
                        if (readCatRef(xml, catRef)) profileDesc.textClass << catRef;
                    }
                    xml.readNext();
                }
            }
            // else if ... other things in ProfileDesc
        }
        xml.readNext();
    }
    return true;
}


bool TEIHeader::load(const QString &filename, TEIHeader &teiHeader)
{
    bool result(false);
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
    QXmlStreamReader xml(&file);
    while (!xml.atEnd() && !xml.hasError()) {
        // If token is StartElement, we'll see if we can read it.
        if(xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == QLatin1String("profileDesc")) {
            result = readProfileDesc(xml, teiHeader.profileDesc);
        }
        xml.readNext(); // next element
    }
    // Removes any device() or data from the reader and resets its internal state to the initial state.
    xml.clear();
    file.close();
    return result;
}


PRAALINE_CORE_END_NAMESPACE
