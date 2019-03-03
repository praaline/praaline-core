#ifndef TEIHEADER_H
#define TEIHEADER_H

#include "pncore_global.h"
#include <QObject>
#include <QPointer>
#include <QList>
#include <QMap>
#include <QString>
#include "base/RealTime.h"
#include "interfaces/InterfaceTextFile.h"

class QXmlStreamReader;

namespace Praaline {
namespace Core {

class Corpus;

class PRAALINE_CORE_SHARED_EXPORT TEIHeader : InterfaceTextFile
{
public:
    TEIHeader();

};

} // namespace Core
} // namespace Praaline

#endif // TEIHEADER_H
