#ifndef SUBTITLESFILE_H
#define SUBTITLESFILE_H

#include <QString>

#include "praaline-core_global.h"
#include "interfaces/InterfaceTextFile.h"
#include "annotation/IntervalTier.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT SubtitlesFile : InterfaceTextFile
{

public:
    // Public static methods to read and write SRT files
    static bool loadSRT(const QString &filename, IntervalTier *tier, const QString &attributeID = QString());
    static bool saveSRT(const QString &filename, IntervalTier *tier, const QString &attributeID = QString());
};

PRAALINE_CORE_END_NAMESPACE

#endif // SUBTITLESFILE_H
