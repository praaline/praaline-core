#ifndef INTERFACETEXTFILE_H
#define INTERFACETEXTFILE_H

#include <QString>
#include <QFile>
#include <QTextStream>

#include "PraalineCore/PraalineCore_Global.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT InterfaceTextFile
{
public:
    static void setDefaultEncoding(const QString &encoding);
    static QString defaultEncoding();

protected:
    InterfaceTextFile();
    ~InterfaceTextFile();
    static void detectEncoding(QFile &file, QTextStream &stream);

private:
    static QString m_defaultEncoding;
};

PRAALINE_CORE_END_NAMESPACE

#endif // INTERFACETEXTFILE_H
