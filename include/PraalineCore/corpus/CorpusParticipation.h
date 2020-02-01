#ifndef CORPUSPARTICIPATION_H
#define CORPUSPARTICIPATION_H

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
#include "praaline-core_global.h"
#include "corpus/CorpusObject.h"
#include "corpus/CorpusCommunication.h"
#include "corpus/CorpusSpeaker.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class Corpus;

class PRAALINE_CORE_SHARED_EXPORT CorpusParticipation : public CorpusObject
{
    Q_OBJECT
    Q_PROPERTY(QString communicationID READ communicationID)
    Q_PROPERTY(QString speakerID READ speakerID)
    Q_PROPERTY(QString role READ role WRITE setRole)

public:
    CorpusParticipation(CorpusCommunication * com, CorpusSpeaker * spk, QString role = QString(),
                        QObject *parent = nullptr);
    ~CorpusParticipation() override {}
    void copyProperties(CorpusParticipation *other);

    CorpusObject::Type type() const override { return CorpusObject::Type_Participation; }
    bool save() override;

    // override CorpusObject ID methods
    QString ID() const override;
    void setID(const QString &ID) override;

    Corpus * corpus() const;

    // read-only properties
    CorpusCommunication * communication() const;
    CorpusSpeaker * speaker() const;
    QString communicationID() const;
    QString speakerID() const;

    QString role() const;
    void setRole(const QString &role);

private:
    CorpusCommunication * m_communication;
    CorpusSpeaker * m_speaker;
    QString m_role;

    Q_DISABLE_COPY(CorpusParticipation)
};

PRAALINE_CORE_END_NAMESPACE

#endif // CORPUSPARTICIPATION_H
