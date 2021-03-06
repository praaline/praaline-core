#ifndef CORPUSBOOKMARK_H
#define CORPUSBOOKMARK_H

/*
    Praaline - Core module - Corpus metadata
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

#include <QObject>
#include <QString>
#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Base/RealTime.h"
#include "PraalineCore/Corpus/CorpusObject.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT CorpusBookmark : public CorpusObject
{
    Q_OBJECT
    Q_PROPERTY(QString communicationID READ communicationID WRITE setCommunicationID)
    Q_PROPERTY(QString annotationID READ annotationID WRITE setAnnotationID)
    Q_PROPERTY(RealTime time READ time WRITE setTime)
    Q_PROPERTY(RealTime timeStart READ timeStart WRITE setTimeStart)
    Q_PROPERTY(RealTime timeEnd READ timeEnd WRITE setTimeEnd)
    Q_PROPERTY(RealTime duration READ duration)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString notes READ notes WRITE setNotes)

public:
    explicit CorpusBookmark(QObject *parent = nullptr);
    CorpusBookmark(const QString &corpusID, const QString &communicationID, const QString &annotationID,
                   const RealTime &time,
                   const QString &name, const QString &notes = QString(), QObject *parent = nullptr);
    CorpusBookmark(const QString &corpusID, const QString &communicationID, const QString &annotationID,
                   const RealTime &timeStart, const RealTime &timeEnd,
                   const QString &name, const QString &notes = QString(), QObject *parent = nullptr);

    QString ID() const override;
    void setID(const QString &ID) override { Q_UNUSED(ID) }

    CorpusObject::Type type() const override { return CorpusObject::Type_Bookmark; }
    bool save() override { return false; }

    // Inherits: QString corpusID() const; from CorpusObject
    QString communicationID() const { return m_communicationID; }
    QString annotationID() const { return m_annotationID; }
    RealTime time() const { return m_time; }
    RealTime timeStart() const { return m_time; }
    RealTime timeEnd() const { return m_timeEnd; }
    RealTime duration() const { return m_timeEnd - m_time; }
    QString name() const { return m_name; }
    QString notes() const { return m_notes; }

    void set(const QString &corpusID = QString(), const QString &communicationID = QString(), const QString &annotationID = QString(),
             const RealTime &time = RealTime(-1, 0),
             const QString &name = QString(), const QString &notes = QString());
    void set(const QString &corpusID = QString(), const QString &communicationID = QString(), const QString &annotationID = QString(),
             const RealTime &timeStart = RealTime(-1, 0), const RealTime &timeEnd = RealTime(-1, 0),
             const QString &name = QString(), const QString &notes = QString());
    // Inherits: void setCorpusID(const QString &corpusID); from Corpus Object
    void setCommunicationID(const QString &communicationID);
    void setAnnotationID(const QString &annotationID);
    void setTime(const RealTime &time);
    void setTimeStart(const RealTime &time);
    void setTimeEnd(const RealTime &time);
    void setName(const QString &name);
    void setNotes(const QString &notes);

private:
    QString m_communicationID;
    QString m_annotationID;
    RealTime m_time;
    RealTime m_timeEnd;
    QString m_name;
    QString m_notes;

    Q_DISABLE_COPY(CorpusBookmark)
};

PRAALINE_CORE_END_NAMESPACE

#endif // CORPUSBOOKMARK_H
