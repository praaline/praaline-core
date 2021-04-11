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

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x050F00
DEFINES += PRAALINE_CORE_LIBRARY
DEFINES += USE_NAMESPACE_PRAALINE_CORE

INCLUDEPATH += . external src include
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
    external/QSqlMigrator/Structure/Table.h \
    src/Serialisers/SQL/SQLSerialiserSpeakerRelation.h

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
    external/QSqlMigrator/Structure/Table.cpp \
    src/Serialisers/SQL/SQLSerialiserSpeakerRelation.cpp

# ===========================================================================================================
# Praaline Core
# ===========================================================================================================

# Public headers

HEADERS += \
    include/PraalineCore/PraalineCore_Global.h \
    include/PraalineCore/Annotation/AnnotationDataTable.h \
    include/PraalineCore/Annotation/AnnotationElement.h \
    include/PraalineCore/Annotation/AnnotationTier.h \
    include/PraalineCore/Annotation/AnnotationTierGroup.h \
    include/PraalineCore/Annotation/Interval.h \
    include/PraalineCore/Annotation/IntervalTier.h \
    include/PraalineCore/Annotation/Point.h \
    include/PraalineCore/Annotation/PointTier.h \
    include/PraalineCore/Annotation/Relation.h \
    include/PraalineCore/Annotation/RelationTier.h \
    include/PraalineCore/Annotation/Sequence.h \
    include/PraalineCore/Annotation/SequenceTier.h \
    include/PraalineCore/Annotation/Transcription.h \
    include/PraalineCore/Annotation/TreeTier.h \
    include/PraalineCore/Base/BaseTypes.h \
    include/PraalineCore/Base/DataType.h \
    include/PraalineCore/Base/IDatastore.h \
    include/PraalineCore/Base/ISaveable.h \
    include/PraalineCore/Base/RealTime.h \
    include/PraalineCore/Base/RealValueList.h \
    include/PraalineCore/Corpus/Corpus.h \
    include/PraalineCore/Corpus/CorpusAnnotation.h \
    include/PraalineCore/Corpus/CorpusBookmark.h \
    include/PraalineCore/Corpus/CorpusCommunication.h \
    include/PraalineCore/Corpus/CorpusObject.h \
    include/PraalineCore/Corpus/CorpusObjectInfo.h \
    include/PraalineCore/Corpus/CorpusParticipation.h \
    include/PraalineCore/Corpus/CorpusRecording.h \
    include/PraalineCore/Corpus/CorpusSpeaker.h \
    include/PraalineCore/Corpus/CorpusSpeakerRelation.h \
    include/PraalineCore/Dataframe/DataFrame.h \
    include/PraalineCore/Datastore/AnnotationDatastore.h \
    include/PraalineCore/Datastore/CorpusDatastore.h \
    include/PraalineCore/Datastore/CorpusRepository.h \
    include/PraalineCore/Datastore/CorpusRepositoryDefinition.h \
    include/PraalineCore/Datastore/DatastoreFactory.h \
    include/PraalineCore/Datastore/DatastoreInfo.h \
    include/PraalineCore/Datastore/FileDatastore.h \
    include/PraalineCore/Datastore/MetadataDatastore.h \
    include/PraalineCore/Datastore/NameValueListDatastore.h \
    include/PraalineCore/Diff/dtl/diff.h \
    include/PraalineCore/Diff/dtl/diff3.h \
    include/PraalineCore/Diff/dtl/dtl.h \
    include/PraalineCore/Diff/dtl/functors.h \
    include/PraalineCore/Diff/dtl/lcs.h \
    include/PraalineCore/Diff/dtl/sequence.h \
    include/PraalineCore/Diff/dtl/ses.h \
    include/PraalineCore/Diff/dtl/variables.h \
    include/PraalineCore/Diff/DiffIntervals.h \
    include/PraalineCore/Diff/DiffPoints.h \
    include/PraalineCore/Interfaces/ImportAnnotations.h \
    include/PraalineCore/Interfaces/InterfaceTextFile.h \
    include/PraalineCore/Interfaces/Anvil/AnvilMetadataTranscript.h \
    include/PraalineCore/Interfaces/CONLL/CONLLXDocument.h \
    include/PraalineCore/Interfaces/CSV/CSVFileAnnotation.h \
    include/PraalineCore/Interfaces/Exmaralda/ExmaraldaBasicTranscription.h \
    include/PraalineCore/Interfaces/Exmaralda/ExmaraldaTranscriptionBridge.h \
    include/PraalineCore/Interfaces/Phon/PhonTranscription.h \
    include/PraalineCore/Interfaces/Praat/AnnotationInterfacePraat.h \
    include/PraalineCore/Interfaces/Praat/PraatPitchFile.h \
    include/PraalineCore/Interfaces/Praat/PraatPointTierFile.h \
    include/PraalineCore/Interfaces/Praat/PraatTextFile.h \
    include/PraalineCore/Interfaces/Praat/PraatTextGrid.h \
    include/PraalineCore/Interfaces/Subtitles/SubtitlesFile.h \
    include/PraalineCore/Interfaces/Transcriber/TranscriberAnnotationGraph.h \
    include/PraalineCore/Interfaces/TEI/TEIHeader.h \
    include/PraalineCore/Interfaces/ELAN/ELANAnnotation.h \
    include/PraalineCore/Language/PhonemeDefinitions.h \
    include/PraalineCore/Language/PhoneticAlphabet.h \
    include/PraalineCore/Language/Tokeniser.h \
    include/PraalineCore/Query/Dataset.h \
    include/PraalineCore/Query/DatasetDefinition.h \
    include/PraalineCore/Query/QueryDefinition.h \
    include/PraalineCore/Query/QueryFilterGroup.h \
    include/PraalineCore/Query/QueryFilterSequence.h \
    include/PraalineCore/Query/QueryOccurrence.h \
    include/PraalineCore/Serialisers/Base/SerialiserAnnotation.h \
    include/PraalineCore/Serialisers/Base/SerialiserMetadata.h \
    include/PraalineCore/Serialisers/Base/SerialiserAnnotationStructure.h \
    include/PraalineCore/Serialisers/Base/SerialiserMetadataStructure.h \
    include/PraalineCore/Serialisers/Base/SerialiserNameValueList.h \
    include/PraalineCore/Serialisers/JSON/JSONSerialiserBase.h \
    include/PraalineCore/Serialisers/JSON/JSONSerialiserAnnotation.h \
    include/PraalineCore/Serialisers/JSON/JSONSerialiserMetadata.h \
    include/PraalineCore/Serialisers/JSON/JSONSerialiserAnnotationStructure.h \
    include/PraalineCore/Serialisers/JSON/JSONSerialiserCorpusBookmark.h \
    include/PraalineCore/Serialisers/JSON/JSONSerialiserDatasetDefinition.h \
    include/PraalineCore/Serialisers/JSON/JSONSerialiserMetadataStructure.h \
    include/PraalineCore/Serialisers/JSON/JSONSerialiserNameValueList.h \
    include/PraalineCore/Serialisers/JSON/JSONSerialiserQueryDefinition.h \
    include/PraalineCore/Serialisers/XML/XMLSerialiserBase.h \
    include/PraalineCore/Serialisers/XML/XMLSerialiserAnnotation.h \
    include/PraalineCore/Serialisers/XML/XMLSerialiserMetadata.h \
    include/PraalineCore/Serialisers/XML/XMLSerialiserAnnotationStructure.h \
    include/PraalineCore/Serialisers/XML/XMLSerialiserCorpusBookmark.h \
    include/PraalineCore/Serialisers/XML/XMLSerialiserMetadataStructure.h \
    include/PraalineCore/Serialisers/XML/XMLSerialiserNameValueList.h \
    include/PraalineCore/Statistics/HistogramCalculator.h \
    include/PraalineCore/Statistics/Measures.h \
    include/PraalineCore/Statistics/SpeakerTimeline.h \
    include/PraalineCore/Statistics/StatisticalMeasureDefinition.h \
    include/PraalineCore/Statistics/StatisticalSummary.h \
    include/PraalineCore/Statistics/WordAlign.h \
    include/PraalineCore/Structure/AnnotationStructure.h \
    include/PraalineCore/Structure/AnnotationStructureAttribute.h \
    include/PraalineCore/Structure/AnnotationStructureLevel.h \
    include/PraalineCore/Structure/MetadataStructure.h \
    include/PraalineCore/Structure/MetadataStructureAttribute.h \
    include/PraalineCore/Structure/MetadataStructureSection.h \
    include/PraalineCore/Structure/NameValueList.h \
    include/PraalineCore/Structure/StructureAttributeBase.h

