#ifndef CORPUSANNOTATION_H
#define CORPUSANNOTATION_H

/*
    Praaline - Core module - Corpus metadata
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

#include <QObject>
#include <QString>
#include <QStringList>
#include "PraalineCore/PraalineCore_Global.h"
#include "PraalineCore/Corpus/CorpusObject.h"

PRAALINE_CORE_BEGIN_NAMESPACE

class Corpus;

class PRAALINE_CORE_SHARED_EXPORT CorpusAnnotation : public CorpusObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged)
    Q_PROPERTY(QString format READ format WRITE setFormat NOTIFY formatChanged)
    Q_PROPERTY(QStringList languages READ languages NOTIFY languagesChanged)
    Q_PROPERTY(QString communicationID READ communicationID CONSTANT)

public:
    explicit CorpusAnnotation(CorpusRepository *repository = nullptr, QObject *parent = nullptr);
    explicit CorpusAnnotation(const QString ID, CorpusRepository *repository = nullptr, QObject *parent = nullptr);
    explicit CorpusAnnotation(CorpusAnnotation *other, QObject *parent = nullptr);
    ~CorpusAnnotation() override {}

    CorpusObject::Type type() const override { return CorpusObject::Type_Annotation; }
    bool save() override;

    QString communicationID() const;
    Corpus * corpus() const;

    QString name() const { return m_name; }
    void setName(const QString &name);

    QString recordingID() const { return m_recordingID; }
    void setRecordingID(const QString &recordingID);

    QString filename() const { return m_filename; }
    void setFilename(const QString &filename);

    QString format() const { return m_format; }
    void setFormat(const QString &format);

    bool isMultiLanguage() const;
    QStringList languages() const;
    void addLanguage(const QString &languageID);
    void removeLanguage(const QString &languageID);

signals:
    void nameChanged();
    void filenameChanged();
    void formatChanged();
    void languagesChanged();

private:
    QString m_name;
    QString m_recordingID;
    QString m_filename;
    QString m_format;
    QStringList m_languages;

    Q_DISABLE_COPY(CorpusAnnotation)
};

PRAALINE_CORE_END_NAMESPACE

#endif // CORPUSANNOTATION_H
