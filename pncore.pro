# Praaline Core Library
# (c) George Christodoulides 2012-2017

! include( ../common.pri ) {
    ! include( ./pncore-common.pri ) {
        error( Could not find the common.pri file! )
    }
}

TEMPLATE = lib

CONFIG(debug, debug|release) {
    TARGET = pncored
} else {
    TARGET = pncore
}

CONFIG += qt thread warn_on stl rtti exceptions c++11

QT += xml sql
QT -= gui

DEFINES += PRAALINE_CORE_LIBRARY
DEFINES += USE_PRAALINE_CORE_NAMESPACE

INCLUDEPATH += . ..
DEPENDPATH += . ..

HEADERS += \
    annotation/AnnotationDataTable.h \
    annotation/AnnotationElement.h \
    annotation/AnnotationTier.h \
    annotation/AnnotationTierGroup.h \
    annotation/Interval.h \
    annotation/IntervalTier.h \
    annotation/Point.h \
    annotation/PointTier.h \
    annotation/Relation.h \
    annotation/RelationTier.h \
    annotation/Sequence.h \
    annotation/SequenceTier.h \
    annotation/Transcription.h \
    annotation/TreeTier.h \
    base/BaseTypes.h \
    base/DataType.h \
    base/IDatastore.h \
    base/ISaveable.h \
    base/RealTime.h \
    base/RealValueList.h \
    corpus/Corpus.h \
    corpus/CorpusAnnotation.h \
    corpus/CorpusBookmark.h \
    corpus/CorpusCommunication.h \
    corpus/CorpusObject.h \
    corpus/CorpusObjectInfo.h \
    corpus/CorpusParticipation.h \
    corpus/CorpusRecording.h \
    corpus/CorpusSpeaker.h \
    dataframe/DataFrame.h \
    datastore/AnnotationDatastore.h \
    datastore/CorpusDatastore.h \
    datastore/CorpusRepository.h \
    datastore/CorpusRepositoryDefinition.h \
    datastore/DatastoreFactory.h \
    datastore/DatastoreInfo.h \
    datastore/FileDatastore.h \
    datastore/MetadataDatastore.h \
    datastore/NameValueListDatastore.h \
    datastore/SQLAnnotationDatastore.h \
    datastore/SQLMetadataDatastore.h \
    datastore/XMLAnnotationDatastore.h \
    datastore/XMLMetadataDatastore.h \
    diff/DiffIntervals.h \
    diff/DiffPoints.h \
    diff/dtl/diff.h \
    diff/dtl/diff3.h \
    diff/dtl/dtl.h \
    diff/dtl/functors.h \
    diff/dtl/lcs.h \
    diff/dtl/sequence.h \
    diff/dtl/ses.h \
    diff/dtl/variables.h \
    interfaces/anvil/AnvilMetadataTranscript.h \
    interfaces/conll/CoNLLXDocument.h \
    interfaces/csv/CSVFileAnnotation.h \
    interfaces/exmaralda/ExmaraldaBasicTranscription.h \
    interfaces/exmaralda/ExmaraldaTranscriptionBridge.h \
    interfaces/ImportAnnotations.h \
    interfaces/InterfaceTextFile.h \
    interfaces/phon/PhonTranscription.h \
    interfaces/praat/AnnotationInterfacePraat.h \
    interfaces/praat/PraatPitchFile.h \
    interfaces/praat/PraatPointTierFile.h \
    interfaces/praat/PraatTextFile.h \
    interfaces/praat/PraatTextGrid.h \
    interfaces/subtitles/SubtitlesFile.h \
    interfaces/transcriber/TranscriberAnnotationGraph.h \
    language/PhonemeDefinitions.h \
    language/PhoneticAlphabet.h \
    language/Tokeniser.h \
    pncore_global.h \
    QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlAddColumnService.h \
    QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlAlterColumnTypeService.h \
    QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlCreateIndexService.h \
    QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlCreateTableService.h \
    QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlDropColumnService.h \
    QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlDropIndexService.h \
    QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlDropTableService.h \
    QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlRenameColumnService.h \
    QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlRenameTableService.h \
    QSqlMigrator/BaseSqlMigrator/Helper/BaseSqlColumnService.h \
    QSqlMigrator/BaseSqlMigrator/Helper/BaseSqlQuoteService.h \
    QSqlMigrator/BaseSqlMigrator/Helper/BaseSqlTypeMapperService.h \
    QSqlMigrator/BaseSqlMigrator/MigrationTracker/BaseMigrationTableService.h \
    QSqlMigrator/CommandExecution/BaseCommandExecutionService.h \
    QSqlMigrator/CommandExecution/CommandExecutionContext.h \
    QSqlMigrator/CommandExecution/CommandExecutionService.h \
    QSqlMigrator/CommandExecution/CommandExecutionServiceRepository.h \
    QSqlMigrator/CommandExecution/CustomCommandService.h \
    QSqlMigrator/CommandExecution/LocalSchemeBaseCommandExecutionService.h \
    QSqlMigrator/CommandExecution/LocalSchemeCommandExecutionContext.h \
    QSqlMigrator/CommandExecution/LocalSchemeCommandExecutionService.h \
    QSqlMigrator/CommandExecution/LocalSchemeCommandExecutionServiceRepository.h \
    QSqlMigrator/Commands/AddColumn.h \
    QSqlMigrator/Commands/AlterColumnType.h \
    QSqlMigrator/Commands/BaseCommand.h \
    QSqlMigrator/Commands/CreateIndex.h \
    QSqlMigrator/Commands/CreateTable.h \
    QSqlMigrator/Commands/CustomCommandBase.h \
    QSqlMigrator/Commands/DropColumn.h \
    QSqlMigrator/Commands/DropIndex.h \
    QSqlMigrator/Commands/DropTable.h \
    QSqlMigrator/Commands/RenameColumn.h \
    QSqlMigrator/Commands/RenameTable.h \
    QSqlMigrator/Databases/FirebirdMigrator/FirebirdMigrator.h \
    QSqlMigrator/Databases/FirebirdMigrator/Helper/FirebirdSqlStructureService.h \
    QSqlMigrator/Databases/MysqlMigrator/CommandExecution/MysqlAlterColumnTypeService.h \
    QSqlMigrator/Databases/MysqlMigrator/CommandExecution/MysqlRenameColumnService.h \
    QSqlMigrator/Databases/MysqlMigrator/Helper/MysqlColumnService.h \
    QSqlMigrator/Databases/MysqlMigrator/Helper/MysqlStructureService.h \
    QSqlMigrator/Databases/MysqlMigrator/Helper/MysqlTypeMapperService.h \
    QSqlMigrator/Databases/MysqlMigrator/MysqlMigrator.h \
    QSqlMigrator/Databases/PostgresqlMigrator/Helper/PostgresqlColumnService.h \
    QSqlMigrator/Databases/PostgresqlMigrator/Helper/PostgresqlQuoteService.h \
    QSqlMigrator/Databases/PostgresqlMigrator/Helper/PostgresqlStructureService.h \
    QSqlMigrator/Databases/PostgresqlMigrator/Helper/PostgresqlTypeMapperService.h \
    QSqlMigrator/Databases/PostgresqlMigrator/PostgresqlMigrator.h \
    QSqlMigrator/Databases/SqliteMigrator/CommandExecution/SqliteAlterColumnService.h \
    QSqlMigrator/Databases/SqliteMigrator/CommandExecution/SqliteAlterColumnTypeService.h \
    QSqlMigrator/Databases/SqliteMigrator/CommandExecution/SqliteDropColumnService.h \
    QSqlMigrator/Databases/SqliteMigrator/CommandExecution/SqliteRenameColumnService.h \
    QSqlMigrator/Databases/SqliteMigrator/DatabaseLock.h \
    QSqlMigrator/Databases/SqliteMigrator/Helper/SqliteSqlStructureService.h \
    QSqlMigrator/Databases/SqliteMigrator/MigrationTracker/SqliteMigrationTableService.h \
    QSqlMigrator/Databases/SqliteMigrator/SqliteMigrator.h \
    QSqlMigrator/Helper/ColumnService.h \
    QSqlMigrator/Helper/HelperRepository.h \
    QSqlMigrator/Helper/QuoteService.h \
    QSqlMigrator/Helper/SqlStructureService.h \
    QSqlMigrator/Helper/TypeMapperService.h \
    QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeAddColumnService.h \
    QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeAlterColumnTypeService.h \
    QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeCreateIndexService.h \
    QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeCreateTableService.h \
    QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeDropColumnService.h \
    QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeDropIndexService.h \
    QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeDropTableService.h \
    QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeRenameColumnService.h \
    QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeRenameTableService.h \
    QSqlMigrator/LocalSchemeMigrator/LocalSchemeComparisonContext.h \
    QSqlMigrator/LocalSchemeMigrator/LocalSchemeComparisonService.h \
    QSqlMigrator/LocalSchemeMigrator/LocalSchemeMigrator.h \
    QSqlMigrator/MigrationExecution/LocalSchemeMigrationExecutionContext.h \
    QSqlMigrator/MigrationExecution/LocalSchemeMigrationExecutionService.h \
    QSqlMigrator/MigrationExecution/MigrationExecutionConfig.h \
    QSqlMigrator/MigrationExecution/MigrationExecutionContext.h \
    QSqlMigrator/MigrationExecution/MigrationExecutionService.h \
    QSqlMigrator/Migrations/Migration.h \
    QSqlMigrator/Migrations/MigrationRepository.h \
    QSqlMigrator/Migrations/RegisterMigration.h \
    QSqlMigrator/MigrationTracker/MigrationTrackerService.h \
    QSqlMigrator/QSqlMigrator.h \
    QSqlMigrator/QSqlMigrator/QSqlMigratorConfig.h \
    QSqlMigrator/QSqlMigrator/QSqlMigratorService.h \
    QSqlMigrator/QSqlMigratorConfig.h \
    QSqlMigrator/Scheme/Database.h \
    QSqlMigrator/Scheme/DbColumn.h \
    QSqlMigrator/Scheme/DbTable.h \
    QSqlMigrator/Structure/Column.h \
    QSqlMigrator/Structure/Index.h \
    QSqlMigrator/Structure/LocalScheme.h \
    QSqlMigrator/Structure/SqlType.h \
    QSqlMigrator/Structure/Table.h \
    query/Dataset.h \
    query/DatasetDefinition.h \
    query/QueryDefinition.h \
    query/QueryFilterGroup.h \
    query/QueryFilterSequence.h \
    query/QueryOccurrence.h \
    serialisers/base/SerialiserAnnotation.h \
    serialisers/base/SerialiserAnnotationStructure.h \
    serialisers/base/SerialiserMetadata.h \
    serialisers/base/SerialiserMetadataStructure.h \
    serialisers/base/SerialiserNameValueList.h \
    serialisers/json/JSONSerialiserAnnotation.h \
    serialisers/json/JSONSerialiserAnnotationStructure.h \
    serialisers/json/JSONSerialiserBase.h \
    serialisers/json/JSONSerialiserCorpusBookmark.h \
    serialisers/json/JSONSerialiserDatasetDefinition.h \
    serialisers/json/JSONSerialiserMetadata.h \
    serialisers/json/JSONSerialiserMetadataStructure.h \
    serialisers/json/JSONSerialiserNameValueList.h \
    serialisers/json/JSONSerialiserQueryDefinition.h \
    serialisers/sql/SQLQueryEngineAnnotation.h \
    serialisers/sql/SQLSchemaProxyBase.h \
    serialisers/sql/SQLSerialiserAnnotation.h \
    serialisers/sql/SQLSerialiserAnnotationStructure.h \
    serialisers/sql/SQLSerialiserBase.h \
    serialisers/sql/SQLSerialiserMetadata.h \
    serialisers/sql/SQLSerialiserMetadataStructure.h \
    serialisers/sql/SQLSerialiserNameValueList.h \
    serialisers/sql/SQLSerialiserSystem.h \
    serialisers/xml/XMLSerialiserAnnotation.h \
    serialisers/xml/XMLSerialiserAnnotationStructure.h \
    serialisers/xml/XMLSerialiserBase.h \
    serialisers/xml/XMLSerialiserCorpusBookmark.h \
    serialisers/xml/XMLSerialiserMetadata.h \
    serialisers/xml/XMLSerialiserMetadataStructure.h \
    serialisers/xml/XMLSerialiserNameValueList.h \
    statistics/HistogramCalculator.h \
    statistics/Measures.h \
    statistics/SpeakerTimeline.h \
    statistics/StatisticalMeasureDefinition.h \
    statistics/StatisticalSummary.h \
    statistics/WordAlign.h \
    structure/AnnotationStructure.h \
    structure/AnnotationStructureAttribute.h \
    structure/AnnotationStructureLevel.h \
    structure/MetadataStructure.h \
    structure/MetadataStructureAttribute.h \
    structure/MetadataStructureSection.h \
    structure/NameValueList.h \
    structure/StructureAttributeBase.h \
    interfaces/tei/TEIHeader.h \
    interfaces/elan/ELANAnnotation.h

