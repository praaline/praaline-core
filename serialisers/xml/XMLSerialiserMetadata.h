#ifndef XMLSERIALISERCORPUS_H
#define XMLSERIALISERCORPUS_H

/*
    Praaline - Core module - XML Serialisers
    Copyright (c) 2011-2018 George Christodoulides

    This program or module is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version. It is provided
    for educational purposes and is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
    the GNU General Public License for more details.
*/

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "XMLSerialiserBase.h"
#include "corpus/Corpus.h"
#include "corpus/CorpusCommunication.h"
#include "corpus/CorpusSpeaker.h"
#include "corpus/CorpusRecording.h"
#include "corpus/CorpusAnnotation.h"

namespace Praaline {
namespace Core {

class XMLSerialiserCorpus : XMLSerialiserBase
{
public:
    static bool saveCorpus(Corpus *corpus, QXmlStreamWriter &xml);
    static bool loadCorpus(Corpus *corpus, QXmlStreamReader &xml);

private:
    XMLSerialiserCorpus();
    static void writeCommunication(CorpusCommunication *com, MetadataStructure *mstructure, QXmlStreamWriter &xml);
    static void writeSpeaker(CorpusSpeaker *spk, MetadataStructure *mstructure, QXmlStreamWriter &xml);
    static void writeRecording(CorpusRecording *rec, MetadataStructure *mstructure, QXmlStreamWriter &xml);
    static void writeAnnotation(CorpusAnnotation *annot, MetadataStructure *mstructure, QXmlStreamWriter &xml);
    static void writeParticipation(CorpusParticipation *participation, MetadataStructure *mstructure, QXmlStreamWriter &xml);

    static CorpusCommunication *readCommunication(MetadataStructure *mstructure, QXmlStreamReader &xml);
    static CorpusSpeaker *readSpeaker(MetadataStructure *mstructure, QXmlStreamReader &xml);
    static CorpusRecording *readRecording(MetadataStructure *mstructure, QXmlStreamReader &xml);
    static CorpusAnnotation *readAnnotation(MetadataStructure *mstructure, QXmlStreamReader &xml);
    static void readParticipation(Corpus *corpus, MetadataStructure *mstructure, QXmlStreamReader &xml);

    static void readAttributes(CorpusObject *obj, MetadataStructure *mstructure, CorpusObject::Type what, QXmlStreamReader &xml);

    static QString xmlElementName_Corpus;
    static QString xmlElementName_Communication;
    static QString xmlElementName_Speaker;
    static QString xmlElementName_Recording;
    static QString xmlElementName_Annotation;
    static QString xmlElementName_Participation;
};

} // namespace Core
} // namespace Praaline

#endif // XMLSERIALISERCORPUS_H
