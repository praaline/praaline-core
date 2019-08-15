#include <QString>
#include <QList>
#include <QDate>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "XMLSerialiserBase.h"
#include "corpus/Corpus.h"
#include "corpus/CorpusCommunication.h"
#include "corpus/CorpusSpeaker.h"
#include "corpus/CorpusRecording.h"
#include "corpus/CorpusAnnotation.h"
#include "XMLSerialiserMetadataStructure.h"
#include "XMLSerialiserAnnotationStructure.h"
#include "XMLSerialiserMetadata.h"

PRAALINE_CORE_BEGIN_NAMESPACE

QString XMLSerialiserMetadata::xmlElementName_Corpus("Corpus");
QString XMLSerialiserMetadata::xmlElementName_Communication("Communication");
QString XMLSerialiserMetadata::xmlElementName_Speaker("Speaker");
QString XMLSerialiserMetadata::xmlElementName_Recording("Recording");
QString XMLSerialiserMetadata::xmlElementName_Annotation("Annotation");
QString XMLSerialiserMetadata::xmlElementName_Participation("Participation");

// ========================================================================================================================================

// public static
bool XMLSerialiserMetadata::saveCorpus(Corpus *corpus, MetadataStructure* mstructure, QXmlStreamWriter &xml)
{
    Q_UNUSED(corpus)
    Q_UNUSED(mstructure)
    Q_UNUSED(xml)
    //    xml.writeStartElement("CorpusData");
    //    xml.writeStartElement("Communications");
    //    foreach (CorpusCommunication *com, corpus->communications()) {
    //        writeCommunication(com, corpus->metadataStructure(), xml);
    //    }
    //    xml.writeEndElement(); // Communications
    //    xml.writeStartElement("Speakers");
    //    foreach (CorpusSpeaker *spk, corpus->speakers()) {
    //        writeSpeaker(spk, corpus->metadataStructure(), xml);
    //    }
    //    xml.writeEndElement(); // Speakers
    //    xml.writeStartElement("Participations");
    //    foreach (CorpusParticipation *participation, corpus->participations()) {
    //        writeParticipation(participation, corpus->metadataStructure(), xml);
    //    }
    //    xml.writeEndElement(); // Participations
    //    xml.writeEndElement(); // CorpusData
    //    return true;
    return false;
}

// public static
bool XMLSerialiserMetadata::saveCommunication(CorpusCommunication *com, MetadataStructure *mstructure, QXmlStreamWriter &xml)
{
    if (!com) return false;
    xml.writeStartElement(xmlElementName_Communication);
    xml.writeAttribute("id", com->ID());
    xml.writeAttribute("name", com->name());
    foreach (MetadataStructureAttribute *attribute, mstructure->attributes(CorpusObject::Type_Communication)) {
        xml.writeAttribute(attribute->ID(), com->property(attribute->ID()).toString());
    }
    foreach (CorpusRecording *rec, com->recordings()) {
        saveRecording(rec, mstructure, xml);
    }
    foreach (CorpusAnnotation *annot, com->annotations()) {
        saveAnnotation(annot, mstructure, xml);
    }
    xml.writeEndElement(); // Communication
    return true;
}

// public static
bool XMLSerialiserMetadata::saveSpeaker(CorpusSpeaker *spk, MetadataStructure *mstructure, QXmlStreamWriter &xml)
{
    if (!spk) return false;
    xml.writeStartElement(xmlElementName_Speaker);
    xml.writeAttribute("id", spk->ID());
    xml.writeAttribute("name", spk->name());
    foreach (MetadataStructureAttribute *attribute, mstructure->attributes(CorpusObject::Type_Speaker)) {
        xml.writeAttribute(attribute->ID(), spk->property(attribute->ID()).toString());
    }
    xml.writeEndElement(); // Speaker
    return true;
}

// public static
bool XMLSerialiserMetadata::saveRecording(CorpusRecording *rec, MetadataStructure *mstructure, QXmlStreamWriter &xml)
{
    if (!rec) return false;
    xml.writeStartElement(xmlElementName_Recording);
    xml.writeAttribute("id", rec->ID());
    xml.writeAttribute("name", rec->name());
    xml.writeAttribute("filename", rec->filename());
    xml.writeAttribute("format", rec->format());
    xml.writeAttribute("duration", QString::number(rec->duration().toNanoseconds()));
    xml.writeAttribute("channels", QString::number(rec->channels()));
    xml.writeAttribute("sampleRate", QString::number(rec->sampleRate()));
    xml.writeAttribute("bitRate", QString::number(rec->bitRate()));
    xml.writeAttribute("encoding", rec->encoding());
    xml.writeAttribute("fileSize", QString::number(rec->fileSize()));
    xml.writeAttribute("checksumMD5", rec->checksumMD5());
    foreach (MetadataStructureAttribute *attribute, mstructure->attributes(CorpusObject::Type_Recording)) {
        xml.writeAttribute(attribute->ID(), rec->property(attribute->ID()).toString());
    }
    xml.writeEndElement(); // Recording
    return true;
}

