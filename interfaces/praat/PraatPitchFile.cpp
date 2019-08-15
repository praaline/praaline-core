#include <QRegularExpression>
#include "PraatPitchFile.h"

PRAALINE_CORE_BEGIN_NAMESPACE

// Initialise regular expressions
// Regular Expressions for:
// text = integer       text\\s+=\\s+(\\d*)
// text = double        text\\s+=\\s+[+-]?(\\d+\\.?\\d*)
// array_element [i]:   array_element\\s+\\[\\d*\\]:

QRegularExpression PraatPitchFile::regex_xmin           = QRegularExpression("xmin\\s+=\\s+[+-]?(\\d+\\.?\\d*)");
QRegularExpression PraatPitchFile::regex_xmax           = QRegularExpression("xmax\\s+=\\s+[+-]?(\\d+\\.?\\d*)");
QRegularExpression PraatPitchFile::regex_nx             = QRegularExpression("nx\\s+=\\s+(\\d*)");
QRegularExpression PraatPitchFile::regex_dx             = QRegularExpression("dx\\s+=\\s+[+-]?(\\d+\\.?\\d*)");
QRegularExpression PraatPitchFile::regex_x1             = QRegularExpression("x1\\s+=\\s+[+-]?(\\d+\\.?\\d*)");
QRegularExpression PraatPitchFile::regex_ceiling        = QRegularExpression("ceiling\\s+=\\s+[+-]?(\\d+\\.?\\d*)");
QRegularExpression PraatPitchFile::regex_maxnCandidates = QRegularExpression("maxnCandidates\\s+=\\s+(\\d*)");
QRegularExpression PraatPitchFile::regex_frame          = QRegularExpression("frame\\s+\\[\\d*\\]:");
QRegularExpression PraatPitchFile::regex_intensity      = QRegularExpression("intensity\\s+=\\s+[+-]?(\\d+\\.?\\d*)");
QRegularExpression PraatPitchFile::regex_nCandidates    = QRegularExpression("nCandidates\\s+=\\s+(\\d*)");
QRegularExpression PraatPitchFile::regex_candidate      = QRegularExpression("candidate\\s+\\[\\d*\\]:");
QRegularExpression PraatPitchFile::regex_frequency      = QRegularExpression("frequency\\s+=\\s+[+-]?(\\d+\\.?\\d*)");
QRegularExpression PraatPitchFile::regex_strength       = QRegularExpression("strength\\s+=\\s+[+-]?(\\d+\\.?\\d*)");

QRegularExpression PraatPitchFile::regex_short_xmin           = QRegularExpression("[+-]?(\\d+\\.?\\d*)");
QRegularExpression PraatPitchFile::regex_short_xmax           = QRegularExpression("[+-]?(\\d+\\.?\\d*)");
QRegularExpression PraatPitchFile::regex_short_nx             = QRegularExpression("(\\d*)");
QRegularExpression PraatPitchFile::regex_short_dx             = QRegularExpression("[+-]?(\\d+\\.?\\d*)");
QRegularExpression PraatPitchFile::regex_short_x1             = QRegularExpression("[+-]?(\\d+\\.?\\d*)");
QRegularExpression PraatPitchFile::regex_short_ceiling        = QRegularExpression("[+-]?(\\d+\\.?\\d*)");
QRegularExpression PraatPitchFile::regex_short_maxnCandidates = QRegularExpression("(\\d*)");
QRegularExpression PraatPitchFile::regex_short_intensity      = QRegularExpression("[+-]?(\\d+\\.?\\d*)");
QRegularExpression PraatPitchFile::regex_short_nCandidates    = QRegularExpression("(\\d*)");
QRegularExpression PraatPitchFile::regex_short_frequency      = QRegularExpression("[+-]?(\\d+\\.?\\d*)");
QRegularExpression PraatPitchFile::regex_short_strength       = QRegularExpression("[+-]?(\\d+\\.?\\d*)");

PraatPitchFile::PraatPitchFile()
{

}

bool PraatPitchFile::readCandidate(bool isShortFile, QTextStream &stream, QString &line, PraatPitchCandidate &candidate)
{
    QString result;
    if (isShortFile || (regex_candidate.match(line).hasMatch())) {
        result = seekPattern(stream, (isShortFile) ? regex_short_frequency : regex_frequency);
        candidate.frequency = result.toDouble();
        result = seekPattern(stream, (isShortFile) ? regex_short_strength : regex_strength);
        candidate.strength = result.toDouble();
        return true;
    }
    // else
    return false;
}

