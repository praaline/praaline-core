#ifndef QUERYOCCURRENCE_H
#define QUERYOCCURRENCE_H

/*
    Praaline - Core module - Queries and Datasets
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
#include <QMap>
#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Annotation/Interval.h"

PRAALINE_CORE_BEGIN_NAMESPACE

struct PRAALINE_CORE_SHARED_EXPORT QueryOccurrencePointer
{
    QString corpusID;
    QString communicationID;
    QString annotationID;
    QString speakerID;
    QString annotationLevelID;
    int intervalNoMin;
    int intervalNoMax;
    long long tMin_nsec;
    long long tMax_nsec;
};

class PRAALINE_CORE_SHARED_EXPORT QueryOccurrence : public QObject
{
    Q_OBJECT
public:
    class ResultInterval {
    public:
        enum Type { LeftContext, Target, RightContext };

        ResultInterval() : type(ResultInterval::Target), intervalNo(0), interval(nullptr)
        {}
        ResultInterval(ResultInterval::Type type, const QString &speakerID, int intervalNo, Interval *interval) :
            type(type), speakerID(speakerID), intervalNo(intervalNo), interval(interval)
        {}

        Type type;
        QString speakerID;
        int intervalNo;
        Interval *interval;
    };

    explicit QueryOccurrence(const QString &corpusID, const QString &communicationID, const QString &annotationID,
                             const QMap<QString, QList<ResultInterval> > &resultIntervals,
                             QObject *parent = nullptr);
    ~QueryOccurrence();

    QString corpusID() const { return m_corpusID; }
    QString communicationID() const { return m_communicationID; }
    QString annotationID() const { return m_annotationID; }
    RealTime tMin() const;
    RealTime tMax() const;
    QStringList annotationLevelIDs() const;
    QStringList speakerIDs() const;
    int intervalNoTarget() const;

    // lazy load mechanism
    bool loaded() const { return m_loaded; }
    QList<ResultInterval> resultIntervals(const QString &annotationLevelID);
    int resultIntervalsCount(const QString &annotationLevelID) const;
    QList<ResultInterval> leftContext(const QString &annotationLevelID);
    QList<ResultInterval> target(const QString &annotationLevelID);
    QList<ResultInterval> rightContext(const QString &annotationLevelID);

signals:

public slots:

protected:
    QString m_corpusID;
    QString m_communicationID;
    QString m_annotationID;
    // Annotation level : a sequence of result intervals
    bool m_loaded;
    QMap<QString, QList<ResultInterval> > m_resultIntervals;
};

PRAALINE_CORE_END_NAMESPACE

#endif // QUERYOCCURRENCE_H
