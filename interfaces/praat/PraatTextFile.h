#ifndef PRAATTEXTFILE_H
#define PRAATTEXTFILE_H

#include "pncore_global.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include "interfaces/InterfaceTextFile.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT PraatTextFile : InterfaceTextFile
{
protected:
    PraatTextFile() {}
    virtual ~PraatTextFile() {}

    static void detectEncoding(QFile &file, QTextStream &stream);
    static QString seekPattern(QTextStream &stream, const QRegularExpression &regex);
};

PRAALINE_CORE_END_NAMESPACE

#endif // PRAATTEXTFILE_H
