module;
#include "clang_lex.hpp"
export module clang.Lex;

export {
namespace clang {
using ::clang::IdentifierInfo;
using ::clang::MacroInfo;
using ::clang::CodeCompletionHandler;
namespace tok {
using ::clang::tok::TokenKind;
} // namespace tok
using ::clang::DiagnosticsEngine;
namespace dependency_directives_scan {
using ::clang::dependency_directives_scan::Token;
using ::clang::dependency_directives_scan::DirectiveKind;
using ::clang::dependency_directives_scan::Directive;
} // namespace dependency_directives_scan
using ::clang::scanSourceForDependencyDirectives;
using ::clang::printDependencyDirectivesAsSource;
using ::clang::DirectoryEntry;
using ::clang::FileEntry;
using ::clang::FileManager;
using ::clang::HeaderSearch;
using ::clang::SourceManager;
using ::clang::ModuleMapCallbacks;
using ::clang::ModuleMap;
using ::clang::HeaderMap;
using ::clang::Module;
using ::clang::DirectoryLookup;
using ::clang::ExternalPreprocessorSource;
using ::clang::HMapBucket;
using ::clang::HMapHeader;
using ::clang::HeaderMapImpl;
using ::clang::HeaderSearchOptions;
using ::clang::LangOptions;
using ::clang::Preprocessor;
using ::clang::TargetInfo;
using ::clang::HeaderFileInfo;
using ::clang::ExternalHeaderFileInfoSource;
using ::clang::FrameworkCacheEntry;
namespace detail {
using ::clang::detail::Qualified;
using ::clang::detail::SearchDirIteratorImpl;
} // namespace detail
using ::clang::ConstSearchDirIterator;
using ::clang::SearchDirIterator;
using ::clang::ConstSearchDirRange;
using ::clang::SearchDirRange;
using ::clang::ApplyHeaderSearchOptions;
namespace frontend {
using ::clang::frontend::IncludeDirGroup;
} // namespace frontend
using ::clang::hash_value;
using ::clang::addHash;
using ::clang::MultipleIncludeOpt;
using ::clang::Token;
using ::clang::PPConditionalInfo;
using ::clang::PragmaLoopHintInfo;
using ::clang::PreprocessorLexer;
using ::clang::DiagnosticBuilder;
using ::clang::ConflictMarkerKind;
using ::clang::PreambleBounds;
using ::clang::Lexer;
using ::clang::SourceLocation;
using ::clang::expandUCNs;
using ::clang::NumericLiteralParser;
using ::clang::CharLiteralParser;
using ::clang::StringLiteralEvalMethod;
using ::clang::StringLiteralParser;
using ::clang::MacroArgs;
using ::clang::DefMacroDirective;
using ::clang::MacroDirective;
using ::clang::UndefMacroDirective;
using ::clang::VisibilityMacroDirective;
using ::clang::ModuleMacro;
using ::clang::MacroDefinition;
using ::clang::GlobalModuleIndex;
using ::clang::ModuleIdPath;
using ::clang::ModuleLoadResult;
using ::clang::ModuleLoader;
using ::clang::TrivialModuleLoader;
using ::clang::PragmaNamespace;
using ::clang::PragmaIntroducerKind;
using ::clang::PragmaIntroducer;
using ::clang::PragmaHandler;
using ::clang::EmptyPragmaHandler;
using ::clang::prepare_PragmaString;
using ::clang::PPCallbacks;
using ::clang::PPChainedCallbacks;
using ::clang::PPConditionalDirectiveRecord;
using ::clang::PreprocessingRecord;
using ::clang::PreprocessedEntity;
using ::clang::PreprocessingDirective;
using ::clang::MacroDefinitionRecord;
using ::clang::MacroExpansion;
using ::clang::InclusionDirective;
using ::clang::ExternalPreprocessingRecordSource;
using ::clang::VAOptExpansionContext;
using ::clang::TokenLexer;
using ::clang::CommentHandler;
using ::clang::EmptylineHandler;
using ::clang::PreprocessorOptions;
using ::clang::ScratchBuffer;
namespace Builtin {
using ::clang::Builtin::Context;
} // namespace Builtin
using ::clang::TokenValue;
using ::clang::MacroUse;
using ::clang::PragmaHandlerRegistry;
using ::clang::ObjCXXARCStandardLibraryKind;
using ::clang::DisableValidationForModuleKind;
using ::clang::TokenConcatenation;
using ::clang::VariadicMacroScopeGuard;
using ::clang::VAOptDefinitionContext;
} // namespace clang
namespace llvm {
using ::llvm::Triple;
using ::llvm::MemoryBufferRef;
using ::llvm::SmallString;
using ::llvm::MemoryBuffer;
} // namespace llvm
}
