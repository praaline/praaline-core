#ifndef PRAATTEXTGRID_H
#define PRAATTEXTGRID_H

#include <QObject>
#include <QString>
#include <QList>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Base/RealTime.h"
#include "PraalineCore/Annotation/AnnotationTierGroup.h"
#include "PraalineCore/Annotation/AnnotationTier.h"
#include "PraalineCore/Annotation/IntervalTier.h"
#include "PraalineCore/Annotation/PointTier.h"
#include "PraalineCore/Interfaces/Praat/PraatTextFile.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class PRAALINE_CORE_SHARED_EXPORT PraatTierData
{
public:
    QString name;
    QString type;
    int itemsCount;
};

class PRAALINE_CORE_SHARED_EXPORT PraatTextGrid : PraatTextFile
{
public:
    // Public static methods to read and write textgrids
    static bool load(const QString &filename, AnnotationTierGroup *data);
    static bool save(const QString &filename, AnnotationTierGroup *data);

    static QList<PraatTierData> getTierData(const QString &filename);

protected:
    PraatTextGrid();
    virtual ~PraatTextGrid();

    // IO Functions
    static bool readTierHeader(bool isShortFile, QTextStream &stream, QString &line,
                               int &tierType, int &tierSize, QString &name, double &xMin, double &xMax);
    static bool readInterval(bool isShortFile, QTextStream &stream, QString &line,
                             double &xMin, double &xMax, QString &text);
    static bool readPoint(bool isShortFile, QTextStream &stream, QString &line,
                          double &timePoint, QString &text);

private:
    static QRegularExpression regex_interval_tier;
    static QRegularExpression regex_point_tier;
    static QRegularExpression regex_name;
    static QRegularExpression regex_size;
    static QRegularExpression regex_xmin;
    static QRegularExpression regex_xmax;
    static QRegularExpression regex_interval;
    static QRegularExpression regex_point;
    static QRegularExpression regex_text;
    static QRegularExpression regex_time;
    static QRegularExpression regex_mark;

    static QRegularExpression regex_short_interval_tier;
    static QRegularExpression regex_short_point_tier;
    static QRegularExpression regex_short_name;
    static QRegularExpression regex_short_size;
    static QRegularExpression regex_short_xmin;
    static QRegularExpression regex_short_xmax;
    static QRegularExpression regex_short_text;
    static QRegularExpression regex_short_time;
    static QRegularExpression regex_short_mark;
};

PRAALINE_CORE_END_NAMESPACE

#endif // PRAATTEXTGRID_H