// public static
bool XMLSerialiserMetadata::saveAnnotation(CorpusAnnotation *annot, MetadataStructure *mstructure, QXmlStreamWriter &xml)
{
    if (!annot) return false;
    xml.writeStartElement(xmlElementName_Annotation);
    xml.writeAttribute("id", annot->ID());
    xml.writeAttribute("name", annot->name());
    xml.writeAttribute("filename", annot->filename());
    xml.writeAttribute("format", annot->format());
    xml.writeStartElement("languages");
    foreach (QString language, annot->languages())
        xml.writeTextElement("language", language);
    xml.writeEndElement(); // languages
    foreach (MetadataStructureAttribute *attribute, mstructure->attributes(CorpusObject::Type_Annotation)) {
        xml.writeAttribute(attribute->ID(), annot->property(attribute->ID()).toString());
    }
    xml.writeEndElement(); // Annotation
    return true;
}

// public static
bool XMLSerialiserMetadata::saveParticipation(CorpusParticipation *participation, MetadataStructure *mstructure, QXmlStreamWriter &xml)
{
    if (!participation) return false;
    xml.writeStartElement(xmlElementName_Participation);
    xml.writeAttribute("communicationID", participation->communicationID());
    xml.writeAttribute("speakerID", participation->speakerID());
    xml.writeAttribute("role", participation->role());
    foreach (MetadataStructureAttribute *attribute, mstructure->attributes(CorpusObject::Type_Participation)) {
        xml.writeAttribute(attribute->ID(), participation->property(attribute->ID()).toString());
    }
    xml.writeEndElement(); // Participation
    return true;
}

// ====================================================================================================================

// private static
void XMLSerialiserMetadata::readAttributes(CorpusObject::Type what, CorpusObject *obj, MetadataStructure *mstructure, QXmlStreamReader &xml)
{
    QXmlStreamAttributes xmlAttributes = xml.attributes();
    foreach (QPointer<MetadataStructureAttribute> attribute, mstructure->attributes(what)) {
        if (xmlAttributes.hasAttribute(attribute->ID())) {
            if (attribute->datatype().base() == DataType::Integer)
                obj->setProperty(attribute->ID(),
                                 xmlAttributes.value(attribute->ID()).toInt());
            else if (attribute->datatype().base() == DataType::Double)
                obj->setProperty(attribute->ID(),
                                 xmlAttributes.value(attribute->ID()).toDouble());
            else if (attribute->datatype().base() == DataType::DateTime)
                obj->setProperty(attribute->ID(),
                                 QDateTime::fromString(xmlAttributes.value(attribute->ID()).toString(), Qt::ISODate));
            else
                obj->setProperty(attribute->ID(),
                                 xmlAttributes.value(attribute->ID()).toString());
        }
    }
}

// private static
Corpus *XMLSerialiserMetadata::readCorpus(MetadataStructure *mstructure, QXmlStreamReader &xml)
{
    Q_UNUSED(mstructure)
    Q_UNUSED(xml)
    //    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == xmlElementName_Corpus)) {
    //        if (xml.tokenType() == QXmlStreamReader::StartElement) {
    //            if (xml.name() == "CorpusData") {
    //                xml.readNext();
    //                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "CorpusData")) {
    //                    if (xml.tokenType() == QXmlStreamReader::StartElement) {
    //                        if (xml.name() == xmlElementName_Communication) {
    //                            CorpusCommunication *com = readCommunication(corpus->metadataStructure(), xml);
    //                            if (com) corpus->addCommunication(com);
    //                        }
    //                        else if (xml.name() == xmlElementName_Speaker) {
    //                            CorpusSpeaker *spk = readSpeaker(corpus->metadataStructure(), xml);
    //                            if (spk) corpus->addSpeaker(spk);
    //                        }
    //                        else if (xml.name() == xmlElementName_Participation) {
    //                            readParticipation(corpus, corpus->metadataStructure(), xml);
    //                        }
    //                    }
    //                    xml.readNext();
    //                }
    //            }
    //        }
    //        xml.readNext(); // next element
    //    }
    //    return true
    return nullptr;
}

