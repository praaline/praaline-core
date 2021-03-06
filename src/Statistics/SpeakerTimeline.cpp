#include <QObject>
#include <QPointer>
#include <QScopedPointer>

#include "PraalineCore/Corpus/CorpusCommunication.h"
#include "PraalineCore/Datastore/CorpusRepository.h"
#include "PraalineCore/Datastore/AnnotationDatastore.h"
#include "PraalineCore/Datastore/FileDatastore.h"
#include "PraalineCore/Annotation/IntervalTier.h"
#include "PraalineCore/Annotation/Interval.h"
#include "PraalineCore/Annotation/AnnotationTierGroup.h"
#include "PraalineCore/Interfaces/Praat/PraatTextGrid.h"
#include "PraalineCore/Statistics/SpeakerTimeline.h"

PRAALINE_CORE_BEGIN_NAMESPACE

struct SpeakerTimelineData {
    QString minimalLevelID;
    QPointer<IntervalTier> tier_timelineSyll;
    QPointer<IntervalTier> tier_timelineSpk;
};

SpeakerTimeline::SpeakerTimeline(QObject *parent) :
    QObject(parent), d(new SpeakerTimelineData)
{
}

SpeakerTimeline::~SpeakerTimeline()
{
    // timelines deleted as child objects
    delete d;
}

QString SpeakerTimeline::minimalLevelID() const
{
    return d->minimalLevelID;
}

IntervalTier *SpeakerTimeline::timelineDetailed() const
{
    return d->tier_timelineSyll;
}

IntervalTier *SpeakerTimeline::timelineCoarse() const
{
    return d->tier_timelineSpk;
}

bool SpeakerTimeline::calculate(CorpusCommunication * com, const QString &minimalLevelID)
{
    if (!com) return false;
    if (!com->repository()) return false;

    if (d->tier_timelineSyll) delete d->tier_timelineSyll;
    if (d->tier_timelineSpk) delete d->tier_timelineSpk;

    // A timeline on the syllable level with detailed = true means there will be an interval for each syllable
    // and possibly segmented syllables when two speakers overlap.
    d->tier_timelineSyll = com->repository()->annotations()->getSpeakerTimeline(com->ID(), "", minimalLevelID, true);
    if (!d->tier_timelineSyll) return false;
    d->tier_timelineSyll->setParent(this);

    // Exclude silence at the begining and end of recording
    int i = 0;
    while (i < d->tier_timelineSyll->count() && d->tier_timelineSyll->interval(i)->isPauseSilent()) {
        d->tier_timelineSyll->interval(i)->setAttribute("temporal", "X");
        i++;
    }
    i = d->tier_timelineSyll->count() - 1;
    while (i >= 0 && d->tier_timelineSyll->interval(i)->isPauseSilent()) {
        d->tier_timelineSyll->interval(i)->setAttribute("temporal", "X");
        i--;
    }

    // Create a timeline clone where regions of identical speakers are merged together
    d->tier_timelineSpk = d->tier_timelineSyll->clone();
    if (!d->tier_timelineSpk) return false;
    d->tier_timelineSpk->setParent(this);
    d->tier_timelineSpk->mergeIdenticalAnnotations();

    // Categorise intervals using an additional attribute on the timeline tier
    for (i = 0; i < d->tier_timelineSpk->count(); ++i) {
        Interval *intv = d->tier_timelineSpk->interval(i);
        if (intv->attribute("temporal").toString() == "X")
            continue; // excluded
        if (intv->isPauseSilent()) {
            QString speakerBeforePause, speakerAfterPause;
            if (i > 0) speakerBeforePause = d->tier_timelineSpk->interval(i - 1)->text();
            if (i < d->tier_timelineSpk->count() - 2) speakerAfterPause = d->tier_timelineSpk->interval(i + 1)->text();
            if (speakerAfterPause.contains(speakerBeforePause) && !speakerBeforePause.isEmpty() && !speakerAfterPause.isEmpty()) {
                intv->setText(speakerBeforePause); // silent pause belonging to the current speaker
                intv->setAttribute("temporal", "P");
            }
            else if (speakerBeforePause.isEmpty() || speakerAfterPause.isEmpty()) {
                intv->setAttribute("temporal", "X");
            } else {
                intv->setAttribute("temporal", "G");
            }
        }
        else {
            // One or many speakers speaking?
            if (intv->text().contains("+")) {
                // Detect overlaps with or without change of turn
                QString speakerBefore, speakerAfter;
                if (i > 0) speakerBefore = d->tier_timelineSpk->interval(i - 1)->text();
                if (i < d->tier_timelineSpk->count() - 2) speakerAfter = d->tier_timelineSpk->interval(i + 1)->text();
                if ((speakerBefore == speakerAfter) && (!speakerBefore.contains("+")) && (!speakerAfter.contains("+")))
                    intv->setAttribute("temporal", "OVC");
                else
                    intv->setAttribute("temporal", "OVT");
            } else {
                intv->setAttribute("temporal", "S");
            }
        }
        foreach (Interval *syllseg, d->tier_timelineSyll->getIntervalsContainedIn(intv)) {
            syllseg->setText(intv->text());
            syllseg->setAttribute("temporal", intv->attribute("temporal"));
        }
    }
    d->minimalLevelID = minimalLevelID;
    return true;
}

