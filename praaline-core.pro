# Praaline Core Library
# (c) George Christodoulides 2012-2020

! include( ../common.pri ) {
    ! include( ./praaline-core-common.pri ) {
        error( Could not find the common.pri file! )
    }
}

TEMPLATE = lib

CONFIG(debug, debug|release) {
    TARGET = praaline-cored
} else {
    TARGET = praaline-core
}

CONFIG += qt thread warn_on stl rtti exceptions c++11

QT += xml sql
QT -= gui

DEFINES += PRAALINE_CORE_LIBRARY
DEFINES += USE_NAMESPACE_PRAALINE_CORE

INCLUDEPATH += . external src include/PraalineCore
DEPENDPATH += . external src

# ===========================================================================================================
# QSqlMigrator
# ===========================================================================================================

HEADERS += \
    external/QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlAddColumnService.h \
    external/QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlAlterColumnTypeService.h \
    external/QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlCreateIndexService.h \
    external/QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlCreateTableService.h \
    external/QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlDropColumnService.h \
    external/QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlDropIndexService.h \
    external/QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlDropTableService.h \
    external/QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlRenameColumnService.h \
    external/QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlRenameTableService.h \
    external/QSqlMigrator/BaseSqlMigrator/Helper/BaseSqlColumnService.h \
    external/QSqlMigrator/BaseSqlMigrator/Helper/BaseSqlQuoteService.h \
    external/QSqlMigrator/BaseSqlMigrator/Helper/BaseSqlTypeMapperService.h \
    external/QSqlMigrator/BaseSqlMigrator/MigrationTracker/BaseMigrationTableService.h \
    external/QSqlMigrator/CommandExecution/BaseCommandExecutionService.h \
    external/QSqlMigrator/CommandExecution/CommandExecutionContext.h \
    external/QSqlMigrator/CommandExecution/CommandExecutionService.h \
    external/QSqlMigrator/CommandExecution/CommandExecutionServiceRepository.h \
    external/QSqlMigrator/CommandExecution/CustomCommandService.h \
    external/QSqlMigrator/CommandExecution/LocalSchemeBaseCommandExecutionService.h \
    external/QSqlMigrator/CommandExecution/LocalSchemeCommandExecutionContext.h \
    external/QSqlMigrator/CommandExecution/LocalSchemeCommandExecutionService.h \
    external/QSqlMigrator/CommandExecution/LocalSchemeCommandExecutionServiceRepository.h \
    external/QSqlMigrator/Commands/AddColumn.h \
    external/QSqlMigrator/Commands/AlterColumnType.h \
    external/QSqlMigrator/Commands/BaseCommand.h \
    external/QSqlMigrator/Commands/CreateIndex.h \
    external/QSqlMigrator/Commands/CreateTable.h \
    external/QSqlMigrator/Commands/CustomCommandBase.h \
    external/QSqlMigrator/Commands/DropColumn.h \
    external/QSqlMigrator/Commands/DropIndex.h \
    external/QSqlMigrator/Commands/DropTable.h \
    external/QSqlMigrator/Commands/RenameColumn.h \
    external/QSqlMigrator/Commands/RenameTable.h \
    external/QSqlMigrator/Databases/FirebirdMigrator/FirebirdMigrator.h \
    external/QSqlMigrator/Databases/FirebirdMigrator/Helper/FirebirdSqlStructureService.h \
    external/QSqlMigrator/Databases/MysqlMigrator/CommandExecution/MysqlAlterColumnTypeService.h \
    external/QSqlMigrator/Databases/MysqlMigrator/CommandExecution/MysqlRenameColumnService.h \
    external/QSqlMigrator/Databases/MysqlMigrator/Helper/MysqlColumnService.h \
    external/QSqlMigrator/Databases/MysqlMigrator/Helper/MysqlStructureService.h \
    external/QSqlMigrator/Databases/MysqlMigrator/Helper/MysqlTypeMapperService.h \
    external/QSqlMigrator/Databases/MysqlMigrator/MysqlMigrator.h \
    external/QSqlMigrator/Databases/PostgresqlMigrator/Helper/PostgresqlColumnService.h \
    external/QSqlMigrator/Databases/PostgresqlMigrator/Helper/PostgresqlQuoteService.h \
    external/QSqlMigrator/Databases/PostgresqlMigrator/Helper/PostgresqlStructureService.h \
    external/QSqlMigrator/Databases/PostgresqlMigrator/Helper/PostgresqlTypeMapperService.h \
    external/QSqlMigrator/Databases/PostgresqlMigrator/PostgresqlMigrator.h \
    external/QSqlMigrator/Databases/SqliteMigrator/CommandExecution/SqliteAlterColumnService.h \
    external/QSqlMigrator/Databases/SqliteMigrator/CommandExecution/SqliteAlterColumnTypeService.h \
    external/QSqlMigrator/Databases/SqliteMigrator/CommandExecution/SqliteDropColumnService.h \
    external/QSqlMigrator/Databases/SqliteMigrator/CommandExecution/SqliteRenameColumnService.h \
    external/QSqlMigrator/Databases/SqliteMigrator/DatabaseLock.h \
    external/QSqlMigrator/Databases/SqliteMigrator/Helper/SqliteSqlStructureService.h \
    external/QSqlMigrator/Databases/SqliteMigrator/MigrationTracker/SqliteMigrationTableService.h \
    external/QSqlMigrator/Databases/SqliteMigrator/SqliteMigrator.h \
    external/QSqlMigrator/Helper/ColumnService.h \
    external/QSqlMigrator/Helper/HelperRepository.h \
    external/QSqlMigrator/Helper/QuoteService.h \
    external/QSqlMigrator/Helper/SqlStructureService.h \
    external/QSqlMigrator/Helper/TypeMapperService.h \
    external/QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeAddColumnService.h \
    external/QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeAlterColumnTypeService.h \
    external/QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeCreateIndexService.h \
    external/QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeCreateTableService.h \
    external/QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeDropColumnService.h \
    external/QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeDropIndexService.h \
    external/QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeDropTableService.h \
    external/QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeRenameColumnService.h \
    external/QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeRenameTableService.h \
    external/QSqlMigrator/LocalSchemeMigrator/LocalSchemeComparisonContext.h \
    external/QSqlMigrator/LocalSchemeMigrator/LocalSchemeComparisonService.h \
    external/QSqlMigrator/LocalSchemeMigrator/LocalSchemeMigrator.h \
    external/QSqlMigrator/MigrationExecution/LocalSchemeMigrationExecutionContext.h \
    external/QSqlMigrator/MigrationExecution/LocalSchemeMigrationExecutionService.h \
    external/QSqlMigrator/MigrationExecution/MigrationExecutionConfig.h \
    external/QSqlMigrator/MigrationExecution/MigrationExecutionContext.h \
    external/QSqlMigrator/MigrationExecution/MigrationExecutionService.h \
    external/QSqlMigrator/Migrations/Migration.h \
    external/QSqlMigrator/Migrations/MigrationRepository.h \
    external/QSqlMigrator/Migrations/RegisterMigration.h \
    external/QSqlMigrator/MigrationTracker/MigrationTrackerService.h \
    external/QSqlMigrator/QSqlMigrator.h \
    external/QSqlMigrator/QSqlMigrator/QSqlMigratorConfig.h \
    external/QSqlMigrator/QSqlMigrator/QSqlMigratorService.h \
    external/QSqlMigrator/QSqlMigratorConfig.h \
    external/QSqlMigrator/Scheme/Database.h \
    external/QSqlMigrator/Scheme/DbColumn.h \
    external/QSqlMigrator/Scheme/DbTable.h \
    external/QSqlMigrator/Structure/Column.h \
    external/QSqlMigrator/Structure/Index.h \
    external/QSqlMigrator/Structure/LocalScheme.h \
    external/QSqlMigrator/Structure/SqlType.h \
    external/QSqlMigrator/Structure/Table.h