SOURCES += \
    base/DataType.cpp \
    base/IDatastore.cpp \
    base/ISaveable.cpp \
    base/RealTime.cpp \
    base/RealValueList.cpp \
    annotation/AnnotationDataTable.cpp \
    annotation/AnnotationElement.cpp \
    annotation/AnnotationTier.cpp \
    annotation/AnnotationTierGroup.cpp \
    annotation/Interval.cpp \
    annotation/IntervalTier.cpp \
    annotation/Point.cpp \
    annotation/PointTier.cpp \
    annotation/Relation.cpp \
    annotation/RelationTier.cpp \
    annotation/Sequence.cpp \
    annotation/SequenceTier.cpp \
    annotation/Transcription.cpp \
    annotation/TreeTier.cpp \
    corpus/Corpus.cpp \
    corpus/CorpusAnnotation.cpp \
    corpus/CorpusBookmark.cpp \
    corpus/CorpusCommunication.cpp \
    corpus/CorpusObject.cpp \
    corpus/CorpusObjectInfo.cpp \
    corpus/CorpusParticipation.cpp \
    corpus/CorpusRecording.cpp \
    corpus/CorpusSpeaker.cpp \
    dataframe/DataFrame.cpp \
    datastore/AnnotationDatastore.cpp \
    datastore/CorpusDatastore.cpp \
    datastore/CorpusRepository.cpp \
    datastore/CorpusRepositoryDefinition.cpp \
    datastore/DatastoreFactory.cpp \
    datastore/FileDatastore.cpp \
    datastore/MetadataDatastore.cpp \
    datastore/NameValueListDatastore.cpp \
    datastore/SQLAnnotationDatastore.cpp \
    datastore/SQLMetadataDatastore.cpp \
    datastore/XMLAnnotationDatastore.cpp \
    datastore/XMLMetadataDatastore.cpp \
    diff/DiffIntervals.cpp \
    diff/DiffPoints.cpp \
    interfaces/anvil/AnvilMetadataTranscript.cpp \
    interfaces/conll/CoNLLXDocument.cpp \
    interfaces/csv/CSVFileAnnotation.cpp \
    interfaces/exmaralda/ExmaraldaBasicTranscription.cpp \
    interfaces/exmaralda/ExmaraldaTranscriptionBridge.cpp \
    interfaces/ImportAnnotations.cpp \
    interfaces/InterfaceTextFile.cpp \
    interfaces/phon/PhonTranscription.cpp \
    interfaces/praat/AnnotationInterfacePraat.cpp \
    interfaces/praat/PraatPitchFile.cpp \
    interfaces/praat/PraatPointTierFile.cpp \
    interfaces/praat/PraatTextFile.cpp \
    interfaces/praat/PraatTextGrid.cpp \
    interfaces/subtitles/SubtitlesFile.cpp \
    interfaces/transcriber/TranscriberAnnotationGraph.cpp \
    interfaces/tei/TEIHeader.cpp \
    interfaces/elan/ELANAnnotation.cpp \
    language/PhonemeDefinitions.cpp \
    language/PhoneticAlphabet.cpp \
    language/Tokeniser.cpp \
    QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlAddColumnService.cpp \
    QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlAlterColumnTypeService.cpp \
    QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlCreateIndexService.cpp \
    QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlCreateTableService.cpp \
    QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlDropColumnService.cpp \
    QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlDropIndexService.cpp \
    QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlDropTableService.cpp \
    QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlRenameColumnService.cpp \
    QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlRenameTableService.cpp \
    QSqlMigrator/BaseSqlMigrator/Helper/BaseSqlColumnService.cpp \
    QSqlMigrator/BaseSqlMigrator/Helper/BaseSqlQuoteService.cpp \
    QSqlMigrator/BaseSqlMigrator/Helper/BaseSqlTypeMapperService.cpp \
    QSqlMigrator/BaseSqlMigrator/MigrationTracker/BaseMigrationTableService.cpp \
    QSqlMigrator/CommandExecution/BaseCommandExecutionService.cpp \
    QSqlMigrator/CommandExecution/CommandExecutionContext.cpp \
    QSqlMigrator/CommandExecution/CommandExecutionService.cpp \
    QSqlMigrator/CommandExecution/CommandExecutionServiceRepository.cpp \
    QSqlMigrator/CommandExecution/CustomCommandService.cpp \
    QSqlMigrator/CommandExecution/LocalSchemeBaseCommandExecutionService.cpp \
    QSqlMigrator/CommandExecution/LocalSchemeCommandExecutionContext.cpp \
    QSqlMigrator/CommandExecution/LocalSchemeCommandExecutionService.cpp \
    QSqlMigrator/CommandExecution/LocalSchemeCommandExecutionServiceRepository.cpp \
    QSqlMigrator/Commands/AddColumn.cpp \
    QSqlMigrator/Commands/AlterColumnType.cpp \
    QSqlMigrator/Commands/BaseCommand.cpp \
    QSqlMigrator/Commands/CreateIndex.cpp \
    QSqlMigrator/Commands/CreateTable.cpp \
    QSqlMigrator/Commands/CustomCommandBase.cpp \
    QSqlMigrator/Commands/DropColumn.cpp \
    QSqlMigrator/Commands/DropIndex.cpp \
    QSqlMigrator/Commands/DropTable.cpp \
    QSqlMigrator/Commands/RenameColumn.cpp \
    QSqlMigrator/Commands/RenameTable.cpp \
    QSqlMigrator/Databases/FirebirdMigrator/FirebirdMigrator.cpp \
    QSqlMigrator/Databases/FirebirdMigrator/Helper/FirebirdSqlStructureService.cpp \
    QSqlMigrator/Databases/MysqlMigrator/CommandExecution/MysqlAlterColumnTypeService.cpp \
    QSqlMigrator/Databases/MysqlMigrator/CommandExecution/MysqlRenameColumnService.cpp \
    QSqlMigrator/Databases/MysqlMigrator/Helper/MysqlColumnService.cpp \
    QSqlMigrator/Databases/MysqlMigrator/Helper/MysqlStructureService.cpp \
    QSqlMigrator/Databases/MysqlMigrator/Helper/MysqlTypeMapperService.cpp \
    QSqlMigrator/Databases/MysqlMigrator/MysqlMigrator.cpp \
    QSqlMigrator/Databases/PostgresqlMigrator/Helper/PostgresqlColumnService.cpp \
    QSqlMigrator/Databases/PostgresqlMigrator/Helper/PostgresqlQuoteService.cpp \
    QSqlMigrator/Databases/PostgresqlMigrator/Helper/PostgresqlStructureService.cpp \
    QSqlMigrator/Databases/PostgresqlMigrator/Helper/PostgresqlTypeMapperService.cpp \
    QSqlMigrator/Databases/PostgresqlMigrator/PostgresqlMigrator.cpp \
    QSqlMigrator/Databases/SqliteMigrator/CommandExecution/SqliteAlterColumnService.cpp \
    QSqlMigrator/Databases/SqliteMigrator/CommandExecution/SqliteAlterColumnTypeService.cpp \
    QSqlMigrator/Databases/SqliteMigrator/CommandExecution/SqliteDropColumnService.cpp \
    QSqlMigrator/Databases/SqliteMigrator/CommandExecution/SqliteRenameColumnService.cpp \
    QSqlMigrator/Databases/SqliteMigrator/DatabaseLock.cpp \
    QSqlMigrator/Databases/SqliteMigrator/Helper/SqliteSqlStructureService.cpp \
    QSqlMigrator/Databases/SqliteMigrator/MigrationTracker/SqliteMigrationTableService.cpp \
    QSqlMigrator/Databases/SqliteMigrator/SqliteMigrator.cpp \
    QSqlMigrator/Helper/HelperRepository.cpp \
    QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeAddColumnService.cpp \
    QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeAlterColumnTypeService.cpp \
    QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeCreateIndexService.cpp \
    QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeCreateTableService.cpp \
    QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeDropColumnService.cpp \
    QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeDropIndexService.cpp \
    QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeDropTableService.cpp \
    QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeRenameColumnService.cpp \
    QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeRenameTableService.cpp \
    QSqlMigrator/LocalSchemeMigrator/LocalSchemeComparisonContext.cpp \
    QSqlMigrator/LocalSchemeMigrator/LocalSchemeComparisonService.cpp \
    QSqlMigrator/LocalSchemeMigrator/LocalSchemeMigrator.cpp \
    QSqlMigrator/MigrationExecution/LocalSchemeMigrationExecutionContext.cpp \
    QSqlMigrator/MigrationExecution/LocalSchemeMigrationExecutionService.cpp \
    QSqlMigrator/MigrationExecution/MigrationExecutionConfig.cpp \
    QSqlMigrator/MigrationExecution/MigrationExecutionContext.cpp \
    QSqlMigrator/MigrationExecution/MigrationExecutionService.cpp \
    QSqlMigrator/Migrations/Migration.cpp \
    QSqlMigrator/Migrations/MigrationRepository.cpp \
    QSqlMigrator/QSqlMigrator/QSqlMigratorConfig.cpp \
    QSqlMigrator/QSqlMigrator/QSqlMigratorService.cpp \
    QSqlMigrator/Scheme/Database.cpp \
    QSqlMigrator/Scheme/DbColumn.cpp \
    QSqlMigrator/Scheme/DbTable.cpp \
    QSqlMigrator/Structure/Column.cpp \
    QSqlMigrator/Structure/Index.cpp \
    QSqlMigrator/Structure/LocalScheme.cpp \
    QSqlMigrator/Structure/SqlType.cpp \
    QSqlMigrator/Structure/Table.cpp \
    query/Dataset.cpp \
    query/DatasetDefinition.cpp \
    query/QueryDefinition.cpp \
    query/QueryFilterGroup.cpp \
    query/QueryFilterSequence.cpp \
    query/QueryOccurrence.cpp \
    serialisers/base/SerialiserAnnotation.cpp \
    serialisers/base/SerialiserAnnotationStructure.cpp \
    serialisers/base/SerialiserMetadata.cpp \
    serialisers/base/SerialiserMetadataStructure.cpp \
    serialisers/base/SerialiserNameValueList.cpp \
    serialisers/json/JSONSerialiserAnnotation.cpp \
    serialisers/json/JSONSerialiserAnnotationStructure.cpp \
    serialisers/json/JSONSerialiserBase.cpp \
    serialisers/json/JSONSerialiserCorpusBookmark.cpp \
    serialisers/json/JSONSerialiserDatasetDefinition.cpp \
    serialisers/json/JSONSerialiserMetadata.cpp \
    serialisers/json/JSONSerialiserMetadataStructure.cpp \
    serialisers/json/JSONSerialiserNameValueList.cpp \
    serialisers/json/JSONSerialiserQueryDefinition.cpp \
    serialisers/sql/SQLQueryEngineAnnotation.cpp \
    serialisers/sql/SQLSchemaProxyBase.cpp \
    serialisers/sql/SQLSerialiserAnnotation.cpp \
    serialisers/sql/SQLSerialiserAnnotationStructure.cpp \
    serialisers/sql/SQLSerialiserBase.cpp \
    serialisers/sql/SQLSerialiserMetadata.cpp \
    serialisers/sql/SQLSerialiserMetadataStructure.cpp \
    serialisers/sql/SQLSerialiserNameValueList.cpp \
    serialisers/sql/SQLSerialiserSystem.cpp \
    serialisers/xml/XMLSerialiserAnnotation.cpp \
    serialisers/xml/XMLSerialiserAnnotationStructure.cpp \
    serialisers/xml/XMLSerialiserBase.cpp \
    serialisers/xml/XMLSerialiserCorpusBookmark.cpp \
    serialisers/xml/XMLSerialiserMetadata.cpp \
    serialisers/xml/XMLSerialiserMetadataStructure.cpp \
    serialisers/xml/XMLSerialiserNameValueList.cpp \
    statistics/HistogramCalculator.cpp \
    statistics/Measures.cpp \
    statistics/SpeakerTimeline.cpp \
    statistics/StatisticalMeasureDefinition.cpp \
    statistics/StatisticalSummary.cpp \
    statistics/WordAlign.cpp \
    structure/AnnotationStructure.cpp \
    structure/AnnotationStructureAttribute.cpp \
    structure/AnnotationStructureLevel.cpp \
    structure/MetadataStructure.cpp \
    structure/MetadataStructureAttribute.cpp \
    structure/MetadataStructureSection.cpp \
    structure/NameValueList.cpp \
    structure/StructureAttributeBase.cpp

DISTFILES += \
    Doxyfile \
    pncore.qmodel