// private static
CorpusCommunication *XMLSerialiserMetadata::readCommunication(MetadataStructure *mstructure, QXmlStreamReader &xml)
{
    // Check that we're really reading a communication
    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == xmlElementName_Communication) {
        return nullptr;
    }
    CorpusCommunication *com = new CorpusCommunication();
    QXmlStreamAttributes xmlAttributes = xml.attributes();
    if (xmlAttributes.hasAttribute("id"))           com->setID(xmlAttributes.value("id").toString());
    if (xmlAttributes.hasAttribute("name"))         com->setName(xmlAttributes.value("name").toString());
    readAttributes(CorpusObject::Type_Communication, com, mstructure, xml);
    // Read recordings and annotations. The order of the elements is not fixed. We'll continue the loop until
    // we hit an EndElement named Communication.
    xml.readNext();
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == xmlElementName_Communication)) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (xml.name() == xmlElementName_Recording) {
                CorpusRecording *rec = readRecording(mstructure, xml);
                if (rec) com->addRecording(rec);
            }
            else if (xml.name() == xmlElementName_Annotation) {
                CorpusAnnotation *annot = readAnnotation(mstructure, xml);
                if (annot) com->addAnnotation(annot);
            }
        }
        xml.readNext(); // next element
    }
    return com;
}

// private static
CorpusSpeaker *XMLSerialiserMetadata::readSpeaker(MetadataStructure *mstructure, QXmlStreamReader &xml)
{
    // Check that we're really reading a speaker
    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == xmlElementName_Speaker) {
        return nullptr;
    }
    CorpusSpeaker *spk = new CorpusSpeaker();
    QXmlStreamAttributes xmlAttributes = xml.attributes();
    if (xmlAttributes.hasAttribute("id"))           spk->setID(xmlAttributes.value("id").toString());
    if (xmlAttributes.hasAttribute("name"))         spk->setName(xmlAttributes.value("name").toString());
    readAttributes(CorpusObject::Type_Speaker, spk, mstructure, xml);
    return spk;

}

// private static
CorpusRecording *XMLSerialiserMetadata::readRecording(MetadataStructure *mstructure, QXmlStreamReader &xml)
{
    // Check that we're really reading a recording
    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == xmlElementName_Recording) {
        return nullptr;
    }
    CorpusRecording *rec = new CorpusRecording();
    QXmlStreamAttributes xmlAttributes = xml.attributes();
    if (xmlAttributes.hasAttribute("id"))           rec->setID(xmlAttributes.value("id").toString());
    if (xmlAttributes.hasAttribute("name"))         rec->setName(xmlAttributes.value("name").toString());
    if (xmlAttributes.hasAttribute("filename"))     rec->setFilename(xmlAttributes.value("filename").toString());
    if (xmlAttributes.hasAttribute("format"))       rec->setFormat(xmlAttributes.value("format").toString());
    if (xmlAttributes.hasAttribute("duration"))     rec->setDuration(RealTime::fromNanoseconds((xmlAttributes.value("duration").toLongLong())));
    if (xmlAttributes.hasAttribute("channels"))     rec->setChannels(xmlAttributes.value("channels").toInt());
    if (xmlAttributes.hasAttribute("sampleRate"))   rec->setSampleRate(xmlAttributes.value("sampleRate").toInt());
    if (xmlAttributes.hasAttribute("bitRate"))      rec->setBitRate(xmlAttributes.value("bitRate").toInt());
    if (xmlAttributes.hasAttribute("encoding"))     rec->setEncoding(xmlAttributes.value("encoding").toString());
    if (xmlAttributes.hasAttribute("fileSize"))     rec->setFileSize(xmlAttributes.value("fileSize").toLongLong());
    if (xmlAttributes.hasAttribute("checksumMD5"))  rec->setChecksumMD5(xmlAttributes.value("checksumMD5").toString());
    readAttributes(CorpusObject::Type_Recording, rec, mstructure, xml);
    return rec;
}

// private static
CorpusAnnotation *XMLSerialiserMetadata::readAnnotation(MetadataStructure *mstructure, QXmlStreamReader &xml)
{
    // Check that we're really reading an annotation
    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == xmlElementName_Annotation) {
        return nullptr;
    }
    CorpusAnnotation *annot = new CorpusAnnotation();
    QXmlStreamAttributes xmlAttributes = xml.attributes();
    if (xmlAttributes.hasAttribute("id"))           annot->setID(xmlAttributes.value("id").toString());
    if (xmlAttributes.hasAttribute("name"))         annot->setName(xmlAttributes.value("name").toString());
    if (xmlAttributes.hasAttribute("filename"))     annot->setFilename(xmlAttributes.value("filename").toString());
    if (xmlAttributes.hasAttribute("format"))       annot->setFormat(xmlAttributes.value("format").toString());
    readAttributes(CorpusObject::Type_Annotation, annot, mstructure, xml);
    // Languages
    xml.readNext(); // next element
    // The order of the elements is not fixed: loop until we hit an EndElement.
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "languages")) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {
            if (xml.name() == "language"){
                annot->addLanguage(xml.readElementText());
            }
        }
        xml.readNext(); // next element
    }
    return annot;
}