SOURCES += \
    external/QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlAddColumnService.cpp \
    external/QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlAlterColumnTypeService.cpp \
    external/QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlCreateIndexService.cpp \
    external/QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlCreateTableService.cpp \
    external/QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlDropColumnService.cpp \
    external/QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlDropIndexService.cpp \
    external/QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlDropTableService.cpp \
    external/QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlRenameColumnService.cpp \
    external/QSqlMigrator/BaseSqlMigrator/CommandExecution/BaseSqlRenameTableService.cpp \
    external/QSqlMigrator/BaseSqlMigrator/Helper/BaseSqlColumnService.cpp \
    external/QSqlMigrator/BaseSqlMigrator/Helper/BaseSqlQuoteService.cpp \
    external/QSqlMigrator/BaseSqlMigrator/Helper/BaseSqlTypeMapperService.cpp \
    external/QSqlMigrator/BaseSqlMigrator/MigrationTracker/BaseMigrationTableService.cpp \
    external/QSqlMigrator/CommandExecution/BaseCommandExecutionService.cpp \
    external/QSqlMigrator/CommandExecution/CommandExecutionContext.cpp \
    external/QSqlMigrator/CommandExecution/CommandExecutionService.cpp \
    external/QSqlMigrator/CommandExecution/CommandExecutionServiceRepository.cpp \
    external/QSqlMigrator/CommandExecution/CustomCommandService.cpp \
    external/QSqlMigrator/CommandExecution/LocalSchemeBaseCommandExecutionService.cpp \
    external/QSqlMigrator/CommandExecution/LocalSchemeCommandExecutionContext.cpp \
    external/QSqlMigrator/CommandExecution/LocalSchemeCommandExecutionService.cpp \
    external/QSqlMigrator/CommandExecution/LocalSchemeCommandExecutionServiceRepository.cpp \
    external/QSqlMigrator/Commands/AddColumn.cpp \
    external/QSqlMigrator/Commands/AlterColumnType.cpp \
    external/QSqlMigrator/Commands/BaseCommand.cpp \
    external/QSqlMigrator/Commands/CreateIndex.cpp \
    external/QSqlMigrator/Commands/CreateTable.cpp \
    external/QSqlMigrator/Commands/CustomCommandBase.cpp \
    external/QSqlMigrator/Commands/DropColumn.cpp \
    external/QSqlMigrator/Commands/DropIndex.cpp \
    external/QSqlMigrator/Commands/DropTable.cpp \
    external/QSqlMigrator/Commands/RenameColumn.cpp \
    external/QSqlMigrator/Commands/RenameTable.cpp \
    external/QSqlMigrator/Databases/FirebirdMigrator/FirebirdMigrator.cpp \
    external/QSqlMigrator/Databases/FirebirdMigrator/Helper/FirebirdSqlStructureService.cpp \
    external/QSqlMigrator/Databases/MysqlMigrator/CommandExecution/MysqlAlterColumnTypeService.cpp \
    external/QSqlMigrator/Databases/MysqlMigrator/CommandExecution/MysqlRenameColumnService.cpp \
    external/QSqlMigrator/Databases/MysqlMigrator/Helper/MysqlColumnService.cpp \
    external/QSqlMigrator/Databases/MysqlMigrator/Helper/MysqlStructureService.cpp \
    external/QSqlMigrator/Databases/MysqlMigrator/Helper/MysqlTypeMapperService.cpp \
    external/QSqlMigrator/Databases/MysqlMigrator/MysqlMigrator.cpp \
    external/QSqlMigrator/Databases/PostgresqlMigrator/Helper/PostgresqlColumnService.cpp \
    external/QSqlMigrator/Databases/PostgresqlMigrator/Helper/PostgresqlQuoteService.cpp \
    external/QSqlMigrator/Databases/PostgresqlMigrator/Helper/PostgresqlStructureService.cpp \
    external/QSqlMigrator/Databases/PostgresqlMigrator/Helper/PostgresqlTypeMapperService.cpp \
    external/QSqlMigrator/Databases/PostgresqlMigrator/PostgresqlMigrator.cpp \
    external/QSqlMigrator/Databases/SqliteMigrator/CommandExecution/SqliteAlterColumnService.cpp \
    external/QSqlMigrator/Databases/SqliteMigrator/CommandExecution/SqliteAlterColumnTypeService.cpp \
    external/QSqlMigrator/Databases/SqliteMigrator/CommandExecution/SqliteDropColumnService.cpp \
    external/QSqlMigrator/Databases/SqliteMigrator/CommandExecution/SqliteRenameColumnService.cpp \
    external/QSqlMigrator/Databases/SqliteMigrator/DatabaseLock.cpp \
    external/QSqlMigrator/Databases/SqliteMigrator/Helper/SqliteSqlStructureService.cpp \
    external/QSqlMigrator/Databases/SqliteMigrator/MigrationTracker/SqliteMigrationTableService.cpp \
    external/QSqlMigrator/Databases/SqliteMigrator/SqliteMigrator.cpp \
    external/QSqlMigrator/Helper/HelperRepository.cpp \
    external/QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeAddColumnService.cpp \
    external/QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeAlterColumnTypeService.cpp \
    external/QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeCreateIndexService.cpp \
    external/QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeCreateTableService.cpp \
    external/QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeDropColumnService.cpp \
    external/QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeDropIndexService.cpp \
    external/QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeDropTableService.cpp \
    external/QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeRenameColumnService.cpp \
    external/QSqlMigrator/LocalSchemeMigrator/CommandExecution/LocalSchemeRenameTableService.cpp \
    external/QSqlMigrator/LocalSchemeMigrator/LocalSchemeComparisonContext.cpp \
    external/QSqlMigrator/LocalSchemeMigrator/LocalSchemeComparisonService.cpp \
    external/QSqlMigrator/LocalSchemeMigrator/LocalSchemeMigrator.cpp \
    external/QSqlMigrator/MigrationExecution/LocalSchemeMigrationExecutionContext.cpp \
    external/QSqlMigrator/MigrationExecution/LocalSchemeMigrationExecutionService.cpp \
    external/QSqlMigrator/MigrationExecution/MigrationExecutionConfig.cpp \
    external/QSqlMigrator/MigrationExecution/MigrationExecutionContext.cpp \
    external/QSqlMigrator/MigrationExecution/MigrationExecutionService.cpp \
    external/QSqlMigrator/Migrations/Migration.cpp \
    external/QSqlMigrator/Migrations/MigrationRepository.cpp \
    external/QSqlMigrator/QSqlMigrator/QSqlMigratorConfig.cpp \
    external/QSqlMigrator/QSqlMigrator/QSqlMigratorService.cpp \
    external/QSqlMigrator/Scheme/Database.cpp \
    external/QSqlMigrator/Scheme/DbColumn.cpp \
    external/QSqlMigrator/Scheme/DbTable.cpp \
    external/QSqlMigrator/Structure/Column.cpp \
    external/QSqlMigrator/Structure/Index.cpp \
    external/QSqlMigrator/Structure/LocalScheme.cpp \
    external/QSqlMigrator/Structure/SqlType.cpp \
    external/QSqlMigrator/Structure/Table.cpp

