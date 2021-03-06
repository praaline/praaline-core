#ifndef EXMARALDAPARTITURTRANSCRIPTION_H
#define EXMARALDAPARTITURTRANSCRIPTION_H

#include <QObject>
#include <QString>
#include <QList>
#include <QStringList>
#include <QHash>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Base/RealTime.h"
#include "PraalineCore/Annotation/AnnotationTierGroup.h"
#include "PraalineCore/Annotation/AnnotationTier.h"
#include "PraalineCore/Annotation/IntervalTier.h"
#include "PraalineCore/Annotation/PointTier.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class ExmaraldaBasicTranscription : public QObject
{
public:
    class SpeakerInfo {
    public:
        QString id;
        QString abbreviation;
        QString sex;
        QString languagesUsed;
        QString L1;
        QString L2;
        QString comment;
        QHash<QString, QString> udMetaInfo;
    };
    class TimelineInfo {
    public:
        QString id;
        RealTime t;
        QString type;
    };
    class EventInfo {
    public:
        QString start;
        QString end;
        QString text;
    };
    class TierInfo {
    public:
        QString speaker;
        QString category;
        QString type;
        QString displayName;
        QList<EventInfo> events;
    };

    // Accessors - Mutators
    QString projectName() const { return m_projectName; }
    void setProjectName(const QString &projecetName) { m_projectName = projecetName; }
    QString transcriptionName() const { return m_transcriptionName; }
    void setTranscriptionName(const QString &transcriptionName) { m_transcriptionName = transcriptionName; }
    QString transcriptionConvention() const { return m_transcriptionConvention; }
    void setTranscriptionConvention(const QString &transcriptionConvention) { m_transcriptionConvention = transcriptionConvention; }
    QString comment() const { return m_comment; }
    void setComment(const QString &comment) { m_comment = comment; }
    QStringList & referencedFiles() { return m_referencedFiles; }
    QHash<QString, QString> & udMetaInfo() { return m_udMetaInfo; }
    QList<SpeakerInfo> & speakerTable() { return m_speakerTable; }
    QList<TimelineInfo> & commonTL() { return m_commonTL; }
    QHash<QString, TierInfo> & tiers() { return m_tiers; }

    // Public static methods to read and write Partitur transcriptions
    static bool load(const QString &filename, ExmaraldaBasicTranscription &transcription);
    static bool save(const QString &filename, ExmaraldaBasicTranscription &transcription);

signals:
    
public slots:
    
protected:

private:
    // Serialisation
    // metadata
    bool readMetadata(QXmlStreamReader &xml);
    bool writeMetadata(QXmlStreamWriter &xml);
    // meta information
    bool readMetaInformation(QXmlStreamReader &xml);
    bool writeMetaInformation(QXmlStreamWriter &xml);
    // speaker table
    bool readSpeakerTable(QXmlStreamReader &xml);
    SpeakerInfo readSpeaker(QXmlStreamReader &xml);
    bool writeSpeakerTable(QXmlStreamWriter &xml);
    // common timeline
    bool readCommonTimeline(QXmlStreamReader &xml);
    TimelineInfo readTimelineInfo(QXmlStreamReader &xml);
    bool writeCommonTimeline(QXmlStreamWriter &xml);
    // tiers
    bool readTier(QXmlStreamReader &xml);
    bool writeTier(QString id, QXmlStreamWriter &xml);

    // Data
    QString m_projectName;
    QString m_transcriptionName;
    QString m_transcriptionConvention;
    QString m_comment;
    QStringList m_referencedFiles;
    QHash<QString, QString> m_udMetaInfo;
    QList<SpeakerInfo> m_speakerTable;
    QList<TimelineInfo> m_commonTL;
    QHash<QString, TierInfo> m_tiers;
};

PRAALINE_CORE_END_NAMESPACE

#endif // EXMARALDAPARTITURTRANSCRIPTION_H
