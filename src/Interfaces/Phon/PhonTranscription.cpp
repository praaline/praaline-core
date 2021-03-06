#include <QDebug>
#include <QString>
#include <QDate>
#include <QXmlStreamReader>

#include "PraalineCore/Corpus/Corpus.h"
#include "PraalineCore/Interfaces/Phon/PhonTranscription.h"

PRAALINE_CORE_BEGIN_NAMESPACE

QString PhonTranscription::xmlElementName_Session("session");
QString PhonTranscription::xmlElementName_Header("header");
QString PhonTranscription::xmlElementName_Participant("participant");
QString PhonTranscription::xmlElementName_UserTier("userTier");
QString PhonTranscription::xmlElementName_Tier("tier");

struct PhonTranscriptionData {
    QString sessionID;
    QString corpusID;
    QString phonVersion;
    QDate recordingDate;
    QString recordingFilename;
    QHash<QString, PhonTranscription::ParticipantInfo> participants;
    QHash<QString, PhonTranscription::TierInfo> phonTierInfo;
    QStringList phonTierOrder;
    QList<PhonTranscription::Segment> segments;
};

PhonTranscription::PhonTranscription() :
    d(new PhonTranscriptionData)
{
}

PhonTranscription::~PhonTranscription()
{
    delete d;
}

// ====================================================================================================================

QString PhonTranscription::sessionID() const
{
    return d->sessionID;
}

QString PhonTranscription::corpusID() const
{
    return d->corpusID;
}

QString PhonTranscription::phonVersion() const
{
    return d->phonVersion;
}

QDate PhonTranscription::recordingDate() const
{
    return d->recordingDate;
}

QString PhonTranscription::recordingFilename() const
{
    return d->recordingFilename;
}

QStringList PhonTranscription::participantIDs() const
{
    return d->participants.keys();
}

PhonTranscription::ParticipantInfo PhonTranscription::participant(const QString &participantID) const
{
    return d->participants.value(participantID);
}

QStringList PhonTranscription::phonTierNames() const
{
    return d->phonTierInfo.keys();
}

PhonTranscription::TierInfo PhonTranscription::phonTierInfo(const QString &tierName) const
{
    return d->phonTierInfo.value(tierName);
}

QStringList PhonTranscription::phonTierOrder() const
{
    return d->phonTierOrder;
}

QList<PhonTranscription::Segment> &PhonTranscription::segments() const
{
    return d->segments;
}

// ====================================================================================================================

bool PhonTranscription::load(const QString &filename)
{
    bool result(false);
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
    QXmlStreamReader xml(&file);
    while (!xml.atEnd() && !xml.hasError()) {
        // If token is StartElement, we'll see if we can read it.
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == QLatin1String("session")) {
            result = readSession(xml);
            file.close();
        }
        xml.readNext(); // next element
    }
    // Removes any device() or data from the reader and resets its internal state to the initial state.
    xml.clear();
    file.close();
    return result;
}

// private
bool PhonTranscription::readSession(QXmlStreamReader &xml)
{
    if ((xml.tokenType() != QXmlStreamReader::StartElement) || (xml.name() != xmlElementName_Session)) return false;
    // Attributes
    if (xml.attributes().hasAttribute("id"))        d->sessionID = xml.attributes().value("id").toString();
    if (xml.attributes().hasAttribute("corpus"))    d->corpusID = xml.attributes().value("corpus").toString();
    if (xml.attributes().hasAttribute("version"))   d->phonVersion = xml.attributes().value("version").toString();
    // Child elements
    xml.readNext();
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == xmlElementName_Session) && !xml.atEnd()) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if      (xml.name() == QLatin1String("header")) {
                readHeader(xml);
            }
            else if (xml.name() == QLatin1String("participants")) {
                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QLatin1String("participants")) && !xml.atEnd()) {
                    if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == xmlElementName_Participant) {
                        readParticipant(xml);
                    }
                    xml.readNext();
                }
            }
            else if (xml.name() == QLatin1String("userTiers")) {
                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QLatin1String("userTiers")) && !xml.atEnd()) {
                    if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == xmlElementName_UserTier) {
                        readUserTier(xml);
                    }
                    xml.readNext();
                }
            }
            else if (xml.name() == QLatin1String("tierOrder")) {
                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QLatin1String("tierOrder")) && !xml.atEnd()) {
                    if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == xmlElementName_Tier) {
                        readTierOrder(xml);
                    }
                    xml.readNext();
                }
            }
            else if (xml.name() == QLatin1String("transcript")) {
                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QLatin1String("transcript")) && !xml.atEnd()) {
                    if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == QLatin1String("u")) {
                        readSegment(xml);
                    }
                    xml.readNext();
                }
            }
        }
        xml.readNext();
    }
    return true;
}

