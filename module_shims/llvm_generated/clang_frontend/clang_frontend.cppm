module;
#include "clang_frontend.hpp"
export module clang.Frontend;

export {
namespace clang {
using ::clang::ASTConsumer;
using ::clang::CreateASTPrinter;
using ::clang::CreateASTDumper;
using ::clang::CreateASTDeclNodeLister;
using ::clang::CreateASTViewer;
using ::clang::CompilerInstance;
using ::clang::CompilerInvocation;
using ::clang::Decl;
using ::clang::DeclGroupRef;
using ::clang::PCHContainerOperations;
using ::clang::ComputePreambleBounds;
using ::clang::PreambleCallbacks;
using ::clang::PrecompiledPreamble;
using ::clang::BuildPreambleError;
using ::clang::BuildPreambleErrorCategory;
using ::clang::make_error_code;
using ::clang::ASTContext;
using ::clang::ASTDeserializationListener;
using ::clang::ASTMutationListener;
using ::clang::ASTReader;
using ::clang::FileEntry;
using ::clang::FileManager;
using ::clang::FrontendAction;
using ::clang::HeaderSearch;
using ::clang::InputKind;
using ::clang::InMemoryModuleCache;
using ::clang::PCHContainerReader;
using ::clang::Preprocessor;
using ::clang::PreprocessorOptions;
using ::clang::Sema;
using ::clang::TargetInfo;
using ::clang::SkipFunctionBodiesScope;
using ::clang::CaptureDiagsKind;
using ::clang::ASTUnit;
using ::clang::LangOptions;
using ::clang::ChainedDiagnosticConsumer;
using ::clang::ParsedSourceLocation;
using ::clang::ParsedSourceRange;
using ::clang::ShowIncludesDestination;
using ::clang::DependencyOutputFormat;
using ::clang::ExtraDepKind;
using ::clang::DependencyOutputOptions;
namespace frontend {
using ::clang::frontend::ActionKind;
} // namespace frontend
using ::clang::FrontendInputFile;
using ::clang::FrontendOptions;
using ::clang::MigratorOptions;
using ::clang::PreprocessorOutputOptions;
using ::clang::DiagnosticsEngine;
using ::clang::HeaderSearchOptions;
using ::clang::TargetOptions;
using ::clang::CreateAndPopulateDiagOpts;
using ::clang::ParseDiagnosticArgs;
using ::clang::CompilerInvocationRefBase;
using ::clang::CompilerInvocationValueBase;
using ::clang::createVFSFromCompilerInvocation;
using ::clang::createVFSFromOverlayFiles;
using ::clang::ExternalSemaSource;
using ::clang::InitializePreprocessor;
using ::clang::DoPrintPreprocessedInput;
using ::clang::DependencyCollector;
using ::clang::DependencyFileGenerator;
using ::clang::ModuleDependencyCollector;
using ::clang::AttachDependencyGraphGen;
using ::clang::AttachHeaderIncludeGen;
using ::clang::createChainedIncludesSource;
using ::clang::CreateInvocationOptions;
using ::clang::createInvocation;
using ::clang::CodeCompleteConsumer;
using ::clang::DiagnosticConsumer;
using ::clang::Module;
using ::clang::SourceManager;
using ::clang::DisableValidationForModuleKind;
using ::clang::DiagOrStoredDiag;
using ::clang::DiagnosticRenderer;
using ::clang::DiagnosticNoteRenderer;
using ::clang::ASTMergeAction;
using ::clang::ASTFrontendAction;
using ::clang::PluginASTAction;
using ::clang::PreprocessorFrontendAction;
using ::clang::WrapperFrontendAction;
using ::clang::InitOnlyAction;
using ::clang::ReadPCHAndPreprocessAction;
using ::clang::DumpCompilerOptionsAction;
using ::clang::ASTPrintAction;
using ::clang::ASTDumpAction;
using ::clang::ASTDeclListAction;
using ::clang::ASTViewAction;
using ::clang::GeneratePCHAction;
using ::clang::GenerateModuleAction;
using ::clang::GenerateInterfaceStubsAction;
using ::clang::GenerateModuleFromModuleMapAction;
using ::clang::GenerateModuleInterfaceAction;
using ::clang::GenerateHeaderUnitAction;
using ::clang::SyntaxOnlyAction;
using ::clang::DumpModuleInfoAction;
using ::clang::VerifyPCHAction;
using ::clang::TemplightDumpAction;
using ::clang::PrintPreambleAction;
using ::clang::PrintDependencyDirectivesSourceMinimizerAction;
using ::clang::DumpRawTokensAction;
using ::clang::DumpTokensAction;
using ::clang::PreprocessOnlyAction;
using ::clang::PrintPreprocessedAction;
using ::clang::GetDependenciesByModuleNameAction;
using ::clang::FrontendPluginRegistry;
using ::clang::LayoutOverrideSource;
using ::clang::DiagnosticOptions;
using ::clang::LogDiagnosticPrinter;
using ::clang::MultiplexASTMutationListener;
using ::clang::MultiplexASTDeserializationListener;
using ::clang::MultiplexConsumer;
using ::clang::SARIFDiagnostic;
using ::clang::SarifDocumentWriter;
using ::clang::SARIFDiagnosticPrinter;
namespace serialized_diags {
using ::clang::serialized_diags::BlockIDs;
using ::clang::serialized_diags::RecordIDs;
using ::clang::serialized_diags::Level;
using ::clang::serialized_diags::create;
using ::clang::serialized_diags::SDError;
using ::clang::serialized_diags::SDErrorCategory;
using ::clang::serialized_diags::make_error_code;
using ::clang::serialized_diags::Location;
using ::clang::serialized_diags::SerializedDiagnosticReader;
} // namespace serialized_diags
using ::clang::TextDiagnostic;
using ::clang::TextDiagnosticBuffer;
using ::clang::TextDiagnosticPrinter;
using ::clang::VerifyDiagnosticConsumer;
} // namespace clang
namespace llvm {
using ::llvm::MemoryBuffer;
using ::llvm::MemoryBufferRef;
namespace vfs {
using ::llvm::vfs::FileSystem;
} // namespace vfs
namespace cl {
using ::llvm::cl::parser;
} // namespace cl
using ::llvm::Triple;
namespace opt {
using ::llvm::opt::ArgList;
} // namespace opt
using ::llvm::raw_fd_ostream;
using ::llvm::Timer;
using ::llvm::TimerGroup;
using ::llvm::raw_ostream;
} // namespace llvm
namespace std {
using ::std::is_error_code_enum;
} // namespace std
}
