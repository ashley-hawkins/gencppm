module;
#include "clang_rewrite.hpp"
export module clang.Rewrite;

export {
namespace clang {
using ::clang::DeltaTree;
using ::clang::Rewriter;
using ::clang::RewriteBuffer;
using ::clang::Preprocessor;
namespace html {
using ::clang::html::HighlightRange;
using ::clang::html::EscapeText;
using ::clang::html::AddLineNumbers;
using ::clang::html::AddHeaderFooterInternalBuiltinCSS;
using ::clang::html::SyntaxHighlight;
using ::clang::html::HighlightMacros;
} // namespace html
using ::clang::RopeRefCountString;
using ::clang::RopePiece;
using ::clang::RopePieceBTreeIterator;
using ::clang::RopePieceBTree;
using ::clang::RewriteRope;
using ::clang::LangOptions;
using ::clang::SourceManager;
using ::clang::ScratchBuffer;
using ::clang::TokenRewriter;
using ::clang::ASTConsumer;
using ::clang::DiagnosticsEngine;
using ::clang::CreateObjCRewriter;
using ::clang::CreateModernObjCRewriter;
using ::clang::CreateHTMLPrinter;
using ::clang::FixItOptions;
using ::clang::FixItRewriter;
using ::clang::HTMLPrintAction;
using ::clang::FixItAction;
using ::clang::FixItRecompile;
using ::clang::RewriteObjCAction;
using ::clang::RewriteMacrosAction;
using ::clang::RewriteTestAction;
using ::clang::RewriteIncludesAction;
using ::clang::PreprocessorOutputOptions;
using ::clang::RewriteMacrosInInput;
using ::clang::DoRewriteTest;
using ::clang::RewriteIncludesInInput;
} // namespace clang
}