# Private headers

HEADERS += \
    src/Datastore/SQLAnnotationDatastore.h \
    src/Datastore/SQLMetadataDatastore.h \
    src/Datastore/XMLAnnotationDatastore.h \
    src/Datastore/XMLMetadataDatastore.h \
    src/Serialisers/SQL/SQLQueryEngineAnnotation.h \
    src/Serialisers/SQL/SQLSchemaProxyBase.h \
    src/Serialisers/SQL/SQLSerialiserAnnotation.h \
    src/Serialisers/SQL/SQLSerialiserAnnotationStructure.h \
    src/Serialisers/SQL/SQLSerialiserBase.h \
    src/Serialisers/SQL/SQLSerialiserMetadata.h \
    src/Serialisers/SQL/SQLSerialiserMetadataStructure.h \
    src/Serialisers/SQL/SQLSerialiserNameValueList.h \
    src/Serialisers/SQL/SQLSerialiserSystem.h

SOURCES += \
    src/Base/DataType.cpp \
    src/Base/IDatastore.cpp \
    src/Base/ISaveable.cpp \
    src/Base/RealTime.cpp \
    src/Base/RealValueList.cpp \
    src/Annotation/AnnotationDataTable.cpp \
    src/Annotation/AnnotationElement.cpp \
    src/Annotation/AnnotationTier.cpp \
    src/Annotation/AnnotationTierGroup.cpp \
    src/Annotation/Interval.cpp \
    src/Annotation/IntervalTier.cpp \
    src/Annotation/Point.cpp \
    src/Annotation/PointTier.cpp \
    src/Annotation/Relation.cpp \
    src/Annotation/RelationTier.cpp \
    src/Annotation/Sequence.cpp \
    src/Annotation/SequenceTier.cpp \
    src/Annotation/Transcription.cpp \
    src/Annotation/TreeTier.cpp \
    src/Corpus/Corpus.cpp \
    src/Corpus/CorpusAnnotation.cpp \
    src/Corpus/CorpusBookmark.cpp \
    src/Corpus/CorpusCommunication.cpp \
    src/Corpus/CorpusObject.cpp \
    src/Corpus/CorpusObjectInfo.cpp \
    src/Corpus/CorpusParticipation.cpp \
    src/Corpus/CorpusRecording.cpp \
    src/Corpus/CorpusSpeaker.cpp \
    src/Corpus/CorpusSpeakerRelation.cpp \
    src/Dataframe/DataFrame.cpp \
    src/Datastore/AnnotationDatastore.cpp \
    src/Datastore/CorpusDatastore.cpp \
    src/Datastore/CorpusRepository.cpp \
    src/Datastore/CorpusRepositoryDefinition.cpp \
    src/Datastore/DatastoreFactory.cpp \
    src/Datastore/FileDatastore.cpp \
    src/Datastore/MetadataDatastore.cpp \
    src/Datastore/NameValueListDatastore.cpp \
    src/Datastore/SQLAnnotationDatastore.cpp \
    src/Datastore/SQLMetadataDatastore.cpp \
    src/Datastore/XMLAnnotationDatastore.cpp \
    src/Datastore/XMLMetadataDatastore.cpp \
    src/Diff/DiffIntervals.cpp \
    src/Diff/DiffPoints.cpp \
    src/Interfaces/ImportAnnotations.cpp \
    src/Interfaces/InterfaceTextFile.cpp \
    src/Interfaces/Anvil/AnvilMetadataTranscript.cpp \
    src/Interfaces/CONLL/CONLLXDocument.cpp \
    src/Interfaces/CSV/CSVFileAnnotation.cpp \
    src/Interfaces/Exmaralda/ExmaraldaBasicTranscription.cpp \
    src/Interfaces/Exmaralda/ExmaraldaTranscriptionBridge.cpp \
    src/Interfaces/Phon/PhonTranscription.cpp \
    src/Interfaces/Praat/AnnotationInterfacePraat.cpp \
    src/Interfaces/Praat/PraatPitchFile.cpp \
    src/Interfaces/Praat/PraatPointTierFile.cpp \
    src/Interfaces/Praat/PraatTextFile.cpp \
    src/Interfaces/Praat/PraatTextGrid.cpp \
    src/Interfaces/Subtitles/SubtitlesFile.cpp \
    src/Interfaces/Transcriber/TranscriberAnnotationGraph.cpp \
    src/Interfaces/TEI/TEIHeader.cpp \
    src/Interfaces/ELAN/ELANAnnotation.cpp \
    src/Language/PhonemeDefinitions.cpp \
    src/Language/PhoneticAlphabet.cpp \
    src/Language/Tokeniser.cpp \
    src/Query/Dataset.cpp \
    src/Query/DatasetDefinition.cpp \
    src/Query/QueryDefinition.cpp \
    src/Query/QueryFilterGroup.cpp \
    src/Query/QueryFilterSequence.cpp \
    src/Query/QueryOccurrence.cpp \
    src/Serialisers/Base/SerialiserAnnotation.cpp \
    src/Serialisers/Base/SerialiserAnnotationStructure.cpp \
    src/Serialisers/Base/SerialiserMetadata.cpp \
    src/Serialisers/Base/SerialiserMetadataStructure.cpp \
    src/Serialisers/Base/SerialiserNameValueList.cpp \
    src/Serialisers/JSON/JSONSerialiserAnnotation.cpp \
    src/Serialisers/JSON/JSONSerialiserAnnotationStructure.cpp \
    src/Serialisers/JSON/JSONSerialiserBase.cpp \
    src/Serialisers/JSON/JSONSerialiserCorpusBookmark.cpp \
    src/Serialisers/JSON/JSONSerialiserDatasetDefinition.cpp \
    src/Serialisers/JSON/JSONSerialiserMetadata.cpp \
    src/Serialisers/JSON/JSONSerialiserMetadataStructure.cpp \
    src/Serialisers/JSON/JSONSerialiserNameValueList.cpp \
    src/Serialisers/JSON/JSONSerialiserQueryDefinition.cpp \
    src/Serialisers/SQL/SQLQueryEngineAnnotation.cpp \
    src/Serialisers/SQL/SQLSchemaProxyBase.cpp \
    src/Serialisers/SQL/SQLSerialiserAnnotation.cpp \
    src/Serialisers/SQL/SQLSerialiserAnnotationStructure.cpp \
    src/Serialisers/SQL/SQLSerialiserBase.cpp \
    src/Serialisers/SQL/SQLSerialiserMetadata.cpp \
    src/Serialisers/SQL/SQLSerialiserMetadataStructure.cpp \
    src/Serialisers/SQL/SQLSerialiserNameValueList.cpp \
    src/Serialisers/SQL/SQLSerialiserSystem.cpp \
    src/Serialisers/XML/XMLSerialiserAnnotation.cpp \
    src/Serialisers/XML/XMLSerialiserAnnotationStructure.cpp \
    src/Serialisers/XML/XMLSerialiserBase.cpp \
    src/Serialisers/XML/XMLSerialiserCorpusBookmark.cpp \
    src/Serialisers/XML/XMLSerialiserMetadata.cpp \
    src/Serialisers/XML/XMLSerialiserMetadataStructure.cpp \
    src/Serialisers/XML/XMLSerialiserNameValueList.cpp \
    src/Statistics/HistogramCalculator.cpp \
    src/Statistics/Measures.cpp \
    src/Statistics/SpeakerTimeline.cpp \
    src/Statistics/StatisticalMeasureDefinition.cpp \
    src/Statistics/StatisticalSummary.cpp \
    src/Statistics/WordAlign.cpp \
    src/Structure/AnnotationStructure.cpp \
    src/Structure/AnnotationStructureAttribute.cpp \
    src/Structure/AnnotationStructureLevel.cpp \
    src/Structure/MetadataStructure.cpp \
    src/Structure/MetadataStructureAttribute.cpp \
    src/Structure/MetadataStructureSection.cpp \
    src/Structure/NameValueList.cpp \
    src/Structure/StructureAttributeBase.cpp

DISTFILES += \
    Doxyfile