bool PraatPitchFile::readFrame(bool isShortFile, QTextStream &stream, QString &line, PraatPitchFrame &frame)
{
    QString result;
    if (isShortFile || (regex_frame.match(line).hasMatch())) {
        result = seekPattern(stream, (isShortFile) ? regex_short_intensity : regex_intensity);
        frame.intensity = result.toDouble();
        result = seekPattern(stream, (isShortFile) ? regex_short_nCandidates : regex_nCandidates);
        int nCandidates = result.toInt();
        if (isShortFile) {
            for (int i = 0; i < nCandidates; i++) {
                line = stream.readLine(); // move to next line
                PraatPitchCandidate candidate;
                if (readCandidate(isShortFile, stream, line, candidate))
                    frame.candidates << candidate;
                else return false;
            }
        } else {
            do {
                line = stream.readLine();
                PraatPitchCandidate candidate;
                if (readCandidate(isShortFile, stream, line, candidate))
                    frame.candidates << candidate;
            } while ((!stream.atEnd()) && (frame.candidates.count() < nCandidates));
        }
        return true;
    }
    // else
    return false;
}

bool PraatPitchFile::readHeader(bool isShortFile, QTextStream &stream, QString &line, PraatPitch &pitch)
{
    QString result;
    // The line must be at the beginning of the header
    if (!((isShortFile) ? regex_short_xmin : regex_xmin).match(line).hasMatch())
        return false;
    result = ((isShortFile) ? regex_short_xmin : regex_xmin).match(line).captured(1);
    pitch.tmin = RealTime::fromSeconds(result.toDouble());
    result = seekPattern(stream, (isShortFile) ? regex_short_xmax : regex_xmax);
    pitch.tmax = RealTime::fromSeconds(result.toDouble());
    result = seekPattern(stream, (isShortFile) ? regex_short_nx : regex_nx);
    pitch.nx = result.toLong();
    result = seekPattern(stream, (isShortFile) ? regex_short_dx : regex_dx);
    pitch.dx = RealTime::fromSeconds(result.toDouble());
    result = seekPattern(stream, (isShortFile) ? regex_short_x1 : regex_x1);
    pitch.tstart = RealTime::fromSeconds(result.toDouble());
    result = seekPattern(stream, (isShortFile) ? regex_short_ceiling : regex_ceiling);
    pitch.ceiling = result.toInt();
    result = seekPattern(stream, (isShortFile) ? regex_short_maxnCandidates : regex_maxnCandidates);
    pitch.maxnCandidates = result.toInt();
    return true;
}

bool PraatPitchFile::load(const QString &filename, PraatPitch &data)
{
    QFile file(filename);
    QString line, result;
    // Open file, create stream, detect encoding
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    QTextStream stream(&file);
    detectEncoding(file, stream);
    // Check file type on header
    bool isTextFile(false), isPitchFile(false), isShortFile(false);
    while (!stream.atEnd()) {
        line = stream.readLine();
        if (line.contains("File type = \"ooTextFile")) isTextFile = true;
        if (line.contains("Object class = \"Pitch 1")) isPitchFile = true;
        if (isTextFile && isPitchFile) break;
    }
    if ((!isTextFile) || (!isPitchFile)) return false;
    // Move to next line, and skip empty lines
    line = stream.readLine();
    while (!stream.atEnd() && line.isEmpty())
        line = stream.readLine();
    // First line: if it starts with "xmin" it is a verbose text file, otherwise a short file
    if (regex_xmin.match(line).hasMatch())
        isShortFile = false;
    else if (regex_short_xmin.match(line).hasMatch())
        isShortFile = true;
    else return false;
    // Process header
    if (!readHeader(isShortFile, stream, line, data)) return false;
    // Process file
    if (isShortFile) {
        for (int i = 0; i < data.nx; i++) {
            line = stream.readLine(); // move to next line
            PraatPitchFrame frame;
            if (readFrame(isShortFile, stream, line, frame))
                data.frames << frame;
            else return false;
        }
    }
    else {
        do {
            line = stream.readLine();
            PraatPitchFrame frame;
            if (readFrame(isShortFile, stream, line, frame))
                data.frames << frame;
        } while (!stream.atEnd());
    }
    return true;
}

bool PraatPitchFile::save(const QString &filename, PraatPitch &data)
{
    Q_UNUSED(filename)
    Q_UNUSED(data)
    return false;
}

PRAALINE_CORE_END_NAMESPACE