// private
bool PhonTranscription::readHeader(QXmlStreamReader &xml)
{
    if ((xml.tokenType() != QXmlStreamReader::StartElement) || (xml.name() != xmlElementName_Header)) return false;
    xml.readNext();
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == xmlElementName_Header) && !xml.atEnd()) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if      (xml.name() == QLatin1String("date"))  { d->recordingDate = QDate::fromString(xml.readElementText()); }
            else if (xml.name() == QLatin1String("media")) { d->recordingFilename = xml.readElementText(); }
        }
        xml.readNext();
    }
    return true;
}

// private
bool PhonTranscription::readParticipant(QXmlStreamReader &xml)
{
    if ((xml.tokenType() != QXmlStreamReader::StartElement) || (xml.name() != xmlElementName_Participant)) return false;
    ParticipantInfo participant;
    if (xml.attributes().hasAttribute("id")) participant.ID = xml.attributes().value("id").toString();
    xml.readNext();
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == xmlElementName_Participant) && !xml.atEnd()) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if      (xml.name() == QLatin1String("role"))      { participant.role = xml.readElementText(); }
            else if (xml.name() == QLatin1String("name"))      { participant.name = xml.readElementText(); }
            else if (xml.name() == QLatin1String("sex"))       { participant.sex = xml.readElementText(); }
            else if (xml.name() == QLatin1String("language"))  { participant.language = xml.readElementText(); }
        }
        xml.readNext();
    }
    d->participants.insert(participant.ID, participant);
    return true;
}

// private
bool PhonTranscription::readUserTier(QXmlStreamReader &xml)
{
    if ((xml.tokenType() != QXmlStreamReader::StartElement) || (xml.name() != xmlElementName_UserTier)) return false;
    // Get tier name, verify it is not empty
    QString tierName;
    if (xml.attributes().hasAttribute("tierName")) tierName = xml.attributes().value("tierName").toString();
    if (tierName.isEmpty()) return false;
    // Create tier if it did not exist
    if (!d->phonTierInfo.contains(tierName)) {
        TierInfo tier;
        tier.userTier = true;
        d->phonTierInfo.insert(tierName, tier);
    }
    // Update attributes
    if (xml.attributes().hasAttribute("grouped"))
        d->phonTierInfo[tierName].grouped = (xml.attributes().value("grouped").toString() == "true") ? true : false;
    return true;
}

// private
bool PhonTranscription::readTierOrder(QXmlStreamReader &xml)
{
    if ((xml.tokenType() != QXmlStreamReader::StartElement) || (xml.name() != xmlElementName_Tier)) return false;
    // Get tier name, verify it is not empty
    QString tierName;
    if (xml.attributes().hasAttribute("tierName")) tierName = xml.attributes().value("tierName").toString();
    if (tierName.isEmpty()) return false;
    // Create tier if it did not exist
    if (!d->phonTierInfo.contains(tierName)) {
        TierInfo tier;
        tier.userTier = true;
        d->phonTierInfo.insert(tierName, tier);
    }
    // Update tier order
    d->phonTierOrder << tierName;
    // Update attributes
    if (xml.attributes().hasAttribute("visible"))
        d->phonTierInfo[tierName].visible = (xml.attributes().value("visible").toString() == "true") ? true : false;
    if (xml.attributes().hasAttribute("locked"))
        d->phonTierInfo[tierName].locked = (xml.attributes().value("locked").toString() == "true") ? true : false;
    if (xml.attributes().hasAttribute("font"))
        d->phonTierInfo[tierName].font = xml.attributes().value("font").toString();
    return true;
}

