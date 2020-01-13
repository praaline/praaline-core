#ifndef SPEAKERTIMELINE_H
#define SPEAKERTIMELINE_H

/*
    Praaline - Core module - Statistics
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
#include <QList>
#include <QScopedPointer>

#include "praaline-core_global.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class CorpusCommunication;
class IntervalTier;

struct SpeakerTimelineData;

class PRAALINE_CORE_SHARED_EXPORT SpeakerTimeline : public QObject
{
    Q_OBJECT
public:
    explicit SpeakerTimeline(QObject *parent = nullptr);
    virtual ~SpeakerTimeline();

    bool calculate(CorpusCommunication * com, const QString &minimalLevelID);

    QString minimalLevelID() const;
    IntervalTier *timelineDetailed() const;
    IntervalTier *timelineCoarse() const;

signals:

public slots:

private:
    SpeakerTimelineData *d;
};

PRAALINE_CORE_END_NAMESPACE

#endif // SPEAKERTIMELINE_H
