#ifndef EXMARALDATRANSCRIPTIONBRIDGE_H
#define EXMARALDATRANSCRIPTIONBRIDGE_H

#include <QObject>
#include <QList>

#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Annotation/AnnotationTier.h"
#include "PraalineCore/Interfaces/Exmaralda/ExmaraldaBasicTranscription.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class ExmaraldaTranscriptionBridge : public QObject
{
    Q_OBJECT
public:
    class TierToExportInfo {
    public:
        QString tierID;
        QString speakerID;
        QString type;
        QString category;
        QString displayName;
        AnnotationTier *tierToExport;
    };

    explicit ExmaraldaTranscriptionBridge(QObject *parent = nullptr);
    void addTier(const QString &tierID, const QString &speakerID,
                 const QString &type, const QString &category,
                 const QString &displayName,
                 AnnotationTier *tierToExport);

    void exportPraalineToPartitur(ExmaraldaBasicTranscription &partitur);
    
signals:
    
public slots:
    
private:
    QList<TierToExportInfo > m_tiersToExport;
};

PRAALINE_CORE_END_NAMESPACE

#endif // EXMARALDATRANSCRIPTIONBRIDGE_H