// private
bool PhonTranscription::readSegment(QXmlStreamReader &xml)
{
    if ((xml.tokenType() != QXmlStreamReader::StartElement) || (xml.name() != QLatin1String("u"))) return false;
    Segment segment;
    if (xml.attributes().hasAttribute("speaker"))
        segment.speakerID = xml.attributes().value("speaker").toString();
    if (xml.attributes().hasAttribute("id"))
        segment.segmentID = xml.attributes().value("id").toString();
    if (xml.attributes().hasAttribute("excludeFromSearches"))
        segment.excludeFromSearches = (xml.attributes().value("excludeFromSearches").toString() == "true") ? true : false;
    xml.readNext();
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QLatin1String("u")) && !xml.atEnd()) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if      (xml.name() == QLatin1String("orthography"))   { readSegmentOrthography(xml, segment); }
            else if (xml.name() == QLatin1String("ipaTier"))       { readSegmentIPATier(xml, segment); }
            else if (xml.name() == QLatin1String("alignment"))     { readSegmentAlignment(xml, segment); }
            else if (xml.name() == QLatin1String("groupTier"))     { readSegmentGroupTier(xml, segment); }
            else if (xml.name() == QLatin1String("segment")) {
                if (xml.attributes().hasAttribute("startTime"))
                    segment.startTime = RealTime::fromSeconds(xml.attributes().value("startTime").toDouble() / 1000.0);
                if (xml.attributes().hasAttribute("duration"))
                    segment.duration = RealTime::fromSeconds(xml.attributes().value("duration").toDouble() / 1000.0);
            }
        }
        xml.readNext();
    }
    d->segments << segment;
    return true;
}

// private
bool PhonTranscription::readSegmentOrthography(QXmlStreamReader &xml, PhonTranscription::Segment &segment)
{
    if ((xml.tokenType() != QXmlStreamReader::StartElement) || (xml.name() != QLatin1String("orthography"))) return false;
    xml.readNext();
    QStringList words;
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QLatin1String("orthography")) && !xml.atEnd()) {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == QLatin1String("g"))   {
            xml.readNext();
            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QLatin1String("g")) && !xml.atEnd()) {
                if (xml.tokenType() == QXmlStreamReader::StartElement) {
                    if      (xml.name() == QLatin1String("w")) { words << xml.readElementText(); }
                    else if (xml.name() == QLatin1String("p")) { words << xml.readElementText(); }
                }
                xml.readNext();
            }
        }
        xml.readNext();
    }
    segment.orthography.clear();
    segment.orthography << words;
    return true;
}

// private
bool PhonTranscription::readSegmentIPATier(QXmlStreamReader &xml, PhonTranscription::Segment &segment)
{
    if ((xml.tokenType() != QXmlStreamReader::StartElement) || (xml.name() != QLatin1String("ipaTier"))) return false;
    IPAData ipaData;
    if (xml.attributes().hasAttribute("form")) ipaData.form = xml.attributes().value("form").toString();
    xml.readNext();
    QStringList ipaWords;
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QLatin1String("ipaTier")) && !xml.atEnd()) {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == QLatin1String("pg"))   {
            xml.readNext();
            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QLatin1String("pg")) && !xml.atEnd()) {
                if (xml.tokenType() == QXmlStreamReader::StartElement) {
                    if      (xml.name() == QLatin1String("w")) { ipaWords << xml.readElementText(); }
                }
                xml.readNext();
            }
        }
        xml.readNext();
    }
    ipaData.pg.clear();
    ipaData.pg << ipaWords;
    if (ipaData.form == "model")
        segment.ipaModel = ipaData;
    else if (ipaData.form == "actual")
        segment.ipaActual = ipaData;
    else return false;
    return true;
}

// private
bool PhonTranscription::readSegmentAlignment(QXmlStreamReader &xml, PhonTranscription::Segment &segment)
{
    Q_UNUSED(segment)
    if ((xml.tokenType() != QXmlStreamReader::StartElement) || (xml.name() != QLatin1String("alignment"))) return false;
    xml.readNext();
    return true;
}

// private
bool PhonTranscription::readSegmentGroupTier(QXmlStreamReader &xml, PhonTranscription::Segment &segment)
{
    if ((xml.tokenType() != QXmlStreamReader::StartElement) || (xml.name() != QLatin1String("groupTier"))) return false;
    // Find the name of the tier we're reading
    QString tierName;
    if (xml.attributes().hasAttribute("tierName")) tierName = xml.attributes().value("tierName").toString();
    if (tierName.isEmpty()) return false;
    // Read it
    xml.readNext();
    QStringList words;
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QLatin1String("groupTier")) && !xml.atEnd()) {
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == QLatin1String("tg"))   {
            xml.readNext();
            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QLatin1String("tg")) && !xml.atEnd()) {
                if (xml.tokenType() == QXmlStreamReader::StartElement) {
                    if      (xml.name() == QLatin1String("w")) { words << xml.readElementText(); }
                    else if (xml.name() == QLatin1String("p")) { words << xml.readElementText(); }
                }
                xml.readNext();
            }
        }
        xml.readNext();
    }
    segment.groupTiers.insert(tierName, words);
    return true;
}

PRAALINE_CORE_END_NAMESPACE
