#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QRegularExpression>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "PraalineCore/Datastore/DatastoreInfo.h"
#include "PraalineCore/Datastore/CorpusRepositoryDefinition.h"

PRAALINE_CORE_BEGIN_NAMESPACE

CorpusRepositoryDefinition::CorpusRepositoryDefinition() :
    basePath(QString()), basePathMedia(QString()), useRelativeBasePathMedia(true)
{
}

CorpusRepositoryDefinition::~CorpusRepositoryDefinition()
{
}


bool CorpusRepositoryDefinition::save(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement("PraalineCorpusDefinition");
    xml.writeAttribute("ID", repositoryID);
    xml.writeAttribute("name", repositoryName);
    xml.writeStartElement("MetadataDatastore");
    xml.writeAttribute("type", infoDatastoreMetadata.typeToString());
    xml.writeAttribute("driver", infoDatastoreMetadata.driver);
    xml.writeAttribute("hostname", infoDatastoreMetadata.hostname);
    if (infoDatastoreMetadata.driver == "QSQLITE") {
        QFileInfo finfo(infoDatastoreMetadata.datasource);
        xml.writeAttribute("datasource", finfo.fileName());
    } else {
        xml.writeAttribute("datasource", infoDatastoreMetadata.datasource);
    }
    xml.writeAttribute("username", infoDatastoreMetadata.username);
    xml.writeAttribute("usepassword", (infoDatastoreMetadata.usePassword) ? "yes" : "no");
    xml.writeEndElement(); // MetadataDatastore
    xml.writeStartElement("AnnotationsDatastore");
    xml.writeAttribute("type", infoDatastoreAnnotations.typeToString());
    xml.writeAttribute("driver", infoDatastoreAnnotations.driver);
    xml.writeAttribute("hostname", infoDatastoreAnnotations.hostname);
    if (infoDatastoreAnnotations.driver == "QSQLITE") {
        QFileInfo finfo(infoDatastoreAnnotations.datasource);
        xml.writeAttribute("datasource", finfo.fileName());
    } else {
        xml.writeAttribute("datasource", infoDatastoreMetadata.datasource);
    }
    xml.writeAttribute("username", infoDatastoreAnnotations.username);
    xml.writeAttribute("usepassword", (infoDatastoreAnnotations.usePassword) ? "yes" : "no");
    xml.writeEndElement(); // AnnotationsDatastore
    xml.writeStartElement("MediaDatastore");
    if (useRelativeBasePathMedia) {
        QString relativeBasePathMedia = QDir(basePath).relativeFilePath(basePathMedia);
        xml.writeAttribute("baseMediaPath", relativeBasePathMedia);
    }
    else {
        xml.writeAttribute("baseMediaPath", basePathMedia);
    }
    xml.writeEndElement(); // MediaDatastore
    xml.writeEndElement(); // PraalineCorpusDefinition
    xml.writeEndDocument();
    file.close();
    this->filenameDefinition = filename;
    return true;
}

void readDatastoreInfo(QXmlStreamReader &xml, DatastoreInfo &info)
{
    if (xml.attributes().hasAttribute("type")) {
        QString type = xml.attributes().value("type").toString();
        info.setTypeFromString(type);
    }
    if (xml.attributes().hasAttribute("driver"))     info.driver = xml.attributes().value("driver").toString();
    if (xml.attributes().hasAttribute("hostname"))   info.hostname = xml.attributes().value("hostname").toString();
    if (xml.attributes().hasAttribute("datasource")) info.datasource = xml.attributes().value("datasource").toString();
    if (xml.attributes().hasAttribute("username"))   info.username = xml.attributes().value("username").toString();
    if (xml.attributes().hasAttribute("usepassword")) {
        if (xml.attributes().value("usepassword").toString() == "yes")
            info.usePassword = true;
        else
            info.usePassword = false;
    }
}

bool CorpusRepositoryDefinition::load(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
    QXmlStreamReader xml(&file);
    while (!xml.atEnd() && !xml.hasError()) {
        // If token is StartElement, we'll see if we can read it.
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == QLatin1String("PraalineCorpusDefinition")) {
            if (xml.attributes().hasAttribute("ID")) repositoryID = xml.attributes().value("ID").toString();
            if (xml.attributes().hasAttribute("name")) repositoryName = xml.attributes().value("name").toString();
            xml.readNext();
            while (!xml.atEnd() && !xml.hasError() &&
                   !(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == QLatin1String("PraalineCorpusDefinition"))) {
                if (xml.tokenType() == QXmlStreamReader::StartElement) {
                    if (xml.name() == QLatin1String("MetadataDatastore")) {
                        readDatastoreInfo(xml, infoDatastoreMetadata);
                    }
                    else if (xml.name() == QLatin1String("AnnotationsDatastore")) {
                        readDatastoreInfo(xml, infoDatastoreAnnotations);
                    }
                    else if (xml.name() == QLatin1String("MediaDatastore")) {
                        if (xml.attributes().hasAttribute("baseMediaPath"))
                            this->basePathMedia = xml.attributes().value("baseMediaPath").toString();
                    }
                }
                xml.readNext();
            }
        }
        xml.readNext(); // next element
    }
    // Error handling
    if(xml.hasError()) {
        file.close();
        return false;
    }
    // Removes any device() or data from the reader and resets its internal state to the initial state.
    xml.clear();
    file.close();

    // Set the filename of Repository Definition file, and set the base path to the absolute path of that file.
    this->filenameDefinition = filename;
    this->basePath = QFileInfo(filename).canonicalPath();
    // Set the media path.
    // If no specific media path is given, then it is the same as the base path (i.e. the path of the Repository
    // Definition file) and use relative path when saving.
    if (this->basePathMedia.isEmpty()) {
        this->basePathMedia = this->basePath;
        useRelativeBasePathMedia = true;
    }
    else {
        // If however, a specific media path is given, then check if it relative or absolute.
        // If it is given as a relative path, then the convert it to an absolute path, relative to the base path.
        if (QDir::isRelativePath(this->basePathMedia)) {
            this->basePathMedia = QDir(this->basePath + "/" + this->basePathMedia).absolutePath();
            useRelativeBasePathMedia = true;
        }
        else {
            useRelativeBasePathMedia = false;
        }
    }
    // Adjust to open correctly SQLite databases
    if (this->infoDatastoreMetadata.driver == "QSQLITE")
        this->infoDatastoreMetadata.datasource = this->basePath + "/" + this->infoDatastoreMetadata.datasource;
    if (this->infoDatastoreAnnotations.driver == "QSQLITE")
        this->infoDatastoreAnnotations.datasource = this->basePath + "/" + this->infoDatastoreAnnotations.datasource;

    return true;
}

PRAALINE_CORE_END_NAMESPACE
