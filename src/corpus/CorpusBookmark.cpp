#include "corpus/CorpusBookmark.h"

PRAALINE_CORE_BEGIN_NAMESPACE

CorpusBookmark::CorpusBookmark(QObject *parent) :
    CorpusObject(nullptr, parent)
{
}

CorpusBookmark::CorpusBookmark(const QString &corpusID, const QString &communicationID, const QString &annotationID,
                               const RealTime &time,
                               const QString &name, const QString &notes, QObject *parent) :
    CorpusObject(nullptr, parent),
    m_communicationID(communicationID), m_annotationID(annotationID),
    m_time(time), m_timeEnd(time), m_name(name), m_notes(notes)
{
    m_corpusID = corpusID;
}

CorpusBookmark::CorpusBookmark(const QString &corpusID, const QString &communicationID, const QString &annotationID,
                               const RealTime &timeStart, const RealTime &timeEnd,
                               const QString &name, const QString &notes, QObject *parent) :
    CorpusObject(nullptr, parent),
    m_communicationID(communicationID), m_annotationID(annotationID),
    m_time(timeStart), m_timeEnd(timeEnd), m_name(name), m_notes(notes)
{
    m_corpusID = corpusID;
}


QString CorpusBookmark::ID() const
{
    return QString("%1_%2_%3_%4_%5")
            .arg(m_corpusID).arg(m_communicationID).arg(m_annotationID)
            .arg(m_time.toDouble()).arg((m_timeEnd.toDouble()));
}

void CorpusBookmark::set(const QString &corpusID, const QString &communicationID, const QString &annotationID,
                         const RealTime &time, const QString &name, const QString &notes)
{
    if (!corpusID.isEmpty()) m_corpusID = corpusID;
    if (!communicationID.isEmpty()) m_communicationID = communicationID;
    if (!annotationID.isEmpty()) m_annotationID = annotationID;
    if (time != RealTime(-1, 0)) { m_time = time; m_timeEnd = time; }
    if (!name.isEmpty()) m_name = name;
    if (!notes.isEmpty()) m_notes = notes;
    m_isDirty = true;
}

void CorpusBookmark::set(const QString &corpusID, const QString &communicationID, const QString &annotationID,
                         const RealTime &timeStart, const RealTime &timeEnd, const QString &name, const QString &notes)
{
    if (!corpusID.isEmpty()) m_corpusID = corpusID;
    if (!communicationID.isEmpty()) m_communicationID = communicationID;
    if (!annotationID.isEmpty()) m_annotationID = annotationID;
    if (timeStart != RealTime(-1, 0)) m_time = timeStart;
    if (timeEnd != RealTime(-1, 0)) m_timeEnd = timeEnd;
    if (!name.isEmpty()) m_name = name;
    if (!notes.isEmpty()) m_notes = notes;
    m_isDirty = true;
}


void CorpusBookmark::setCommunicationID(const QString &communicationID)
{
    if (m_communicationID != communicationID) {
        m_communicationID = communicationID;
        m_isDirty = true;
    }
}

void CorpusBookmark::setAnnotationID(const QString &annotationID)
{
    if (m_annotationID != annotationID) {
        m_annotationID = annotationID;
        m_isDirty = true;
    }
}

void CorpusBookmark::setTime(const RealTime &time)
{
    if (m_time != time) {
        m_time = time;
        m_timeEnd = time;
        m_isDirty = true;
    }
}

void CorpusBookmark::setTimeStart(const RealTime &timeStart)
{
    if (m_time != timeStart) {
        m_time = timeStart;
        m_isDirty = true;
    }
}

void CorpusBookmark::setTimeEnd(const RealTime &timeEnd)
{
    if (m_timeEnd != timeEnd) {
        m_timeEnd = timeEnd;
        m_isDirty = true;
    }
}

void CorpusBookmark::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;
        m_isDirty = true;
    }
}

void CorpusBookmark::setNotes(const QString &notes)
{
    if (m_notes != notes) {
        m_notes = notes;
        m_isDirty = true;
    }
}

PRAALINE_CORE_END_NAMESPACE
