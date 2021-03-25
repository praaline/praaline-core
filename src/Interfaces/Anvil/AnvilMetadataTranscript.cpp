#include <QDebug>
#include <QXmlStreamReader>

#include "PraalineCore/Corpus/Corpus.h"
#include "PraalineCore/Interfaces/Anvil/AnvilMetadataTranscript.h"

PRAALINE_CORE_BEGIN_NAMESPACE

QString AnvilMetadataTranscript::xmlElementName_Location("Location");
QString AnvilMetadataTranscript::xmlElementName_Contact("Contact");
QString AnvilMetadataTranscript::xmlElementName_Project("Project");
QString AnvilMetadataTranscript::xmlElementName_Content("Content");
QString AnvilMetadataTranscript::xmlElementName_Actor("Actor");
QString AnvilMetadataTranscript::xmlElementName_MediaFileResource("MediaFile");
QString AnvilMetadataTranscript::xmlElementName_WrittenResource("WrittenResource");
QString AnvilMetadataTranscript::xmlElementName_Resources("Resources");
QString AnvilMetadataTranscript::xmlElementName_Actors("Actors");
QString AnvilMetadataTranscript::xmlElementName_MDGroup("MDGroup");
QString AnvilMetadataTranscript::xmlElementName_Session("Session");

AnvilMetadataTranscript::AnvilMetadataTranscript()
{
}

// private static
AnvilMetadataTranscript::LocationData *
AnvilMetadataTranscript::readLocation(QXmlStreamReader &xml)
{
    if ((xml.tokenType() != QXmlStreamReader::StartElement) || (xml.name() != xmlElementName_Location)) return nullptr;
    LocationData *location = new LocationData();
    xml.readNext();
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == xmlElementName_Location) && !xml.atEnd()) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if      (xml.name() == QLatin1String("Continent"))  { location->continent = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Country"))    { location->country = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Region"))     { location->region = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Address"))    { location->address = xml.readElementText(); }
        }
        xml.readNext();
    }
    return location;
}

// private static
AnvilMetadataTranscript::ContactData *
AnvilMetadataTranscript::readContact(QXmlStreamReader &xml)
{
    if ((xml.tokenType() != QXmlStreamReader::StartElement) || (xml.name() != xmlElementName_Contact)) return nullptr;
    ContactData *contact = new ContactData();
    xml.readNext();
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == xmlElementName_Contact) && !xml.atEnd()) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if      (xml.name() == QLatin1String("Name"))          { contact->name = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Address"))       { contact->address = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Email"))         { contact->email = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Organisation"))  { contact->organisation = xml.readElementText(); }
        }
        xml.readNext();
    }
    return contact;
}

// private static
AnvilMetadataTranscript::ProjectData *
AnvilMetadataTranscript::readProject(QXmlStreamReader &xml)
{
    if ((xml.tokenType() != QXmlStreamReader::StartElement) || (xml.name() != xmlElementName_Project)) return nullptr;
    ProjectData *project = new ProjectData();
    xml.readNext();
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == xmlElementName_Project) && !xml.atEnd()) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if      (xml.name() == QLatin1String("Name"))        { project->name = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Title"))       { project->title = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Id"))          { project->id = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Description")) { project->description = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Contact")) {
                ContactData *contact = readContact(xml);
                if (contact) project->contacts << contact;
            }
        }
        xml.readNext();
    }
    return project;
}

// private static
AnvilMetadataTranscript::ContentData *
AnvilMetadataTranscript::readContent(QXmlStreamReader &xml)
{
    if ((xml.tokenType() != QXmlStreamReader::StartElement) || (xml.name() != xmlElementName_Content)) return nullptr;
    ContentData *content = new ContentData();
    xml.readNext();
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == xmlElementName_Content) && !xml.atEnd()) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if      (xml.name() == QLatin1String("Genre"))          { content->genre = xml.readElementText(); }
            else if (xml.name() == QLatin1String("SubGenre"))       { content->subGenres = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Task"))           { content->task = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Modalities"))     { content->modalities = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Subject"))        { content->subjects = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Interactivity"))  { content->interactivity = xml.readElementText(); }
            else if (xml.name() == QLatin1String("PlanningType"))   { content->planning = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Involvement"))    { content->involvement = xml.readElementText(); }
            else if (xml.name() == QLatin1String("SocialContext"))  { content->socialContext = xml.readElementText(); }
            else if (xml.name() == QLatin1String("EventStructure")) { content->eventStructure = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Channel"))        { content->channel = xml.readElementText(); }
        }
        xml.readNext();
    }
    return content;
}

// private static
AnvilMetadataTranscript::ActorData *
AnvilMetadataTranscript::readActor(QXmlStreamReader &xml)
{
    if ((xml.tokenType() != QXmlStreamReader::StartElement) || (xml.name() != xmlElementName_Actor)) return nullptr;
    ActorData *actor = new ActorData();
    xml.readNext();
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == xmlElementName_Actor) && !xml.atEnd()) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if      (xml.name() == QLatin1String("Role"))              { actor->role = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Name"))              { actor->name = xml.readElementText(); }
            else if (xml.name() == QLatin1String("FullName"))          { actor->fullName = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Code"))              { actor->code = xml.readElementText(); }
            else if (xml.name() == QLatin1String("FamilySocialRole"))  { actor->familySocialRole = xml.readElementText(); }
            else if (xml.name() == QLatin1String("EthnicGroup"))       { actor->ethnicGroup = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Age"))               { actor->age = xml.readElementText().toInt(); }
            else if (xml.name() == QLatin1String("BirthDate"))         { actor->birthDate = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Sex"))               { actor->sex = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Education"))         { actor->education = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Anonymized"))        { actor->anonymized = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Contact"))           { ContactData *contact = readContact(xml);
                QStringList contactData; contactData << contact->name << contact->organisation << contact->address << contact->email;
                actor->contact = contactData.join(", ");
            }
            else if (xml.name() == QLatin1String("Description"))       { actor->description = xml.readElementText(); }
        }
        xml.readNext();
    }
    return actor;
}

