#ifndef CORPUSSPEAKERRELATION_H
#define CORPUSSPEAKERRELATION_H

/*
    Praaline - Core module - Corpus metadata
    Copyright (c) 2021 George Christodoulides

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
#include "PraalineCore/Corpus/CorpusObject.h"
#include "PraalineCore/Corpus/CorpusCommunication.h"
#include "PraalineCore/Corpus/CorpusSpeaker.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class Corpus;

class PRAALINE_CORE_SHARED_EXPORT CorpusSpeakerRelation : public CorpusObject
{
    Q_OBJECT
    Q_PROPERTY(QString relation READ relation)
    Q_PROPERTY(QString communicationID READ communicationID)
    Q_PROPERTY(QString speakerID_1 READ speakerID_1)
    Q_PROPERTY(QString speakerID_2 READ speakerID_2)

public:
    CorpusSpeakerRelation(const QString &relation,
                          CorpusCommunication * com, CorpusSpeaker * spk1, CorpusSpeaker * spk2,
                          QObject *parent = nullptr);
    ~CorpusSpeakerRelation() override {}
    void copyProperties(CorpusSpeakerRelation *other);

    CorpusObject::Type type() const override { return CorpusObject::Type_SpeakerRelation; }
    bool save() override;

    // override CorpusObject ID methods
    QString ID() const override;
    void setID(const QString &ID) override;

    Corpus * corpus() const;

    // read-only properties
    QString relation() const;
    CorpusCommunication * communication() const;
    CorpusSpeaker * speaker_1() const;
    CorpusSpeaker * speaker_2() const;
    QString communicationID() const;
    QString speakerID_1() const;
    QString speakerID_2() const;

private:
    QString m_relation;
    CorpusCommunication * m_communication;
    CorpusSpeaker * m_speaker_1;
    CorpusSpeaker * m_speaker_2;

    Q_DISABLE_COPY(CorpusSpeakerRelation)
};

PRAALINE_CORE_END_NAMESPACE

#endif // CORPUSSPEAKERRELATION_H
