#ifndef SPEAKERTIMELINE_H
#define SPEAKERTIMELINE_H

/*
    Praaline - Core module - Statistics
    Copyright (c) 2011-2019 George Christodoulides

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

#include "pncore_global.h"

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

    bool calculate(QPointer<CorpusCommunication> com, const QString &minimalLevelID);

    QString minimalLevelID() const;
    QPointer<IntervalTier> timelineDetailed() const;
    QPointer<IntervalTier> timelineCoarse() const;

signals:

public slots:

private:
    SpeakerTimelineData *d;
};

PRAALINE_CORE_END_NAMESPACE

#endif // SPEAKERTIMELINE_H