// private static
AnvilMetadataTranscript::MediaFileResourceData *
AnvilMetadataTranscript::readMediaFileResource(QXmlStreamReader &xml)
{
    xml.readNext();
    return nullptr;
}

// private static
AnvilMetadataTranscript::WrittenResourceData *
AnvilMetadataTranscript::readWrittenResource(QXmlStreamReader &xml)
{
    xml.readNext();
    return nullptr;
}

// private static
AnvilMetadataTranscript::SessionData *
AnvilMetadataTranscript::readSession(QXmlStreamReader &xml)
{
    if ((xml.tokenType() != QXmlStreamReader::StartElement) || (xml.name() != xmlElementName_Session)) return nullptr;
    SessionData *session = new SessionData();
    xml.readNext();
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == xmlElementName_Session) && !xml.atEnd()) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if      (xml.name() == QLatin1String("Name"))           { session->name = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Title"))          { session->title = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Date"))           { session->date = xml.readElementText(); }
            else if (xml.name() == QLatin1String("Descripiton"))    { session->description = xml.readElementText(); }
            else if (xml.name() == xmlElementName_MDGroup) {
                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == xmlElementName_MDGroup) && !xml.atEnd()) {
                    if (xml.tokenType() == QXmlStreamReader::StartElement) {
                        if (xml.name() == xmlElementName_Location) {
                            LocationData *location = readLocation(xml);
                            if (location) session->locations << location;
                        }
                        else if (xml.name() == xmlElementName_Project) {
                            ProjectData *project = readProject(xml);
                            if (project) session->projects << project;
                        }
                        else if (xml.name() == xmlElementName_Content) {
                             ContentData *content = readContent(xml);
                            if (content) session->contents << content;
                        }
                        else if (xml.name() == xmlElementName_Actors) {
                            xml.readNext();
                            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == xmlElementName_Actors) && !xml.atEnd()) {
                                if (xml.tokenType() == QXmlStreamReader::StartElement) {
                                    if (xml.name() == xmlElementName_Actor) {
                                        ActorData *actor = readActor(xml);
                                        if (actor) session->actors << actor;
                                    }
                                }
                                xml.readNext();
                            }
                        } // Actors
                    }
                    xml.readNext();
                }
            } // /MDGroup
            else if (xml.name() == xmlElementName_Resources) {
                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == xmlElementName_Resources) && !xml.atEnd()) {
                    if (xml.tokenType() == QXmlStreamReader::StartElement) {

                    }
                    xml.readNext();
                }
            } // /Resources
        }
        xml.readNext();
    }
    return session;
}

// static
bool AnvilMetadataTranscript::load(const QString &filename, Corpus *corpus)
{
    SessionData *session = nullptr;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
    QXmlStreamReader xml(&file);
    while (!xml.atEnd() && !xml.hasError()) {
        // If token is StartElement, we'll see if we can read it.
        if (xml.tokenType() == QXmlStreamReader::StartElement && xml.name() == QLatin1String("Session")) {
            session = readSession(xml);
            file.close();
        }
        xml.readNext(); // next element
    }
    // Removes any device() or data from the reader and resets its internal state to the initial state.
    xml.clear();
    file.close();

    // Update / create corpus items
    if (!session) return false;
    QString communicationID = QString(session->name).remove("-meta");
    CorpusCommunication * com = corpus->communication(communicationID);
    if (!com) return false;
    com->setProperty("title", session->title);
    com->setProperty("dateRecorded", session->date);
    com->setProperty("description", session->description);
    foreach (ContentData *content, session->contents) {
        com->setProperty("genre", content->genre);
        com->setProperty("subgenres", content->subGenres);
        com->setProperty("task", content->task);
        com->setProperty("modalities", content->modalities);
        com->setProperty("subjects", content->subjects);
        com->setProperty("interactivity", content->interactivity);
        com->setProperty("planning", content->planning);
        com->setProperty("involvement", content->involvement);
        com->setProperty("socialContext", content->socialContext);
        com->setProperty("eventStructure", content->eventStructure);
        com->setProperty("channel", content->channel);
    }
    int i = 1;
    foreach (ActorData *actor, session->actors) {
        QString speakerID = QString("%1_$L%2").arg(communicationID).arg(i);
        i++;
        CorpusSpeaker * spk = corpus->speaker(speakerID);
        if (!spk) continue;
        spk->setProperty("age", actor->age);
        spk->setProperty("anonymized", actor->anonymized);
        spk->setProperty("birthDate", actor->birthDate);
        spk->setProperty("code", actor->code);
        spk->setProperty("contact", actor->contact);
        spk->setProperty("description", actor->description);
        spk->setProperty("education", actor->education);
        spk->setProperty("ethnicGroup", actor->ethnicGroup);
        spk->setProperty("familySocialRole", actor->familySocialRole);
        spk->setProperty("fullName", actor->fullName);
        spk->setProperty("name", actor->name);
        spk->setProperty("sex", actor->sex);

        CorpusParticipation * participation = corpus->participation(communicationID, speakerID);
        if (participation) {
            participation->setProperty("role", actor->role);
        }
    }

    return true;
}

// static
bool AnvilMetadataTranscript::save(const QString &filename, Corpus *corpus)
{
    Q_UNUSED(filename)
    Q_UNUSED(corpus)
    return false;
}

PRAALINE_CORE_END_NAMESPACE
