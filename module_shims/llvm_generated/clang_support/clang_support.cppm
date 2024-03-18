module;
#include "clang_support.hpp"
export module clang.Support;

export {
namespace llvm {
using ::llvm::raw_ostream;
} // namespace llvm
namespace clang {
namespace RISCV {
using ::clang::RISCV::VScaleVal;
using ::clang::RISCV::VectorTypeModifier;
using ::clang::RISCV::BaseTypeModifier;
using ::clang::RISCV::TypeModifier;
using ::clang::RISCV::Policy;
using ::clang::RISCV::PrototypeDescriptor;
using ::clang::RISCV::parsePrototypes;
using ::clang::RISCV::BasicType;
using ::clang::RISCV::ScalarTypeKind;
using ::clang::RISCV::LMULType;
using ::clang::RISCV::RVVType;
using ::clang::RISCV::RVVTypePtr;
using ::clang::RISCV::RVVTypes;
using ::clang::RISCV::RVVTypeCache;
using ::clang::RISCV::PolicyScheme;
using ::clang::RISCV::RVVIntrinsic;
using ::clang::RISCV::RVVRequire;
using ::clang::RISCV::RVVIntrinsicRecord;
} // namespace RISCV
} // namespace clang
}