void debugCreateTimelineTextgrid(CorpusCommunication * com, const QString &minimalLevelID)
{
    if (!com) return;
    if (!com->repository()) return;

    SpeakerTimeline timeline;
    if (!timeline.calculate(com, minimalLevelID)) return;

    IntervalTier *tier_timelineSyll(timeline.timelineDetailed());
    IntervalTier *tier_timelineSpk(timeline.timelineCoarse());

    QString path = com->repository()->files()->basePath();
    QScopedPointer<AnnotationTierGroup> txg(new AnnotationTierGroup());
    foreach (CorpusAnnotation * annot, com->annotations()) {
        if (!annot) continue;
        QString annotationID = annot->ID();
        SpeakerAnnotationTierGroupMap tiersAll = com->repository()->annotations()->getTiersAllSpeakers(annotationID);
        foreach (QString speakerID, tiersAll.keys()) {
            AnnotationTierGroup *tiers = tiersAll.value(speakerID);
            if (!tiers) continue;
            IntervalTier *tier_syll = tiers->getIntervalTierByName("syll");
            IntervalTier *tier_tokmin = tiers->getIntervalTierByName("tok_min");
            txg->addTier(tier_syll->clone());
            txg->addTier(tier_tokmin->clone());
            // Turn
            IntervalTier *tier_turns = tier_timelineSpk->clone();
            foreach (Interval *intv, tier_turns->intervals()) {
                if (intv->text().contains(speakerID)) intv->setText(speakerID); else intv->setText("");
            }
            tier_turns->mergeIdenticalAnnotations();
            txg->addTier(tier_turns);
        }
        qDeleteAll(tiersAll);
    }
    txg->addTier(tier_timelineSyll);
    IntervalTier *tier_timelineSyllT = tier_timelineSyll->clone("timelineSyllT");
    foreach (Interval *intv, tier_timelineSyllT->intervals())
        intv->setText(intv->attribute("temporal").toString());
    txg->addTier(tier_timelineSyllT);
    txg->addTier(tier_timelineSpk);
    IntervalTier *tier_timelineSpkT = tier_timelineSpk->clone("timelineSpkT");
    foreach (Interval *intv, tier_timelineSpkT->intervals())
        intv->setText(intv->attribute("temporal").toString());
    txg->addTier(tier_timelineSpkT);

    PraatTextGrid::save(path + "/" + com->ID() + ".TextGrid", txg.data());
}

PRAALINE_CORE_END_NAMESPACE
