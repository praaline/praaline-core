#ifndef TEIHEADER_H
#define TEIHEADER_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QString>

#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Base/RealTime.h"
#include "PraalineCore/Interfaces/InterfaceTextFile.h"

class QXmlStreamReader;

PRAALINE_CORE_BEGIN_NAMESPACE

class Corpus;

class PRAALINE_CORE_SHARED_EXPORT TEIHeader : InterfaceTextFile
{
public:
    TEIHeader();

    class CatRef {
    public:
        QString target;
        QString corresp;
    };

    class ProfileDesc {
    public:
        QString abstract;
        QString langUsage;
        QList<CatRef> textClass;
    };

    ProfileDesc profileDesc;

    static bool load(const QString &filename, TEIHeader &teiHeader);

private:
    static bool readCatRef(QXmlStreamReader &xml, CatRef &catRef);
    static bool readProfileDesc(QXmlStreamReader &xml, ProfileDesc &profileDesc);

};

PRAALINE_CORE_END_NAMESPACE

#endif // TEIHEADER_H
