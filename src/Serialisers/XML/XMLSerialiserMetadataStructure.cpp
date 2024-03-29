#include <QFile>
#include <QXmlStreamWriter>

#include "PraalineCore/Serialisers/XML/XMLSerialiserMetadataStructure.h"

PRAALINE_CORE_BEGIN_NAMESPACE

// Initialise static strings
QString XMLSerialiserMetadataStructure::xmlElementName_Structure("MetadataStructure");
QString XMLSerialiserMetadataStructure::xmlElementName_Section("MetadataStructureSection");
QString XMLSerialiserMetadataStructure::xmlElementName_Attribute("MetadataStructureAttribute");

XMLSerialiserMetadataStructure::XMLSerialiserMetadataStructure() {}
XMLSerialiserMetadataStructure::~XMLSerialiserMetadataStructure() {}

// -------------------------------------------------------------------------------------------------------------------------

// static
bool XMLSerialiserMetadataStructure::write(MetadataStructure *structure, const QString &filename)
{
    if (!structure) return false;
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    write(structure, xml);
    xml.writeEndDocument();
    file.close();
    return true;
}

// static
void XMLSerialiserMetadataStructure::write(MetadataStructure *structure, QXmlStreamWriter &xml)
{
    xml.writeStartElement(xmlElementName_Structure);
    QList<CorpusObject::Type> corpusObjectTypes;
    corpusObjectTypes << CorpusObject::Type_Corpus << CorpusObject::Type_Communication << CorpusObject::Type_Speaker
                      << CorpusObject::Type_Recording << CorpusObject::Type_Annotation << CorpusObject::Type_Participation;
    foreach (CorpusObject::Type corpusObjectType, corpusObjectTypes) {
        foreach (MetadataStructureSection *section, structure->sections(corpusObjectType)) {
            writeSection(corpusObjectType, section, xml);
        }
    }
    xml.writeEndElement();
}

// static
void XMLSerialiserMetadataStructure::writePartial(MetadataStructure *structure, CorpusObject::Type what, QXmlStreamWriter &xml)
{
    xml.writeStartElement(xmlElementName_Structure);
    foreach (MetadataStructureSection *section, structure->sections(what)) {
        writeSection(what, section, xml);
    }
    xml.writeEndElement();
}

// static
void XMLSerialiserMetadataStructure::writeSection(CorpusObject::Type what, MetadataStructureSection *section, QXmlStreamWriter &xml)
{
    xml.writeStartElement(xmlElementName_Section);
    xml.writeAttribute("object", CorpusObject::typeToString(what));
    xml.writeAttribute("id", section->ID());
    xml.writeAttribute("name", section->name());
    xml.writeAttribute("description", section->description());
    xml.writeAttribute("itemOrder", QString::number(section->itemOrder()));
    foreach (MetadataStructureAttribute *attribute, section->attributes()) {
        writeAttribute(attribute, xml);
    }
    xml.writeEndElement();
}

// static
void XMLSerialiserMetadataStructure::writeAttribute(MetadataStructureAttribute *attribute, QXmlStreamWriter &xml)
{
    xml.writeStartElement(xmlElementName_Attribute);
    xml.writeAttribute("id", attribute->ID());
    xml.writeAttribute("name", attribute->name());
    xml.writeAttribute("description", attribute->description());
    xml.writeAttribute("datatype", attribute->datatypeString());
    xml.writeAttribute("datalength", QString::number(attribute->datatypePrecision()));
    xml.writeAttribute("indexed", (attribute->indexed()) ? "true" : "false");
    xml.writeAttribute("nameValueList", attribute->nameValueList());
    xml.writeAttribute("mandatory", (attribute->mandatory()) ? "true" : "false");
    xml.writeAttribute("itemOrder", QString::number(attribute->itemOrder()));
    xml.writeEndElement();
}

// -------------------------------------------------------------------------------------------------------------------------

// static
MetadataStructure *XMLSerialiserMetadataStructure::read(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return new MetadataStructure();
    QXmlStreamReader xml(&file);
    while (!xml.atEnd() && !xml.hasError()) {
        // If token is StartElement, we'll see if we can read it.
        if(xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == xmlElementName_Structure) {
            MetadataStructure *structure = read(xml);
            file.close();
            return structure;
        }
        xml.readNext(); // next element
    }
    // Error handling
    if(xml.hasError()) {
        file.close();
        return new MetadataStructure();
    }
    // Removes any device() or data from the reader and resets its internal state to the initial state.
    xml.clear();
    file.close();
    return new MetadataStructure();
}

// static
MetadataStructure *XMLSerialiserMetadataStructure::read(QXmlStreamReader &xml)
{
    // Create the new corpus metadata structure specification
    MetadataStructure *structure = new MetadataStructure();
    // Check that we're really reading a corpus metadata specification
    if (xml.tokenType() != QXmlStreamReader::StartElement || xml.name() != xmlElementName_Structure) {
        return structure; // empty
    }
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == xmlElementName_Structure)) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {
            // parse each item:
            if (xml.name() == xmlElementName_Section) {
                if (xml.attributes().hasAttribute("object")) {
                    QString objectType = xml.attributes().value("object").toString();
                    CorpusObject::Type object = CorpusObject::stringToType(objectType);
                    MetadataStructureSection *section = readSection(xml);
                    if (section) {
                        section->setParent(structure);
                        structure->addSection(object, section);
                    }
                }
            }
        }
        xml.readNext(); // next element
    }
    return structure;
}

