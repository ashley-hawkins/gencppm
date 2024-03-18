module;
#include "clang_parse.hpp"
export module clang.Parse;

export {
namespace clang {
using ::clang::LoopHint;
using ::clang::Preprocessor;
using ::clang::ASTConsumer;
using ::clang::ASTContext;
using ::clang::CodeCompleteConsumer;
using ::clang::Sema;
using ::clang::ParseAST;
using ::clang::PragmaHandler;
using ::clang::Scope;
using ::clang::BalancedDelimiterTracker;
using ::clang::CorrectionCandidateCallback;
using ::clang::DeclGroupRef;
using ::clang::DiagnosticBuilder;
using ::clang::Parser;
using ::clang::ParsingDeclRAIIObject;
using ::clang::ParsingDeclSpec;
using ::clang::ParsingDeclarator;
using ::clang::ParsingFieldDeclarator;
using ::clang::ColonProtectionRAIIObject;
using ::clang::InMessageExpressionRAIIObject;
using ::clang::PoisonSEHIdentifiersRAIIObject;
using ::clang::OMPClause;
using ::clang::ObjCTypeParamList;
using ::clang::OMPTraitProperty;
using ::clang::OMPTraitSelector;
using ::clang::OMPTraitSet;
using ::clang::OMPTraitInfo;
using ::clang::SuppressAccessChecks;
using ::clang::ExtensionRAIIObject;
using ::clang::ParsingOpenMPDirectiveRAII;
using ::clang::GreaterThanIsOperatorScope;
using ::clang::OffsetOfStateRAIIObject;
using ::clang::ParenBraceBracketBalancer;
} // namespace clang
}
