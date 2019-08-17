#ifndef TRANSCRIPTION_H
#define TRANSCRIPTION_H

/*
    Praaline - Core module - Annotation
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

#include "pncore_global.h"
#include <QObject>
#include <QString>
#include <QList>
#include <QStringList>
#include "base/RealTime.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class CorpusSpeaker;
class Interval;

struct TranscriptionData;

class PRAALINE_CORE_SHARED_EXPORT Transcription : public QObject
{
    Q_OBJECT
public:
    explicit Transcription(QObject *parent = nullptr);
    ~Transcription();

    int speakerCount() const;
    QStringList speakerIDs() const;
    QList<CorpusSpeaker *> speakers() const;

signals:

public slots:

private:
    TranscriptionData *d;
};

PRAALINE_CORE_END_NAMESPACE

#endif // TRANSCRIPTION_H
