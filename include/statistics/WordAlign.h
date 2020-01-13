#ifndef WORDALIGN_H
#define WORDALIGN_H

/*
    Praaline - Core module - Statistics
    Copyright (c) 2011-2020 George Christodoulides

    This program or module is free software: you can redistribute it
    and/or modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version. It is provided
    for educational purposes and is distributed in the hope that it will
    be useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
    the GNU General Public License for more details.
*/

#include <QString>
#include <QList>
#include "praaline-core_global.h"

PRAALINE_CORE_BEGIN_NAMESPACE

struct WordAlignData;

class PRAALINE_CORE_SHARED_EXPORT WordAlign
{
public:
    class AlignmentItem {
    public:
        QString ref;
        QString hyp;
        QString op;
    };

    WordAlign();
    ~WordAlign();

    void align(QList<QString> wordsReference, QList<QString> wordsHypothesis);

    QList<AlignmentItem> alignment() const;
    QString alignmentText() const;
    QString alignmentTextOriginal(const QString &format) const;
    QString alignmentTextModified(const QString &format) const;

    double WER() const;
    int insertionsCount() const;
    int deletionsCount() const;
    int substitutionsCount() const;
    int matchesCount() const;
    int wordsReferenceCount() const;
    int wordsHypothesisCount() const;

private:
    void initialise();
    void backtrace();

    WordAlignData *d;
};

PRAALINE_CORE_END_NAMESPACE

#endif // WORDALIGN_H
