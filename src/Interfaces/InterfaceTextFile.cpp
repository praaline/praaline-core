#include <QString>
#include <QByteArray>
#include <QTextStream>

#if QT_VERSION >= 0x060000
#include <QStringConverter>
#endif

#include "PraalineCore/Interfaces/InterfaceTextFile.h"

PRAALINE_CORE_BEGIN_NAMESPACE

// QString InterfaceTextFile::m_defaultEncoding = "UTF-8";
// or
QString InterfaceTextFile::m_defaultEncoding = "ISO 8859-1";

InterfaceTextFile::InterfaceTextFile()
{
}

InterfaceTextFile::~InterfaceTextFile()
{
}

void InterfaceTextFile::setDefaultEncoding(const QString &encoding)
{
    m_defaultEncoding = encoding;
}

QString InterfaceTextFile::defaultEncoding()
{
    return m_defaultEncoding;
}

void InterfaceTextFile::detectEncoding(QFile &file, QTextStream &stream)
{
    // Encoding detection
    QByteArray fileHeaderHex = file.peek(4).toHex();
    char *fileHeaderChar = fileHeaderHex.data();
    QString fileBOM;
    for(int i = 0; i < fileHeaderHex.size(); i++) {
        fileBOM += fileHeaderChar[i];
    }
    stream.setAutoDetectUnicode(true);
    if(fileBOM.left(6) == "efbbbf") {
        #if QT_VERSION >= 0x060000
        stream.setEncoding(QStringConverter::Utf8);
        #else
        stream.setCodec("UTF-8");
        #endif
    }
    else if(fileBOM.left(4) == "feff") {
        #if QT_VERSION >= 0x060000
        stream.setEncoding(QStringConverter::Utf16BE);
        #else
        stream.setCodec("UTF-16BE");
        #endif
    }
    else if(fileBOM.left(4) == "fffe") {
        #if QT_VERSION >= 0x060000
        stream.setEncoding(QStringConverter::Utf16LE);
        #else
        stream.setCodec("UTF-16LE");
        #endif
    }
    else if(fileBOM.left(8) == "0000feff") {
        #if QT_VERSION >= 0x060000
        stream.setEncoding(QStringConverter::Utf32BE);
        #else
        stream.setCodec("UTF-32BE");
        #endif
    }
    else if(fileBOM.left(8) == "fffe0000") {
        #if QT_VERSION >= 0x060000
        stream.setEncoding(QStringConverter::Utf32LE);
        #else
        stream.setCodec("UTF-32LE");
        #endif
    }
    else {
        #if QT_VERSION >= 0x060000
        stream.setEncoding(QStringConverter::Latin1);
        #else
        stream.setCodec(m_defaultEncoding.toLatin1().constData());
        #endif
    }
}

PRAALINE_CORE_END_NAMESPACE