# ===========================================================================================================
# Praaline Core
# ===========================================================================================================

# Public headers

HEADERS += \
    include/PraalineCore/praaline-core_global.h \
    include/PraalineCore/annotation/AnnotationDataTable.h \
    include/PraalineCore/annotation/AnnotationElement.h \
    include/PraalineCore/annotation/AnnotationTier.h \
    include/PraalineCore/annotation/AnnotationTierGroup.h \
    include/PraalineCore/annotation/Interval.h \
    include/PraalineCore/annotation/IntervalTier.h \
    include/PraalineCore/annotation/Point.h \
    include/PraalineCore/annotation/PointTier.h \
    include/PraalineCore/annotation/Relation.h \
    include/PraalineCore/annotation/RelationTier.h \
    include/PraalineCore/annotation/Sequence.h \
    include/PraalineCore/annotation/SequenceTier.h \
    include/PraalineCore/annotation/Transcription.h \
    include/PraalineCore/annotation/TreeTier.h \
    include/PraalineCore/base/BaseTypes.h \
    include/PraalineCore/base/DataType.h \
    include/PraalineCore/base/IDatastore.h \
    include/PraalineCore/base/ISaveable.h \
    include/PraalineCore/base/RealTime.h \
    include/PraalineCore/base/RealValueList.h \
    include/PraalineCore/corpus/Corpus.h \
    include/PraalineCore/corpus/CorpusAnnotation.h \
    include/PraalineCore/corpus/CorpusBookmark.h \
    include/PraalineCore/corpus/CorpusCommunication.h \
    include/PraalineCore/corpus/CorpusObject.h \
    include/PraalineCore/corpus/CorpusObjectInfo.h \
    include/PraalineCore/corpus/CorpusParticipation.h \
    include/PraalineCore/corpus/CorpusRecording.h \
    include/PraalineCore/corpus/CorpusSpeaker.h \
    include/PraalineCore/dataframe/DataFrame.h \
    include/PraalineCore/datastore/AnnotationDatastore.h \
    include/PraalineCore/datastore/CorpusDatastore.h \
    include/PraalineCore/datastore/CorpusRepository.h \
    include/PraalineCore/datastore/CorpusRepositoryDefinition.h \
    include/PraalineCore/datastore/DatastoreFactory.h \
    include/PraalineCore/datastore/DatastoreInfo.h \
    include/PraalineCore/datastore/FileDatastore.h \
    include/PraalineCore/datastore/MetadataDatastore.h \
    include/PraalineCore/datastore/NameValueListDatastore.h \
    include/PraalineCore/diff/dtl/diff.h \
    include/PraalineCore/diff/dtl/diff3.h \
    include/PraalineCore/diff/dtl/dtl.h \
    include/PraalineCore/diff/dtl/functors.h \
    include/PraalineCore/diff/dtl/lcs.h \
    include/PraalineCore/diff/dtl/sequence.h \
    include/PraalineCore/diff/dtl/ses.h \
    include/PraalineCore/diff/dtl/variables.h \
    include/PraalineCore/diff/DiffIntervals.h \
    include/PraalineCore/diff/DiffPoints.h \
    include/PraalineCore/interfaces/anvil/AnvilMetadataTranscript.h \
    include/PraalineCore/interfaces/conll/CoNLLXDocument.h \
    include/PraalineCore/interfaces/csv/CSVFileAnnotation.h \
    include/PraalineCore/interfaces/exmaralda/ExmaraldaBasicTranscription.h \
    include/PraalineCore/interfaces/exmaralda/ExmaraldaTranscriptionBridge.h \
    include/PraalineCore/interfaces/ImportAnnotations.h \
    include/PraalineCore/interfaces/InterfaceTextFile.h \
    include/PraalineCore/interfaces/phon/PhonTranscription.h \
    include/PraalineCore/interfaces/praat/AnnotationInterfacePraat.h \
    include/PraalineCore/interfaces/praat/PraatPitchFile.h \
    include/PraalineCore/interfaces/praat/PraatPointTierFile.h \
    include/PraalineCore/interfaces/praat/PraatTextFile.h \
    include/PraalineCore/interfaces/praat/PraatTextGrid.h \
    include/PraalineCore/interfaces/subtitles/SubtitlesFile.h \
    include/PraalineCore/interfaces/transcriber/TranscriberAnnotationGraph.h \
    include/PraalineCore/interfaces/tei/TEIHeader.h \
    include/PraalineCore/interfaces/elan/ELANAnnotation.h \
    include/PraalineCore/language/PhonemeDefinitions.h \
    include/PraalineCore/language/PhoneticAlphabet.h \
    include/PraalineCore/language/Tokeniser.h \
    include/PraalineCore/query/Dataset.h \
    include/PraalineCore/query/DatasetDefinition.h \
    include/PraalineCore/query/QueryDefinition.h \
    include/PraalineCore/query/QueryFilterGroup.h \
    include/PraalineCore/query/QueryFilterSequence.h \
    include/PraalineCore/query/QueryOccurrence.h \
    include/PraalineCore/serialisers/json/JSONSerialiserAnnotationStructure.h \
    include/PraalineCore/serialisers/json/JSONSerialiserCorpusBookmark.h \
    include/PraalineCore/serialisers/json/JSONSerialiserDatasetDefinition.h \
    include/PraalineCore/serialisers/json/JSONSerialiserMetadataStructure.h \
    include/PraalineCore/serialisers/json/JSONSerialiserNameValueList.h \
    include/PraalineCore/serialisers/json/JSONSerialiserQueryDefinition.h \
    include/PraalineCore/serialisers/xml/XMLSerialiserAnnotationStructure.h \
    include/PraalineCore/serialisers/xml/XMLSerialiserCorpusBookmark.h \
    include/PraalineCore/serialisers/xml/XMLSerialiserMetadataStructure.h \
    include/PraalineCore/serialisers/xml/XMLSerialiserNameValueList.h \
    include/PraalineCore/statistics/HistogramCalculator.h \
    include/PraalineCore/statistics/Measures.h \
    include/PraalineCore/statistics/SpeakerTimeline.h \
    include/PraalineCore/statistics/StatisticalMeasureDefinition.h \
    include/PraalineCore/statistics/StatisticalSummary.h \
    include/PraalineCore/statistics/WordAlign.h \
    include/PraalineCore/structure/AnnotationStructure.h \
    include/PraalineCore/structure/AnnotationStructureAttribute.h \
    include/PraalineCore/structure/AnnotationStructureLevel.h \
    include/PraalineCore/structure/MetadataStructure.h \
    include/PraalineCore/structure/MetadataStructureAttribute.h \
    include/PraalineCore/structure/MetadataStructureSection.h \
    include/PraalineCore/structure/NameValueList.h \
    include/PraalineCore/structure/StructureAttributeBase.h

