#ifndef PRAATPITCHFILE_H
#define PRAATPITCHFILE_H

#include "pncore_global.h"
#include <QObject>
#include <QString>
#include <QList>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include "base/RealTime.h"
#include "PraatTextFile.h"

namespace Praaline {
namespace Core {

class PRAALINE_CORE_SHARED_EXPORT PraatPitchCandidate
{
public:
    PraatPitchCandidate() :
        frequency(0.0), strength(0.0)
    {}

    double frequency;
    double strength;
};

class PRAALINE_CORE_SHARED_EXPORT PraatPitchFrame
{
public:
    PraatPitchFrame() :
        intensity(0.0)
    {}

    double intensity;
    QList<PraatPitchCandidate> candidates;
};

class PRAALINE_CORE_SHARED_EXPORT PraatPitch
{
public:
    PraatPitch() :
        tmin(RealTime::zeroTime), tmax(RealTime::zeroTime), nx(0), dx(RealTime::zeroTime),
        tstart(RealTime::zeroTime), ceiling(0), maxnCandidates(0)
    {}

    RealTime tmin;
    RealTime tmax;
    long nx;
    RealTime dx;
    RealTime tstart;
    int ceiling;
    int maxnCandidates;
    QList<PraatPitchFrame> frames;
};

class PraatPitchFile : public PraatTextFile
{
public:
    PraatPitchFile();

    static bool load(const QString &filename, PraatPitch &data);
    static bool save(const QString &filename, PraatPitch &data);

protected:
    static bool readCandidate(bool isShortFile, QTextStream &stream, QString &line, PraatPitchCandidate &candidate);
    static bool readFrame(bool isShortFile, QTextStream &stream, QString &line, PraatPitchFrame &frame);
    static bool readHeader(bool isShortFile, QTextStream &stream, QString &line, PraatPitch &pitch);

private:
    static QRegularExpression regex_xmin;
    static QRegularExpression regex_xmax;
    static QRegularExpression regex_nx;
    static QRegularExpression regex_dx;
    static QRegularExpression regex_x1;
    static QRegularExpression regex_ceiling;
    static QRegularExpression regex_maxnCandidates;
    static QRegularExpression regex_frame;
    static QRegularExpression regex_intensity;
    static QRegularExpression regex_nCandidates;
    static QRegularExpression regex_candidate;
    static QRegularExpression regex_frequency;
    static QRegularExpression regex_strength;
    static QRegularExpression regex_short_xmin;
    static QRegularExpression regex_short_xmax;
    static QRegularExpression regex_short_nx;
    static QRegularExpression regex_short_dx;
    static QRegularExpression regex_short_x1;
    static QRegularExpression regex_short_ceiling;
    static QRegularExpression regex_short_maxnCandidates;
    static QRegularExpression regex_short_intensity;
    static QRegularExpression regex_short_nCandidates;
    static QRegularExpression regex_short_frequency;
    static QRegularExpression regex_short_strength;
};

} // namespace Core
} // namespace Praaline

#endif // PRAATPITCHFILE_H
