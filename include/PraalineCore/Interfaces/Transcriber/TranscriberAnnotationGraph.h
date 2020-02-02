#ifndef TRANSCRIBERANNOTATIONGRAPH_H
#define TRANSCRIBERANNOTATIONGRAPH_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QString>

#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Base/RealTime.h"
#include "PraalineCore/Corpus/CorpusSpeaker.h"
#include "PraalineCore/Annotation/AnnotationTierGroup.h"
#include "PraalineCore/Annotation/AnnotationTier.h"
#include "PraalineCore/Annotation/IntervalTier.h"
#include "PraalineCore/Annotation/PointTier.h"
#include "PraalineCore/Interfaces/InterfaceTextFile.h"

class QXmlStreamReader;

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT TranscriberAnnotationGraph : InterfaceTextFile
{
public:    
    // Public static methods to read and write Transcriber Annotation Graphs in XML format
    static bool load(const QString &filename, QList<CorpusSpeaker *> &speakers,
                     SpeakerAnnotationTierGroupMap &tiersAll);
    static bool save(const QString &filename, QList<CorpusSpeaker *> &speakers,
                     SpeakerAnnotationTierGroupMap &tiersAll);

private:
    struct SpeakerData {
        QString ID;
        QString name;
        QString check;
        QString dialect;
        QString accent;
        QString scope;
    };

    struct TurnData {
        QStringList speakerIDs;
        RealTime startTime;
        RealTime endTime;
        QMap<QString, QList<Interval *> > intervals;
        QList<Point *> events;
    };

    struct SectionData {
        QString type;
        RealTime startTime;
        RealTime endTime;
        QString topicID;
        QList<TurnData *> turns;
    };

    struct TransData {
        QMap<QString, QString> topics;
        QList<SpeakerData *> speakers;
        QList<SectionData *> sections;
    };

    TranscriberAnnotationGraph();
    static SpeakerData  *readSpeaker(QXmlStreamReader &xml);
    static TurnData     *readTurn(QXmlStreamReader &xml);
    static SectionData  *readSection(QXmlStreamReader &xml);
    static TransData    *readTrans(QXmlStreamReader &xml);

    // XML element names
    static QString xmlElementName_Trans;
    static QString xmlElementName_Topic;
    static QString xmlElementName_Speaker;
    static QString xmlElementName_Section;
    static QString xmlElementName_Turn;
};

PRAALINE_CORE_END_NAMESPACE

#endif // TRANSCRIBERANNOTATIONGRAPH_H