// static
MetadataStructure *XMLSerialiserMetadataStructure::readPartial(CorpusObject::Type what, QXmlStreamReader &xml)
{
    // Create the new corpus metadata structure specification
    MetadataStructure *structure = new MetadataStructure();
    // Check that we're really reading a corpus metadata specification
    if (xml.tokenType() != QXmlStreamReader::StartElement || xml.name() != xmlElementName_Structure) {
        return structure; // empty
    }
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == xmlElementName_Structure)) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {
            // parse each item:
            if (xml.name() == xmlElementName_Section) {
                if (xml.attributes().hasAttribute("object")) {
                    QString objectType = xml.attributes().value("object").toString();
                    CorpusObject::Type object = CorpusObject::stringToType(objectType);
                    // PARTIAL READ: if the section is about a different type of object, ignore
                    if (object == what) {
                        MetadataStructureSection *section = readSection(xml);
                        if (section) {
                            section->setParent(structure);
                            structure->addSection(object, section);
                        }
                    }
                }
            }
            // else if (xml.name() == xmlElementName_NameValueList)
        }
        xml.readNext(); // next element
    }
    return structure;
}

// static
MetadataStructureSection *XMLSerialiserMetadataStructure::readSection(QXmlStreamReader &xml)
{
    // Create the new corpus metadata section specification
    MetadataStructureSection *section = new MetadataStructureSection();
    // Check that we're really reading a corpus metadata section specification
    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == xmlElementName_Section) {
        delete section;
        return nullptr;
    }
    // Read the corpus item's attributes
    QXmlStreamAttributes attributes = xml.attributes();
    if (attributes.hasAttribute("id")) {
        section->setID(attributes.value("id").toString());
    }
    if (attributes.hasAttribute("name")) {
        section->setName(attributes.value("name").toString());
    }
    if (attributes.hasAttribute("description")) {
        section->setDescription(attributes.value("description").toString());
    }
    if (attributes.hasAttribute("itemOrder")) {
        section->setItemOrder(attributes.value("itemOrder").toInt());
    }
    xml.readNext(); // next element
    // The order of the elements is not fixed: loop until we hit an EndElement.
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == xmlElementName_Section)) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {
            if (xml.name() == xmlElementName_Attribute) {
                MetadataStructureAttribute *attribute = readAttribute(xml);
                if (attribute) {
                    attribute->setParent(section);
                    section->addAttribute(attribute);
                }
            }
        }
        xml.readNext(); // next element
    }
    return section;
}

// static
MetadataStructureAttribute *XMLSerialiserMetadataStructure::readAttribute(QXmlStreamReader &xml)
{
    // Create the new corpus metadata section specification
    MetadataStructureAttribute *attribute = new MetadataStructureAttribute();
    // Check that we're really reading a corpus metadata section specification
    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == xmlElementName_Attribute) {
        delete attribute;
        return nullptr;
    }
    // Read the corpus item's attributes
    QXmlStreamAttributes xmlAttributes = xml.attributes();
    if (xmlAttributes.hasAttribute("id")) {
        attribute->setID(xmlAttributes.value("id").toString());
    }
    if (xmlAttributes.hasAttribute("name")) {
        attribute->setName(xmlAttributes.value("name").toString());
    }
    if (xmlAttributes.hasAttribute("description")) {
        attribute->setDescription(xmlAttributes.value("description").toString());
    }
    if (xmlAttributes.hasAttribute("datatype")) {
        attribute->setDatatype(DataType(xmlAttributes.value("datatype").toString()));
    }
    if (xmlAttributes.hasAttribute("datalength")) {
        attribute->setDatatype(DataType(attribute->datatype().base(), xmlAttributes.value("datalength").toInt()));
    }
    if (xmlAttributes.hasAttribute("indexed")) {
        if (xmlAttributes.value("indexed").toString() == "true") attribute->setIndexed(true); else attribute->setIndexed(false);
    }
    if (xmlAttributes.hasAttribute("nameValueList")) {
        attribute->setNameValueList(xmlAttributes.value("nameValueList").toString());
    }
    if (xmlAttributes.hasAttribute("mandatory")) {
        if (xmlAttributes.value("mandatory").toString() == "true") attribute->setMandatory(true); else attribute->setMandatory(false);
    }
    if (xmlAttributes.hasAttribute("itemOrder")) {
        attribute->setItemOrder(xmlAttributes.value("itemOrder").toInt());
    }
    xml.readNext(); // next element
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == xmlElementName_Attribute)) {
        xml.readNext(); // next element
    }
    return attribute;
}

PRAALINE_CORE_END_NAMESPACE
