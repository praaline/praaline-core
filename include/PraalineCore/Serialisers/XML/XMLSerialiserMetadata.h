#ifndef XMLSERIALISERMETADATA_H
#define XMLSERIALISERMETADATA_H

/*
    Praaline - Core module - XML Serialisers
    Copyright (c) 2011-2020 George Christodoulides

    This program or module is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version. It is provided
    for educational purposes and is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
    the GNU General Public License for more details.
*/

#include <QList>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Corpus/Corpus.h"
#include "PraalineCore/Corpus/CorpusCommunication.h"
#include "PraalineCore/Corpus/CorpusSpeaker.h"
#include "PraalineCore/Corpus/CorpusRecording.h"
#include "PraalineCore/Corpus/CorpusAnnotation.h"
#include "PraalineCore/Structure/MetadataStructure.h"
#include "PraalineCore/Serialisers/XML/XMLSerialiserBase.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class XMLSerialiserMetadata : public XMLSerialiserBase
{
public:
    static bool saveCorpus(Corpus *corpus, MetadataStructure* mstructure, QXmlStreamWriter &xml);
    static bool saveCommunication(CorpusCommunication *com, MetadataStructure *mstructure, QXmlStreamWriter &xml);
    static bool saveSpeaker(CorpusSpeaker *spk, MetadataStructure *mstructure, QXmlStreamWriter &xml);
    static bool saveRecording(CorpusRecording *rec, MetadataStructure *mstructure, QXmlStreamWriter &xml);
    static bool saveAnnotation(CorpusAnnotation *annot, MetadataStructure *mstructure, QXmlStreamWriter &xml);
    static bool saveParticipation(CorpusParticipation *participation, MetadataStructure *mstructure, QXmlStreamWriter &xml);

    static bool saveCorpora(const QList<Corpus *> &list, MetadataStructure *mstructure, QXmlStreamWriter &xml);
    static bool saveCommunications(const QList<CorpusCommunication *> &list, MetadataStructure *mstructure, QXmlStreamWriter &xml);
    static bool saveSpeakers(const QList<CorpusSpeaker *> &list, MetadataStructure *mstructure, QXmlStreamWriter &xml);
    static bool saveRecordings(const QList<CorpusRecording *> &list, MetadataStructure *mstructure, QXmlStreamWriter &xml);
    static bool saveAnnotations(const QList<CorpusAnnotation *> &list, MetadataStructure *mstructure, QXmlStreamWriter &xml);
    static bool saveParticipations(const QList<CorpusParticipation *> &list, MetadataStructure *mstructure, QXmlStreamWriter &xml);

    static bool loadCorpora(QList<Corpus *> &list, MetadataStructure *mstructure, QXmlStreamReader &xml);
    static bool loadCommunications(QList<CorpusCommunication *> &list, MetadataStructure *mstructure, QXmlStreamReader &xml);
    static bool loadSpeakers(QList<CorpusSpeaker *> &list, MetadataStructure *mstructure, QXmlStreamReader &xml);
    static bool loadRecordings(QList<CorpusRecording *> &list, MetadataStructure *mstructure, QXmlStreamReader &xml);
    static bool loadAnnotations(QList<CorpusAnnotation *> &list, MetadataStructure *mstructure, QXmlStreamReader &xml);
   // static bool loadParticipations(QList<CorpusParticipation *> &list, MetadataStructure *mstructure, QXmlStreamReader &xml);

protected:
    XMLSerialiserMetadata() {}
    ~XMLSerialiserMetadata() {}

private:
    static Corpus *readCorpus(MetadataStructure *mstructure, QXmlStreamReader &xml);
    static CorpusCommunication *readCommunication(MetadataStructure *mstructure, QXmlStreamReader &xml);
    static CorpusSpeaker *readSpeaker(MetadataStructure *mstructure, QXmlStreamReader &xml);
    static CorpusRecording *readRecording(MetadataStructure *mstructure, QXmlStreamReader &xml);
    static CorpusAnnotation *readAnnotation(MetadataStructure *mstructure, QXmlStreamReader &xml);
   // static CorpusParticipation *readParticipation(MetadataStructure *mstructure, QXmlStreamReader &xml);

    static void readAttributes(CorpusObject::Type what, CorpusObject *obj, MetadataStructure *mstructure, QXmlStreamReader &xml);

    static QString xmlElementName_Corpus;
    static QString xmlElementName_Communication;
    static QString xmlElementName_Speaker;
    static QString xmlElementName_Recording;
    static QString xmlElementName_Annotation;
    static QString xmlElementName_Participation;
};

PRAALINE_CORE_END_NAMESPACE

#endif // XMLSERIALISERMETADATA_H