# Private headers

HEADERS += \
    src/datastore/SQLAnnotationDatastore.h \
    src/datastore/SQLMetadataDatastore.h \
    src/datastore/XMLAnnotationDatastore.h \
    src/datastore/XMLMetadataDatastore.h \
    src/serialisers/base/SerialiserAnnotation.h \
    src/serialisers/base/SerialiserAnnotationStructure.h \
    src/serialisers/base/SerialiserMetadata.h \
    src/serialisers/base/SerialiserMetadataStructure.h \
    src/serialisers/base/SerialiserNameValueList.h \
    src/serialisers/json/JSONSerialiserAnnotation.h \
    src/serialisers/json/JSONSerialiserBase.h \
    src/serialisers/json/JSONSerialiserMetadata.h \
    src/serialisers/sql/SQLQueryEngineAnnotation.h \
    src/serialisers/sql/SQLSchemaProxyBase.h \
    src/serialisers/sql/SQLSerialiserAnnotation.h \
    src/serialisers/sql/SQLSerialiserAnnotationStructure.h \
    src/serialisers/sql/SQLSerialiserBase.h \
    src/serialisers/sql/SQLSerialiserMetadata.h \
    src/serialisers/sql/SQLSerialiserMetadataStructure.h \
    src/serialisers/sql/SQLSerialiserNameValueList.h \
    src/serialisers/sql/SQLSerialiserSystem.h \
    src/serialisers/xml/XMLSerialiserAnnotation.h \
    src/serialisers/xml/XMLSerialiserBase.h \
    src/serialisers/xml/XMLSerialiserMetadata.h