// private static
//CorpusParticipation *XMLSerialiserMetadata::readParticipation(MetadataStructure *mstructure, QXmlStreamReader &xml)
//{
//    // Check that we're really reading a participation
//    if (xml.tokenType() != QXmlStreamReader::StartElement && xml.name() == xmlElementName_Participation) {
//        return nullptr;
//    }
//    QString communicationID, speakerID, role;
//    QXmlStreamAttributes xmlAttributes = xml.attributes();
//    if (xmlAttributes.hasAttribute("communicationID"))  communicationID = xmlAttributes.value("communicationID").toString();
//    if (xmlAttributes.hasAttribute("speakerID"))        speakerID = xmlAttributes.value("speakerID").toString();
//    if (xmlAttributes.hasAttribute("role"))             role = xmlAttributes.value("role").toString();
//    QPointer<CorpusParticipation> participation = corpus->addParticipation(communicationID, speakerID, role);
//    if (!participation) return;
//    readAttributes(participation, mstructure, CorpusObject::Type_Participation, xml);
//}


// ========================================================================================================================================


// public static
bool XMLSerialiserMetadata::saveCorpora(const QList<QPointer<Corpus> > &list, MetadataStructure *mstructure, QXmlStreamWriter &xml)
{
    Q_UNUSED(list)
    Q_UNUSED(mstructure)
    Q_UNUSED(xml)
    return false;
}

// public static
bool XMLSerialiserMetadata::saveCommunications(const QList<QPointer<CorpusCommunication> > &list, MetadataStructure *mstructure, QXmlStreamWriter &xml)
{
    Q_UNUSED(list)
    Q_UNUSED(mstructure)
    Q_UNUSED(xml)
    return false;
}

// public static
bool XMLSerialiserMetadata::saveSpeakers(const QList<QPointer<CorpusSpeaker> > &list, MetadataStructure *mstructure, QXmlStreamWriter &xml)
{
    Q_UNUSED(list)
    Q_UNUSED(mstructure)
    Q_UNUSED(xml)
    return false;
}

// public static
bool XMLSerialiserMetadata::saveRecordings(const QList<QPointer<CorpusRecording> > &list, MetadataStructure *mstructure, QXmlStreamWriter &xml)
{
    Q_UNUSED(list)
    Q_UNUSED(mstructure)
    Q_UNUSED(xml)
    return false;
}

// public static
bool XMLSerialiserMetadata::saveAnnotations(const QList<QPointer<CorpusAnnotation> > &list, MetadataStructure *mstructure, QXmlStreamWriter &xml)
{
    Q_UNUSED(list)
    Q_UNUSED(mstructure)
    Q_UNUSED(xml)
    return false;
}

// public static
bool XMLSerialiserMetadata::saveParticipations(const QList<QPointer<CorpusParticipation> > &list, MetadataStructure *mstructure, QXmlStreamWriter &xml)
{
    Q_UNUSED(list)
    Q_UNUSED(mstructure)
    Q_UNUSED(xml)
    return false;
}

// public static
bool XMLSerialiserMetadata::loadCorpora(QList<QPointer<Corpus> > &list, MetadataStructure *mstructure, QXmlStreamReader &xml)
{
    Q_UNUSED(list)
    Q_UNUSED(mstructure)
    Q_UNUSED(xml)
    return false;
}

// public static
bool XMLSerialiserMetadata::loadCommunications(QList<QPointer<CorpusCommunication> > &list, MetadataStructure *mstructure, QXmlStreamReader &xml)
{
    Q_UNUSED(list)
    Q_UNUSED(mstructure)
    Q_UNUSED(xml)
    return false;
}

// public static
bool XMLSerialiserMetadata::loadSpeakers(QList<QPointer<CorpusSpeaker> > &list, MetadataStructure *mstructure, QXmlStreamReader &xml)
{
    Q_UNUSED(list)
    Q_UNUSED(mstructure)
    Q_UNUSED(xml)
    return false;
}

// public static
bool XMLSerialiserMetadata::loadRecordings(QList<QPointer<CorpusRecording> > &list, MetadataStructure *mstructure, QXmlStreamReader &xml)
{
    Q_UNUSED(list)
    Q_UNUSED(mstructure)
    Q_UNUSED(xml)
    return false;
}

// public static
bool XMLSerialiserMetadata::loadAnnotations(QList<QPointer<CorpusAnnotation> > &list, MetadataStructure *mstructure, QXmlStreamReader &xml)
{
    Q_UNUSED(list)
    Q_UNUSED(mstructure)
    Q_UNUSED(xml)
    return false;
}

PRAALINE_CORE_END_NAMESPACE
