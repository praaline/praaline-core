#ifndef CORPUSCOMMUNICATIONSPEAKERRELATION_H
#define CORPUSCOMMUNICATIONSPEAKERRELATION_H

#include <QString>
#include "PraalineCore/PraalineCore_Global.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT CorpusCommunicationSpeakerRelation
{
public:
    CorpusCommunicationSpeakerRelation(const QString &speakerID_1, const QString &speakerID_2,
                                       const QString &relation = QString(), const QString &notes = QString());

    QString speakerID_1() const;
    QString speakerID_2() const;

    QString relation() const;
    void setRelation(const QString &relation);

    QString notes() const;
    void setNotes(const QString &notes);

private:
    QString m_speakerID_1;
    QString m_speakerID_2;
    QString m_relation;
    QString m_notes;
};

PRAALINE_CORE_END_NAMESPACE

#endif // CORPUSCOMMUNICATIONSPEAKERRELATION_H