SOURCES += \
    src/base/DataType.cpp \
    src/base/IDatastore.cpp \
    src/base/ISaveable.cpp \
    src/base/RealTime.cpp \
    src/base/RealValueList.cpp \
    src/annotation/AnnotationDataTable.cpp \
    src/annotation/AnnotationElement.cpp \
    src/annotation/AnnotationTier.cpp \
    src/annotation/AnnotationTierGroup.cpp \
    src/annotation/Interval.cpp \
    src/annotation/IntervalTier.cpp \
    src/annotation/Point.cpp \
    src/annotation/PointTier.cpp \
    src/annotation/Relation.cpp \
    src/annotation/RelationTier.cpp \
    src/annotation/Sequence.cpp \
    src/annotation/SequenceTier.cpp \
    src/annotation/Transcription.cpp \
    src/annotation/TreeTier.cpp \
    src/corpus/Corpus.cpp \
    src/corpus/CorpusAnnotation.cpp \
    src/corpus/CorpusBookmark.cpp \
    src/corpus/CorpusCommunication.cpp \
    src/corpus/CorpusObject.cpp \
    src/corpus/CorpusObjectInfo.cpp \
    src/corpus/CorpusParticipation.cpp \
    src/corpus/CorpusRecording.cpp \
    src/corpus/CorpusSpeaker.cpp \
    src/dataframe/DataFrame.cpp \
    src/datastore/AnnotationDatastore.cpp \
    src/datastore/CorpusDatastore.cpp \
    src/datastore/CorpusRepository.cpp \
    src/datastore/CorpusRepositoryDefinition.cpp \
    src/datastore/DatastoreFactory.cpp \
    src/datastore/FileDatastore.cpp \
    src/datastore/MetadataDatastore.cpp \
    src/datastore/NameValueListDatastore.cpp \
    src/datastore/SQLAnnotationDatastore.cpp \
    src/datastore/SQLMetadataDatastore.cpp \
    src/datastore/XMLAnnotationDatastore.cpp \
    src/datastore/XMLMetadataDatastore.cpp \
    src/diff/DiffIntervals.cpp \
    src/diff/DiffPoints.cpp \
    src/interfaces/anvil/AnvilMetadataTranscript.cpp \
    src/interfaces/conll/CoNLLXDocument.cpp \
    src/interfaces/csv/CSVFileAnnotation.cpp \
    src/interfaces/exmaralda/ExmaraldaBasicTranscription.cpp \
    src/interfaces/exmaralda/ExmaraldaTranscriptionBridge.cpp \
    src/interfaces/ImportAnnotations.cpp \
    src/interfaces/InterfaceTextFile.cpp \
    src/interfaces/phon/PhonTranscription.cpp \
    src/interfaces/praat/AnnotationInterfacePraat.cpp \
    src/interfaces/praat/PraatPitchFile.cpp \
    src/interfaces/praat/PraatPointTierFile.cpp \
    src/interfaces/praat/PraatTextFile.cpp \
    src/interfaces/praat/PraatTextGrid.cpp \
    src/interfaces/subtitles/SubtitlesFile.cpp \
    src/interfaces/transcriber/TranscriberAnnotationGraph.cpp \
    src/interfaces/tei/TEIHeader.cpp \
    src/interfaces/elan/ELANAnnotation.cpp \
    src/language/PhonemeDefinitions.cpp \
    src/language/PhoneticAlphabet.cpp \
    src/language/Tokeniser.cpp \
    src/query/Dataset.cpp \
    src/query/DatasetDefinition.cpp \
    src/query/QueryDefinition.cpp \
    src/query/QueryFilterGroup.cpp \
    src/query/QueryFilterSequence.cpp \
    src/query/QueryOccurrence.cpp \
    src/serialisers/base/SerialiserAnnotation.cpp \
    src/serialisers/base/SerialiserAnnotationStructure.cpp \
    src/serialisers/base/SerialiserMetadata.cpp \
    src/serialisers/base/SerialiserMetadataStructure.cpp \
    src/serialisers/base/SerialiserNameValueList.cpp \
    src/serialisers/json/JSONSerialiserAnnotation.cpp \
    src/serialisers/json/JSONSerialiserAnnotationStructure.cpp \
    src/serialisers/json/JSONSerialiserBase.cpp \
    src/serialisers/json/JSONSerialiserCorpusBookmark.cpp \
    src/serialisers/json/JSONSerialiserDatasetDefinition.cpp \
    src/serialisers/json/JSONSerialiserMetadata.cpp \
    src/serialisers/json/JSONSerialiserMetadataStructure.cpp \
    src/serialisers/json/JSONSerialiserNameValueList.cpp \
    src/serialisers/json/JSONSerialiserQueryDefinition.cpp \
    src/serialisers/sql/SQLQueryEngineAnnotation.cpp \
    src/serialisers/sql/SQLSchemaProxyBase.cpp \
    src/serialisers/sql/SQLSerialiserAnnotation.cpp \
    src/serialisers/sql/SQLSerialiserAnnotationStructure.cpp \
    src/serialisers/sql/SQLSerialiserBase.cpp \
    src/serialisers/sql/SQLSerialiserMetadata.cpp \
    src/serialisers/sql/SQLSerialiserMetadataStructure.cpp \
    src/serialisers/sql/SQLSerialiserNameValueList.cpp \
    src/serialisers/sql/SQLSerialiserSystem.cpp \
    src/serialisers/xml/XMLSerialiserAnnotation.cpp \
    src/serialisers/xml/XMLSerialiserAnnotationStructure.cpp \
    src/serialisers/xml/XMLSerialiserBase.cpp \
    src/serialisers/xml/XMLSerialiserCorpusBookmark.cpp \
    src/serialisers/xml/XMLSerialiserMetadata.cpp \
    src/serialisers/xml/XMLSerialiserMetadataStructure.cpp \
    src/serialisers/xml/XMLSerialiserNameValueList.cpp \
    src/statistics/HistogramCalculator.cpp \
    src/statistics/Measures.cpp \
    src/statistics/SpeakerTimeline.cpp \
    src/statistics/StatisticalMeasureDefinition.cpp \
    src/statistics/StatisticalSummary.cpp \
    src/statistics/WordAlign.cpp \
    src/structure/AnnotationStructure.cpp \
    src/structure/AnnotationStructureAttribute.cpp \
    src/structure/AnnotationStructureLevel.cpp \
    src/structure/MetadataStructure.cpp \
    src/structure/MetadataStructureAttribute.cpp \
    src/structure/MetadataStructureSection.cpp \
    src/structure/NameValueList.cpp \
    src/structure/StructureAttributeBase.cpp

DISTFILES += \
    Doxyfile
