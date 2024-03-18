module;
#include "llvm_support.hpp"
export module LLVM.Support;

export {
namespace llvm {
namespace AMDGPU {
namespace HSAMD {
using ::llvm::AMDGPU::HSAMD::AccessQualifier;
using ::llvm::AMDGPU::HSAMD::AddressSpaceQualifier;
using ::llvm::AMDGPU::HSAMD::ValueKind;
using ::llvm::AMDGPU::HSAMD::ValueType;
namespace Kernel {
namespace Attrs {
using ::llvm::AMDGPU::HSAMD::Kernel::Attrs::Metadata;
} // namespace Attrs
namespace Arg {
using ::llvm::AMDGPU::HSAMD::Kernel::Arg::Metadata;
} // namespace Arg
namespace CodeProps {
using ::llvm::AMDGPU::HSAMD::Kernel::CodeProps::Metadata;
} // namespace CodeProps
namespace DebugProps {
using ::llvm::AMDGPU::HSAMD::Kernel::DebugProps::Metadata;
} // namespace DebugProps
using ::llvm::AMDGPU::HSAMD::Kernel::Metadata;
} // namespace Kernel
using ::llvm::AMDGPU::HSAMD::Metadata;
using ::llvm::AMDGPU::HSAMD::fromString;
using ::llvm::AMDGPU::HSAMD::toString;
} // namespace HSAMD
namespace PALMD {
using ::llvm::AMDGPU::PALMD::Key;
} // namespace PALMD
} // namespace AMDGPU
namespace amdhsa {
using ::llvm::amdhsa::kernel_descriptor_t;
} // namespace amdhsa
using ::llvm::StringRef;
using ::llvm::Twine;
using ::llvm::install_fatal_error_handler;
using ::llvm::remove_fatal_error_handler;
using ::llvm::ScopedFatalErrorHandler;
using ::llvm::report_fatal_error;
using ::llvm::install_bad_alloc_error_handler;
using ::llvm::remove_bad_alloc_error_handler;
using ::llvm::install_out_of_memory_new_handler;
using ::llvm::report_bad_alloc_error;
using ::llvm::llvm_unreachable_internal;
namespace sys {
using ::llvm::sys::getSwappedBytes;
using ::llvm::sys::swapByteOrder;
namespace fs {
using ::llvm::sys::fs::FileAccess;
using ::llvm::sys::fs::OpenFlags;
using ::llvm::sys::fs::CreationDisposition;
using ::llvm::sys::fs::FileLocker;
using ::llvm::sys::fs::file_t;
using ::llvm::sys::fs::UniqueID;
using ::llvm::sys::fs::kInvalidFile;
using ::llvm::sys::fs::file_type;
using ::llvm::sys::fs::space_info;
using ::llvm::sys::fs::perms;
using ::llvm::sys::fs::basic_file_status;
using ::llvm::sys::fs::file_status;
using ::llvm::sys::fs::make_absolute;
using ::llvm::sys::fs::create_directories;
using ::llvm::sys::fs::create_directory;
using ::llvm::sys::fs::create_link;
using ::llvm::sys::fs::create_hard_link;
using ::llvm::sys::fs::real_path;
using ::llvm::sys::fs::expand_tilde;
using ::llvm::sys::fs::current_path;
using ::llvm::sys::fs::set_current_path;
using ::llvm::sys::fs::remove;
using ::llvm::sys::fs::remove_directories;
using ::llvm::sys::fs::rename;
using ::llvm::sys::fs::copy_file;
using ::llvm::sys::fs::resize_file;
using ::llvm::sys::fs::resize_file_before_mapping_readwrite;
using ::llvm::sys::fs::md5_contents;
using ::llvm::sys::fs::exists;
using ::llvm::sys::fs::AccessMode;
using ::llvm::sys::fs::access;
using ::llvm::sys::fs::can_execute;
using ::llvm::sys::fs::can_write;
using ::llvm::sys::fs::equivalent;
using ::llvm::sys::fs::is_local;
using ::llvm::sys::fs::get_file_type;
using ::llvm::sys::fs::is_directory;
using ::llvm::sys::fs::is_regular_file;
using ::llvm::sys::fs::is_symlink_file;
using ::llvm::sys::fs::is_other;
using ::llvm::sys::fs::status;
using ::llvm::sys::fs::getUmask;
using ::llvm::sys::fs::setPermissions;
using ::llvm::sys::fs::getPermissions;
using ::llvm::sys::fs::file_size;
using ::llvm::sys::fs::setLastAccessAndModificationTime;
using ::llvm::sys::fs::status_known;
using ::llvm::sys::fs::createUniquePath;
using ::llvm::sys::fs::createUniqueFile;
using ::llvm::sys::fs::TempFile;
using ::llvm::sys::fs::createTemporaryFile;
using ::llvm::sys::fs::createUniqueDirectory;
using ::llvm::sys::fs::getPotentiallyUniqueFileName;
using ::llvm::sys::fs::getPotentiallyUniqueTempFileName;
using ::llvm::sys::fs::openFile;
using ::llvm::sys::fs::openNativeFile;
using ::llvm::sys::fs::convertFDToNativeFile;
using ::llvm::sys::fs::getStdinHandle;
using ::llvm::sys::fs::getStdoutHandle;
using ::llvm::sys::fs::getStderrHandle;
using ::llvm::sys::fs::readNativeFile;
using ::llvm::sys::fs::readNativeFileToEOF;
using ::llvm::sys::fs::readNativeFileSlice;
using ::llvm::sys::fs::openFileForWrite;
using ::llvm::sys::fs::openNativeFileForWrite;
using ::llvm::sys::fs::openFileForReadWrite;
using ::llvm::sys::fs::openNativeFileForReadWrite;
using ::llvm::sys::fs::openFileForRead;
using ::llvm::sys::fs::openNativeFileForRead;
using ::llvm::sys::fs::tryLockFile;
using ::llvm::sys::fs::lockFile;
using ::llvm::sys::fs::unlockFile;
using ::llvm::sys::fs::closeFile;
using ::llvm::sys::fs::changeFileOwnership;
using ::llvm::sys::fs::getUniqueID;
using ::llvm::sys::fs::disk_space;
using ::llvm::sys::fs::mapped_file_region;
using ::llvm::sys::fs::getMainExecutable;
using ::llvm::sys::fs::directory_entry;
namespace detail {
using ::llvm::sys::fs::detail::DirIterState;
using ::llvm::sys::fs::detail::directory_iterator_construct;
using ::llvm::sys::fs::detail::directory_iterator_increment;
using ::llvm::sys::fs::detail::directory_iterator_destruct;
using ::llvm::sys::fs::detail::RecDirIterState;
} // namespace detail
using ::llvm::sys::fs::directory_iterator;
using ::llvm::sys::fs::recursive_directory_iterator;
} // namespace fs
using ::llvm::sys::MemoryFence;
using ::llvm::sys::CompareAndSwap;
using ::llvm::sys::COMThreadingMode;
using ::llvm::sys::InitializeCOMRAII;
using ::llvm::sys::TimePoint;
using ::llvm::sys::toTimeT;
using ::llvm::sys::toTimePoint;
using ::llvm::sys::DynamicLibrary;
using ::llvm::sys::StrError;
using ::llvm::sys::RetryAfterSignal;
namespace path {
using ::llvm::sys::path::Style;
using ::llvm::sys::path::is_style_posix;
using ::llvm::sys::path::is_style_windows;
using ::llvm::sys::path::const_iterator;
using ::llvm::sys::path::reverse_iterator;
using ::llvm::sys::path::begin;
using ::llvm::sys::path::end;
using ::llvm::sys::path::rbegin;
using ::llvm::sys::path::rend;
using ::llvm::sys::path::remove_filename;
using ::llvm::sys::path::replace_extension;
using ::llvm::sys::path::replace_path_prefix;
using ::llvm::sys::path::remove_leading_dotslash;
using ::llvm::sys::path::remove_dots;
using ::llvm::sys::path::append;
using ::llvm::sys::path::native;
using ::llvm::sys::path::make_preferred;
using ::llvm::sys::path::convert_to_slash;
using ::llvm::sys::path::root_name;
using ::llvm::sys::path::root_directory;
using ::llvm::sys::path::root_path;
using ::llvm::sys::path::relative_path;
using ::llvm::sys::path::parent_path;
using ::llvm::sys::path::filename;
using ::llvm::sys::path::stem;
using ::llvm::sys::path::extension;
using ::llvm::sys::path::is_separator;
using ::llvm::sys::path::get_separator;
using ::llvm::sys::path::system_temp_directory;
using ::llvm::sys::path::home_directory;
using ::llvm::sys::path::user_config_directory;
using ::llvm::sys::path::cache_directory;
using ::llvm::sys::path::has_root_name;
using ::llvm::sys::path::has_root_directory;
using ::llvm::sys::path::has_root_path;
using ::llvm::sys::path::has_relative_path;
using ::llvm::sys::path::has_parent_path;
using ::llvm::sys::path::has_filename;
using ::llvm::sys::path::has_stem;
using ::llvm::sys::path::has_extension;
using ::llvm::sys::path::is_absolute;
using ::llvm::sys::path::is_absolute_gnu;
using ::llvm::sys::path::is_relative;
} // namespace path
namespace locale {
using ::llvm::sys::locale::columnWidth;
using ::llvm::sys::locale::isPrint;
} // namespace locale
using ::llvm::sys::MemoryBlock;
using ::llvm::sys::Memory;
using ::llvm::sys::OwningMemoryBlock;
using ::llvm::sys::SmartMutex;
using ::llvm::sys::SmartScopedLock;
using ::llvm::sys::ProcessInfo;
using ::llvm::sys::ProcessStatistics;
using ::llvm::sys::findProgramByName;
using ::llvm::sys::ChangeStdinMode;
using ::llvm::sys::ChangeStdoutMode;
using ::llvm::sys::ChangeStdinToBinary;
using ::llvm::sys::ChangeStdoutToBinary;
using ::llvm::sys::ExecuteAndWait;
using ::llvm::sys::ExecuteNoWait;
using ::llvm::sys::commandLineFitsWithinSystemLimits;
using ::llvm::sys::WindowsEncodingMethod;
using ::llvm::sys::writeFileWithEncoding;
using ::llvm::sys::Wait;
using ::llvm::sys::printArg;
using ::llvm::sys::Process;
using ::llvm::sys::SmartRWMutex;
using ::llvm::sys::SmartScopedReader;
using ::llvm::sys::SmartScopedWriter;
using ::llvm::sys::RunInterruptHandlers;
using ::llvm::sys::RemoveFileOnSignal;
using ::llvm::sys::DontRemoveFileOnSignal;
using ::llvm::sys::PrintStackTraceOnErrorSignal;
using ::llvm::sys::DisableSystemDialogsOnCrash;
using ::llvm::sys::PrintStackTrace;
using ::llvm::sys::RunSignalHandlers;
using ::llvm::sys::SignalHandlerCallback;
using ::llvm::sys::AddSignalHandler;
using ::llvm::sys::SetInterruptFunction;
using ::llvm::sys::SetInfoSignalFunction;
using ::llvm::sys::SetOneShotPipeSignalFunction;
using ::llvm::sys::DefaultOneShotPipeSignalHandler;
using ::llvm::sys::CleanupOnSignal;
using ::llvm::sys::unregisterHandlers;
namespace unicode {
using ::llvm::sys::unicode::ColumnWidthErrors;
using ::llvm::sys::unicode::isPrintable;
using ::llvm::sys::unicode::isFormatting;
using ::llvm::sys::unicode::columnWidthUTF8;
using ::llvm::sys::unicode::foldCharSimple;
using ::llvm::sys::unicode::nameToCodepointStrict;
using ::llvm::sys::unicode::LooseMatchingResult;
using ::llvm::sys::unicode::nameToCodepointLooseMatching;
using ::llvm::sys::unicode::MatchForCodepointName;
using ::llvm::sys::unicode::nearestMatchesForCodepointName;
} // namespace unicode
using ::llvm::sys::UnicodeCharRange;
using ::llvm::sys::UnicodeCharSet;
using ::llvm::sys::RunningOnValgrind;
using ::llvm::sys::ValgrindDiscardTranslations;
using ::llvm::sys::Watchdog;
} // namespace sys
using ::llvm::is_integral_or_enum;
using ::llvm::add_lvalue_reference_if_not_pointer;
using ::llvm::add_const_past_pointer;
using ::llvm::const_pointer_or_const_ref;
namespace detail {
using ::llvm::detail::trivial_helper;
using ::llvm::detail::AllocatorHolder;
using ::llvm::detail::printBumpPtrAllocatorStats;
using ::llvm::detail::ConstantLog2;
using ::llvm::detail::HasPointerLikeTypeTraits;
using ::llvm::detail::IsPointerLike;
using ::llvm::detail::SelfType;
using ::llvm::detail::isPresent;
using ::llvm::detail::unwrapValue;
using ::llvm::detail::reverse_if_helper;
using ::llvm::detail::reverse_if;
using ::llvm::detail::format_adapter;
using ::llvm::detail::provider_format_adapter;
using ::llvm::detail::stream_operator_format_adapter;
using ::llvm::detail::missing_format_adapter;
using ::llvm::detail::has_FormatProvider;
using ::llvm::detail::has_StreamOperator;
using ::llvm::detail::uses_format_member;
using ::llvm::detail::uses_format_provider;
using ::llvm::detail::uses_stream_operator;
using ::llvm::detail::uses_missing_provider;
using ::llvm::detail::build_format_adapter;
using ::llvm::detail::use_integral_formatter;
using ::llvm::detail::use_char_formatter;
using ::llvm::detail::is_cstring;
using ::llvm::detail::use_string_formatter;
using ::llvm::detail::use_pointer_formatter;
using ::llvm::detail::use_double_formatter;
using ::llvm::detail::HelperFunctions;
using ::llvm::detail::IterValue;
using ::llvm::detail::range_item_has_provider;
using ::llvm::detail::unit;
using ::llvm::detail::AlignAdapter;
using ::llvm::detail::PadAdapter;
using ::llvm::detail::RepeatAdapter;
using ::llvm::detail::ErrorAdapter;
using ::llvm::detail::has_hoist_check;
using ::llvm::detail::detect_has_hoist_check;
using ::llvm::detail::isLegalToHoistInto;
} // namespace detail
using ::llvm::is_copy_assignable;
using ::llvm::is_move_assignable;
using ::llvm::TagNameItem;
using ::llvm::TagNameMap;
namespace ELFAttrs {
using ::llvm::ELFAttrs::AttrType;
using ::llvm::ELFAttrs::attrTypeAsString;
using ::llvm::ELFAttrs::attrTypeFromString;
using ::llvm::ELFAttrs::AttrMagic;
} // namespace ELFAttrs
namespace ARMBuildAttrs {
using ::llvm::ARMBuildAttrs::getARMAttributeTags;
using ::llvm::ARMBuildAttrs::SpecialAttr;
using ::llvm::ARMBuildAttrs::AttrType;
using ::llvm::ARMBuildAttrs::CPUArch;
using ::llvm::ARMBuildAttrs::CPUArchProfile;
} // namespace ARMBuildAttrs
using ::llvm::AlignedCharArrayUnion;
using ::llvm::raw_ostream;
using ::llvm::isCurrentDebugType;
using ::llvm::setCurrentDebugType;
using ::llvm::setCurrentDebugTypes;
using ::llvm::DebugFlag;
using ::llvm::EnableDebugBuffering;
using ::llvm::dbgs;
using ::llvm::ErrorOr;
using ::llvm::format_object_base;
using ::llvm::validate_format_parameters;
using ::llvm::format_object;
using ::llvm::format;
using ::llvm::FormattedString;
using ::llvm::left_justify;
using ::llvm::right_justify;
using ::llvm::center_justify;
using ::llvm::FormattedNumber;
using ::llvm::format_hex;
using ::llvm::format_hex_no_prefix;
using ::llvm::format_decimal;
using ::llvm::FormattedBytes;
using ::llvm::format_bytes;
using ::llvm::format_bytes_with_ascii;
using ::llvm::Duration;
using ::llvm::formatv_object_base;
using ::llvm::Expected;
using ::llvm::raw_pwrite_stream;
using ::llvm::raw_fd_ostream;
using ::llvm::outs;
using ::llvm::errs;
using ::llvm::nulls;
using ::llvm::raw_fd_stream;
using ::llvm::raw_string_ostream;
using ::llvm::raw_svector_ostream;
using ::llvm::raw_null_ostream;
using ::llvm::buffer_ostream;
using ::llvm::buffer_unique_ostream;
using ::llvm::Error;
using ::llvm::writeToOutput;
using ::llvm::ErrorSuccess;
using ::llvm::ErrorInfoBase;
using ::llvm::make_error;
using ::llvm::ErrorInfo;
using ::llvm::ErrorList;
using ::llvm::joinErrors;
using ::llvm::cantFail;
using ::llvm::ErrorHandlerTraits;
using ::llvm::handleErrorImpl;
using ::llvm::handleErrors;
using ::llvm::handleAllErrors;
using ::llvm::handleExpected;
using ::llvm::logAllUnhandledErrors;
using ::llvm::toString;
using ::llvm::consumeError;
using ::llvm::expectedToOptional;
using ::llvm::expectedToStdOptional;
using ::llvm::errorToBool;
using ::llvm::ErrorAsOutParameter;
using ::llvm::ExpectedAsOutParameter;
using ::llvm::ECError;
using ::llvm::inconvertibleErrorCode;
using ::llvm::errorCodeToError;
using ::llvm::errorToErrorCode;
using ::llvm::errorOrToExpected;
using ::llvm::expectedToErrorOr;
using ::llvm::StringError;
using ::llvm::createStringError;
using ::llvm::FileError;
using ::llvm::createFileError;
using ::llvm::ExitOnError;
using ::llvm::wrap;
using ::llvm::unwrap;
using ::llvm::Uint24;
using ::llvm::uint24_t;
using ::llvm::getSwappedBytes;
using ::llvm::DataExtractor;
namespace support {
using ::llvm::support::endianness;
namespace detail {
using ::llvm::support::detail::PickAlignment;
using ::llvm::support::detail::packed_endian_specific_integral;
} // namespace detail
namespace endian {
using ::llvm::support::endian::system_endianness;
using ::llvm::support::endian::byte_swap;
using ::llvm::support::endian::read;
using ::llvm::support::endian::readNext;
using ::llvm::support::endian::write;
using ::llvm::support::endian::make_unsigned_t;
using ::llvm::support::endian::readAtBitAlignment;
using ::llvm::support::endian::writeAtBitAlignment;
using ::llvm::support::endian::read16;
using ::llvm::support::endian::read32;
using ::llvm::support::endian::read64;
using ::llvm::support::endian::read16le;
using ::llvm::support::endian::read32le;
using ::llvm::support::endian::read64le;
using ::llvm::support::endian::read16be;
using ::llvm::support::endian::read32be;
using ::llvm::support::endian::read64be;
using ::llvm::support::endian::write16;
using ::llvm::support::endian::write32;
using ::llvm::support::endian::write64;
using ::llvm::support::endian::write16le;
using ::llvm::support::endian::write32le;
using ::llvm::support::endian::write64le;
using ::llvm::support::endian::write16be;
using ::llvm::support::endian::write32be;
using ::llvm::support::endian::write64be;
using ::llvm::support::endian::Writer;
} // namespace endian
using ::llvm::support::ulittle16_t;
using ::llvm::support::ulittle32_t;
using ::llvm::support::ulittle64_t;
using ::llvm::support::little16_t;
using ::llvm::support::little32_t;
using ::llvm::support::little64_t;
using ::llvm::support::aligned_ulittle16_t;
using ::llvm::support::aligned_ulittle32_t;
using ::llvm::support::aligned_ulittle64_t;
using ::llvm::support::aligned_little16_t;
using ::llvm::support::aligned_little32_t;
using ::llvm::support::aligned_little64_t;
using ::llvm::support::ubig16_t;
using ::llvm::support::ubig32_t;
using ::llvm::support::ubig64_t;
using ::llvm::support::big16_t;
using ::llvm::support::big32_t;
using ::llvm::support::big64_t;
using ::llvm::support::aligned_ubig16_t;
using ::llvm::support::aligned_ubig32_t;
using ::llvm::support::aligned_ubig64_t;
using ::llvm::support::aligned_big16_t;
using ::llvm::support::aligned_big32_t;
using ::llvm::support::aligned_big64_t;
using ::llvm::support::unaligned_uint16_t;
using ::llvm::support::unaligned_uint32_t;
using ::llvm::support::unaligned_uint64_t;
using ::llvm::support::unaligned_int16_t;
using ::llvm::support::unaligned_int32_t;
using ::llvm::support::unaligned_int64_t;
using ::llvm::support::little_t;
using ::llvm::support::big_t;
using ::llvm::support::aligned_little_t;
using ::llvm::support::aligned_big_t;
} // namespace support
using ::llvm::ScopedPrinter;
using ::llvm::ELFAttributeParser;
using ::llvm::ARMAttributeParser;
namespace ARM {
namespace EHABI {
using ::llvm::ARM::EHABI::EHTEntryKind;
using ::llvm::ARM::EHABI::UnwindOpcodes;
using ::llvm::ARM::EHABI::PersonalityRoutineIndex;
} // namespace EHABI
namespace WinEH {
using ::llvm::ARM::WinEH::RuntimeFunctionFlag;
using ::llvm::ARM::WinEH::ReturnType;
using ::llvm::ARM::WinEH::RuntimeFunction;
using ::llvm::ARM::WinEH::PrologueFolding;
using ::llvm::ARM::WinEH::EpilogueFolding;
using ::llvm::ARM::WinEH::StackAdjustment;
using ::llvm::ARM::WinEH::SavedRegisterMask;
using ::llvm::ARM::WinEH::RuntimeFunctionARM64;
using ::llvm::ARM::WinEH::EpilogueScope;
using ::llvm::ARM::WinEH::ExceptionDataRecord;
using ::llvm::ARM::WinEH::HeaderWords;
} // namespace WinEH
} // namespace ARM
using ::llvm::maskTrailingOnes;
using ::llvm::maskLeadingOnes;
using ::llvm::maskTrailingZeros;
using ::llvm::maskLeadingZeros;
using ::llvm::reverseBits;
using ::llvm::Hi_32;
using ::llvm::Lo_32;
using ::llvm::Make_64;
using ::llvm::isInt;
using ::llvm::isShiftedInt;
using ::llvm::isUInt;
using ::llvm::isShiftedUInt;
using ::llvm::maxUIntN;
using ::llvm::minIntN;
using ::llvm::maxIntN;
using ::llvm::isUIntN;
using ::llvm::isIntN;
using ::llvm::isMask_32;
using ::llvm::isMask_64;
using ::llvm::isShiftedMask_32;
using ::llvm::isShiftedMask_64;
using ::llvm::isPowerOf2_32;
using ::llvm::isPowerOf2_64;
using ::llvm::CTLog2;
using ::llvm::Log2_32;
using ::llvm::Log2_64;
using ::llvm::Log2_32_Ceil;
using ::llvm::Log2_64_Ceil;
using ::llvm::MinAlign;
using ::llvm::NextPowerOf2;
using ::llvm::PowerOf2Ceil;
using ::llvm::alignTo;
using ::llvm::alignToPowerOf2;
using ::llvm::divideCeil;
using ::llvm::divideNearest;
using ::llvm::alignDown;
using ::llvm::SignExtend32;
using ::llvm::SignExtend64;
using ::llvm::AbsoluteDifference;
using ::llvm::SaturatingAdd;
using ::llvm::SaturatingMultiply;
using ::llvm::SaturatingMultiplyAdd;
using ::llvm::huge_valf;
using ::llvm::AddOverflow;
using ::llvm::SubOverflow;
using ::llvm::MulOverflow;
using ::llvm::Align;
using ::llvm::assumeAligned;
using ::llvm::MaybeAlign;
using ::llvm::isAligned;
using ::llvm::isAddrAligned;
using ::llvm::alignAddr;
using ::llvm::offsetToAlignment;
using ::llvm::offsetToAlignedAddr;
using ::llvm::Log2;
using ::llvm::commonAlignment;
using ::llvm::encode;
using ::llvm::decodeMaybeAlign;
using ::llvm::DebugStr;
using ::llvm::safe_malloc;
using ::llvm::safe_calloc;
using ::llvm::safe_realloc;
using ::llvm::allocate_buffer;
using ::llvm::deallocate_buffer;
using ::llvm::AllocatorBase;
using ::llvm::MallocAllocator;
using ::llvm::BumpPtrAllocatorImpl;
using ::llvm::SpecificBumpPtrAllocator;
using ::llvm::ArrayRecycler;
using ::llvm::AtomicOrderingCABI;
using ::llvm::isValidAtomicOrderingCABI;
using ::llvm::AtomicOrdering;
using ::llvm::isValidAtomicOrdering;
using ::llvm::toIRString;
using ::llvm::isStrongerThan;
using ::llvm::isAtLeastOrStrongerThan;
using ::llvm::isStrongerThanUnordered;
using ::llvm::isStrongerThanMonotonic;
using ::llvm::isAcquireOrStronger;
using ::llvm::isReleaseOrStronger;
using ::llvm::getMergedAtomicOrdering;
using ::llvm::toCABI;
using ::llvm::PointerLikeTypeTraits;
using ::llvm::FunctionPointerLikeTypeTraits;
using ::llvm::shouldReverseIterate;
using ::llvm::NfaPath;
using ::llvm::NfaStatePair;
namespace internal {
using ::llvm::internal::NfaTranscriber;
} // namespace internal
using ::llvm::Automaton;
using ::llvm::decodePackedBCD;
using ::llvm::BLAKE3Result;
using ::llvm::BLAKE3;
using ::llvm::TruncatedBLAKE3;
using ::llvm::ThreadPool;
using ::llvm::BPFunctionNode;
using ::llvm::BalancedPartitioningConfig;
using ::llvm::BalancedPartitioning;
using ::llvm::encodeBase64;
using ::llvm::decodeBase64;
using ::llvm::stream_error_code;
using ::llvm::BinaryStreamError;
using ::llvm::BinaryStreamFlags;
using ::llvm::BinaryStream;
using ::llvm::WritableBinaryStream;
using ::llvm::FileOutputBuffer;
using ::llvm::simplify_type;
using ::llvm::isa_impl;
using ::llvm::isa_impl_cl;
using ::llvm::isa_impl_wrap;
using ::llvm::cast_retty;
using ::llvm::cast_retty_impl;
using ::llvm::cast_retty_wrap;
using ::llvm::cast_convert_val;
using ::llvm::is_simple_type;
using ::llvm::CastIsPossible;
using ::llvm::NullableValueCastFailed;
using ::llvm::DefaultDoCastIfPossible;
using ::llvm::ValueFromPointerCast;
using ::llvm::UniquePtrCast;
using ::llvm::OptionalValueCast;
using ::llvm::ConstStrippingForwardingCast;
using ::llvm::ForwardToPointerCast;
using ::llvm::CastInfo;
using ::llvm::isa;
using ::llvm::cast;
using ::llvm::IsNullable;
using ::llvm::ValueIsPresent;
using ::llvm::dyn_cast;
using ::llvm::isa_and_present;
using ::llvm::isa_and_nonnull;
using ::llvm::cast_if_present;
using ::llvm::cast_or_null;
using ::llvm::dyn_cast_if_present;
using ::llvm::dyn_cast_or_null;
using ::llvm::unique_dyn_cast;
using ::llvm::unique_dyn_cast_or_null;
using ::llvm::MemoryBuffer;
using ::llvm::MemoryBufferRef;
using ::llvm::WritableMemoryBuffer;
using ::llvm::WriteThroughMemoryBuffer;
using ::llvm::BinaryByteStream;
using ::llvm::MemoryBufferByteStream;
using ::llvm::MutableBinaryByteStream;
using ::llvm::AppendingBinaryByteStream;
using ::llvm::FileBufferByteStream;
using ::llvm::BinaryItemTraits;
using ::llvm::BinaryItemStream;
using ::llvm::BinaryStreamRefBase;
using ::llvm::BinaryStreamRef;
using ::llvm::BinarySubstreamRef;
using ::llvm::WritableBinaryStreamRef;
using ::llvm::VarStreamArrayExtractor;
using ::llvm::VarStreamArrayIterator;
using ::llvm::VarStreamArray;
using ::llvm::FixedStreamArrayIterator;
using ::llvm::FixedStreamArray;
using ::llvm::ConversionResult;
using ::llvm::ConversionFlags;
using ::llvm::ConvertUTF8toUTF16;
using ::llvm::ConvertUTF8toUTF32Partial;
using ::llvm::ConvertUTF8toUTF32;
using ::llvm::ConvertUTF16toUTF8;
using ::llvm::ConvertUTF32toUTF8;
using ::llvm::ConvertUTF16toUTF32;
using ::llvm::ConvertUTF32toUTF16;
using ::llvm::isLegalUTF8Sequence;
using ::llvm::isLegalUTF8String;
using ::llvm::getUTF8SequenceSize;
using ::llvm::getNumBytesForUTF8;
using ::llvm::ArrayRef;
using ::llvm::SmallVectorImpl;
using ::llvm::ConvertUTF8toWide;
using ::llvm::convertWideToUTF8;
using ::llvm::ConvertCodePointToUTF8;
using ::llvm::convertUTF8Sequence;
using ::llvm::hasUTF16ByteOrderMark;
using ::llvm::convertUTF16ToUTF8String;
using ::llvm::convertUTF32ToUTF8String;
using ::llvm::convertUTF8ToUTF16String;
using ::llvm::BinaryStreamReader;
using ::llvm::BinaryStreamWriter;
using ::llvm::BranchProbability;
using ::llvm::BlockFrequency;
using ::llvm::BuryPointer;
namespace cfg {
using ::llvm::cfg::UpdateKind;
using ::llvm::cfg::Update;
using ::llvm::cfg::LegalizeUpdates;
} // namespace cfg
using ::llvm::GraphDiff;
using ::llvm::crc32;
using ::llvm::JamCRC;
namespace CSKYAttrs {
using ::llvm::CSKYAttrs::getCSKYAttributeTags;
using ::llvm::CSKYAttrs::AttrType;
using ::llvm::CSKYAttrs::ISA_FLAGS;
using ::llvm::CSKYAttrs::ISA_EXT_FLAGS;
using ::llvm::CSKYAttrs::DSP_VERSION;
using ::llvm::CSKYAttrs::VDSP_VERSION;
using ::llvm::CSKYAttrs::FPU_VERSION;
using ::llvm::CSKYAttrs::FPU_ABI;
using ::llvm::CSKYAttrs::FPU_HARDFP;
} // namespace CSKYAttrs
using ::llvm::CSKYAttributeParser;
using ::llvm::CachePruningPolicy;
using ::llvm::parseCachePruningPolicy;
using ::llvm::pruneCache;
using ::llvm::CachedFileStream;
using ::llvm::AddStreamFn;
using ::llvm::FileCache;
using ::llvm::AddBufferFn;
using ::llvm::localCache;
using ::llvm::checkedAdd;
using ::llvm::checkedSub;
using ::llvm::checkedMul;
using ::llvm::checkedMulAdd;
using ::llvm::checkedAddUnsigned;
using ::llvm::checkedMulUnsigned;
using ::llvm::checkedMulAddUnsigned;
using ::llvm::format_provider;
using ::llvm::FloatStyle;
using ::llvm::IntegerStyle;
using ::llvm::HexPrintStyle;
using ::llvm::getDefaultPrecision;
using ::llvm::isPrefixedHexStyle;
using ::llvm::write_integer;
using ::llvm::write_hex;
using ::llvm::write_double;
namespace Reloc {
using ::llvm::Reloc::Model;
} // namespace Reloc
namespace CodeModel {
using ::llvm::CodeModel::Model;
} // namespace CodeModel
namespace PICLevel {
using ::llvm::PICLevel::Level;
} // namespace PICLevel
namespace PIELevel {
using ::llvm::PIELevel::Level;
} // namespace PIELevel
namespace TLSModel {
using ::llvm::TLSModel::Model;
} // namespace TLSModel
namespace CodeGenOpt {
using ::llvm::CodeGenOpt::IDType;
using ::llvm::CodeGenOpt::Level;
using ::llvm::CodeGenOpt::getLevel;
using ::llvm::CodeGenOpt::parseLevel;
} // namespace CodeGenOpt
using ::llvm::CodeGenFileType;
using ::llvm::FramePointerKind;
namespace ZeroCallUsedRegs {
using ::llvm::ZeroCallUsedRegs::ZeroCallUsedRegsKind;
} // namespace ZeroCallUsedRegs
using ::llvm::UWTableKind;
using ::llvm::FunctionReturnThunksKind;
using ::llvm::CodeGenCoverage;
using ::llvm::object_creator;
using ::llvm::object_deleter;
using ::llvm::ManagedStaticBase;
using ::llvm::ManagedStatic;
using ::llvm::llvm_shutdown;
using ::llvm::llvm_shutdown_obj;
using ::llvm::StringSaver;
using ::llvm::UniqueStringSaver;
namespace vfs {
using ::llvm::vfs::FileSystem;
using ::llvm::vfs::Status;
using ::llvm::vfs::File;
using ::llvm::vfs::directory_entry;
namespace detail {
using ::llvm::vfs::detail::DirIterImpl;
using ::llvm::vfs::detail::RecDirIterState;
using ::llvm::vfs::detail::InMemoryDirectory;
using ::llvm::vfs::detail::InMemoryNode;
using ::llvm::vfs::detail::NewInMemoryNodeInfo;
using ::llvm::vfs::detail::NamedNodeOrError;
} // namespace detail
using ::llvm::vfs::directory_iterator;
using ::llvm::vfs::recursive_directory_iterator;
using ::llvm::vfs::getRealFileSystem;
using ::llvm::vfs::createPhysicalFileSystem;
using ::llvm::vfs::OverlayFileSystem;
using ::llvm::vfs::ProxyFileSystem;
using ::llvm::vfs::InMemoryFileSystem;
using ::llvm::vfs::getNextVirtualUniqueID;
using ::llvm::vfs::getVFSFromYAML;
using ::llvm::vfs::YAMLVFSEntry;
using ::llvm::vfs::RedirectingFSDirIterImpl;
using ::llvm::vfs::RedirectingFileSystemParser;
using ::llvm::vfs::RedirectingFileSystem;
using ::llvm::vfs::collectVFSFromYAML;
using ::llvm::vfs::YAMLVFSWriter;
} // namespace vfs
namespace cl {
using ::llvm::cl::ParseCommandLineOptions;
using ::llvm::cl::VersionPrinterTy;
using ::llvm::cl::SetVersionPrinter;
using ::llvm::cl::AddExtraVersionPrinter;
using ::llvm::cl::PrintOptionValues;
using ::llvm::cl::Option;
using ::llvm::cl::AddLiteralOption;
using ::llvm::cl::NumOccurrencesFlag;
using ::llvm::cl::ValueExpected;
using ::llvm::cl::OptionHidden;
using ::llvm::cl::FormattingFlags;
using ::llvm::cl::MiscFlags;
using ::llvm::cl::OptionCategory;
using ::llvm::cl::getGeneralCategory;
using ::llvm::cl::SubCommand;
using ::llvm::cl::TopLevelSubCommand;
using ::llvm::cl::AllSubCommands;
using ::llvm::cl::desc;
using ::llvm::cl::value_desc;
using ::llvm::cl::initializer;
using ::llvm::cl::list_initializer;
using ::llvm::cl::init;
using ::llvm::cl::list_init;
using ::llvm::cl::LocationClass;
using ::llvm::cl::location;
using ::llvm::cl::cat;
using ::llvm::cl::sub;
using ::llvm::cl::cb;
namespace detail {
using ::llvm::cl::detail::callback_traits;
} // namespace detail
using ::llvm::cl::callback;
using ::llvm::cl::GenericOptionValue;
using ::llvm::cl::OptionValue;
using ::llvm::cl::OptionValueBase;
using ::llvm::cl::OptionValueCopy;
using ::llvm::cl::boolOrDefault;
using ::llvm::cl::OptionEnumValue;
using ::llvm::cl::ValuesClass;
using ::llvm::cl::values;
using ::llvm::cl::generic_parser_base;
using ::llvm::cl::parser;
using ::llvm::cl::basic_parser_impl;
using ::llvm::cl::basic_parser;
using ::llvm::cl::printOptionDiff;
using ::llvm::cl::OptionDiffPrinter;
using ::llvm::cl::applicator;
using ::llvm::cl::apply;
using ::llvm::cl::opt_storage;
using ::llvm::cl::opt;
using ::llvm::cl::list_storage;
using ::llvm::cl::list;
using ::llvm::cl::multi_val;
using ::llvm::cl::bits_storage;
using ::llvm::cl::bits;
using ::llvm::cl::alias;
using ::llvm::cl::aliasopt;
using ::llvm::cl::extrahelp;
using ::llvm::cl::PrintVersionMessage;
using ::llvm::cl::PrintHelpMessage;
using ::llvm::cl::getRegisteredOptions;
using ::llvm::cl::getRegisteredSubcommands;
using ::llvm::cl::TokenizeGNUCommandLine;
using ::llvm::cl::TokenizeWindowsCommandLine;
using ::llvm::cl::TokenizeWindowsCommandLineNoCopy;
using ::llvm::cl::TokenizeWindowsCommandLineFull;
using ::llvm::cl::TokenizerCallback;
using ::llvm::cl::tokenizeConfigFile;
using ::llvm::cl::ExpansionContext;
using ::llvm::cl::expandResponseFiles;
using ::llvm::cl::ExpandResponseFiles;
using ::llvm::cl::HideUnrelatedOptions;
using ::llvm::cl::ResetAllOptionOccurrences;
using ::llvm::cl::ResetCommandLineParser;
using ::llvm::cl::ProvidePositionalOption;
} // namespace cl
using ::llvm::DebugCompressionType;
namespace compression {
namespace zlib {
using ::llvm::compression::zlib::isAvailable;
using ::llvm::compression::zlib::compress;
using ::llvm::compression::zlib::decompress;
} // namespace zlib
namespace zstd {
using ::llvm::compression::zstd::isAvailable;
using ::llvm::compression::zstd::compress;
using ::llvm::compression::zstd::decompress;
} // namespace zstd
using ::llvm::compression::Format;
using ::llvm::compression::formatFor;
using ::llvm::compression::Params;
using ::llvm::compression::getReasonIfUnsupported;
using ::llvm::compression::compress;
using ::llvm::compression::decompress;
} // namespace compression
namespace ConverterEBCDIC {
using ::llvm::ConverterEBCDIC::convertToEBCDIC;
using ::llvm::ConverterEBCDIC::convertToUTF8;
} // namespace ConverterEBCDIC
using ::llvm::CrashRecoveryContextCleanup;
using ::llvm::CrashRecoveryContext;
using ::llvm::CrashRecoveryContextCleanupBase;
using ::llvm::CrashRecoveryContextDestructorCleanup;
using ::llvm::CrashRecoveryContextDeleteCleanup;
using ::llvm::CrashRecoveryContextReleaseRefCleanup;
using ::llvm::CrashRecoveryContextCleanupRegistrar;
using ::llvm::djbHash;
using ::llvm::caseFoldingDjbHash;
using ::llvm::DefaultDOTGraphTraits;
using ::llvm::DOTGraphTraits;
namespace dxil {
using ::llvm::dxil::ParameterKind;
using ::llvm::dxil::parameterTypeNameToKind;
} // namespace dxil
using ::llvm::DebugCounter;
namespace sampleprof {
using ::llvm::sampleprof::FSDiscriminatorPass;
} // namespace sampleprof
using ::llvm::SignedDivisionByConstantInfo;
using ::llvm::UnsignedDivisionByConstantInfo;
using ::llvm::errc;
using ::llvm::make_error_code;
using ::llvm::RTTIRoot;
using ::llvm::RTTIExtends;
using ::llvm::DenseMapInfo;
using ::llvm::SmallString;
using ::llvm::MD5;
using ::llvm::MD5Hash;
using ::llvm::SMLoc;
using ::llvm::SMRange;
using ::llvm::SMDiagnostic;
using ::llvm::SMFixIt;
using ::llvm::SourceMgr;
using ::llvm::FileCollectorFileSystem;
using ::llvm::FileCollectorBase;
using ::llvm::FileCollector;
using ::llvm::DiffFilesWithTolerance;
using ::llvm::FileRemover;
using ::llvm::FilePermissionsApplier;
using ::llvm::AlignStyle;
using ::llvm::FmtAlign;
using ::llvm::FormatAdapter;
using ::llvm::fmt_align;
using ::llvm::fmt_pad;
using ::llvm::fmt_repeat;
using ::llvm::fmt_consume;
using ::llvm::ReplacementType;
using ::llvm::ReplacementItem;
using ::llvm::formatv_object;
using ::llvm::formatv;
using ::llvm::formatted_raw_ostream;
using ::llvm::fouts;
using ::llvm::ferrs;
using ::llvm::fdbgs;
using ::llvm::DominatorTreeBase;
namespace DomTreeBuilder {
using ::llvm::DomTreeBuilder::SemiNCAInfo;
using ::llvm::DomTreeBuilder::Calculate;
using ::llvm::DomTreeBuilder::CalculateWithUpdates;
using ::llvm::DomTreeBuilder::InsertEdge;
using ::llvm::DomTreeBuilder::DeleteEdge;
using ::llvm::DomTreeBuilder::ApplyUpdates;
using ::llvm::DomTreeBuilder::Verify;
} // namespace DomTreeBuilder
using ::llvm::DomTreeNodeBase;
using ::llvm::PrintDomTree;
using ::llvm::DomTreeNodeTraits;
using ::llvm::DomTreeBase;
using ::llvm::PostDomTreeBase;
namespace IDFCalculatorDetail {
using ::llvm::IDFCalculatorDetail::ChildrenGetterTy;
} // namespace IDFCalculatorDetail
using ::llvm::IDFCalculatorBase;
using ::llvm::LoopInfoBase;
using ::llvm::LoopBase;
using ::llvm::getExitBlockHelper;
using ::llvm::getUniqueExitBlocksHelper;
using ::llvm::PopulateLoopsDFS;
using ::llvm::compareVectors;
using ::llvm::addInnerLoopsToHeadersMap;
using ::llvm::GlobPattern;
namespace DOT {
using ::llvm::DOT::EscapeString;
using ::llvm::DOT::getColorString;
} // namespace DOT
namespace GraphProgram {
using ::llvm::GraphProgram::Name;
} // namespace GraphProgram
using ::llvm::DisplayGraph;
using ::llvm::GraphWriter;
using ::llvm::WriteGraph;
using ::llvm::createGraphFilename;
using ::llvm::dumpDotGraphToFile;
using ::llvm::ViewGraph;
namespace hashbuilder_detail {
using ::llvm::hashbuilder_detail::IsHashableData;
using ::llvm::hashbuilder_detail::HashCodeHasher;
using ::llvm::hashbuilder_detail::HashCodeHashBuilder;
} // namespace hashbuilder_detail
using ::llvm::HashBuilderBase;
using ::llvm::HashBuilderImpl;
using ::llvm::HashBuilder;
using ::llvm::hash_value;
using ::llvm::EnablePrettyStackTrace;
using ::llvm::EnablePrettyStackTraceOnSigInfoForThisThread;
using ::llvm::setBugReportMsg;
using ::llvm::getBugReportMsg;
using ::llvm::PrettyStackTraceEntry;
using ::llvm::PrettyStackTraceString;
using ::llvm::PrettyStackTraceFormat;
using ::llvm::PrettyStackTraceProgram;
using ::llvm::SavePrettyStackState;
using ::llvm::RestorePrettyStackState;
using ::llvm::InitLLVM;
using ::llvm::InstructionCost;
namespace json {
using ::llvm::json::is_uint_64_bit_v;
using ::llvm::json::isUTF8;
using ::llvm::json::fixUTF8;
using ::llvm::json::Array;
using ::llvm::json::ObjectKey;
using ::llvm::json::Value;
using ::llvm::json::toJSON;
using ::llvm::json::Object;
using ::llvm::json::Path;
using ::llvm::json::fromJSON;
using ::llvm::json::ObjectMapper;
using ::llvm::json::parse;
using ::llvm::json::ParseError;
using ::llvm::json::OStream;
} // namespace json
using ::llvm::KnownBits;
using ::llvm::encodeSLEB128;
using ::llvm::encodeULEB128;
using ::llvm::decodeULEB128;
using ::llvm::decodeSLEB128;
using ::llvm::getULEB128Size;
using ::llvm::getSLEB128Size;
using ::llvm::ToolContext;
using ::llvm::line_iterator;
using ::llvm::LockFileManager;
namespace MSP430Attrs {
using ::llvm::MSP430Attrs::getMSP430AttributeTags;
using ::llvm::MSP430Attrs::AttrType;
using ::llvm::MSP430Attrs::ISA;
using ::llvm::MSP430Attrs::CodeModel;
using ::llvm::MSP430Attrs::DataModel;
using ::llvm::MSP430Attrs::EnumSize;
} // namespace MSP430Attrs
using ::llvm::MSP430AttributeParser;
using ::llvm::MSVCPError;
using ::llvm::MSVCPExpected;
namespace Mips {
using ::llvm::Mips::AFL_REG;
using ::llvm::Mips::AFL_ASE;
using ::llvm::Mips::AFL_EXT;
using ::llvm::Mips::AFL_FLAGS1;
using ::llvm::Mips::Val_GNU_MIPS_ABI_FP;
using ::llvm::Mips::Val_GNU_MIPS_ABI_MSA;
} // namespace Mips
using ::llvm::ModRefInfo;
using ::llvm::isNoModRef;
using ::llvm::isModOrRefSet;
using ::llvm::isModAndRefSet;
using ::llvm::isModSet;
using ::llvm::isRefSet;
using ::llvm::IRMemLocation;
using ::llvm::MemoryEffectsBase;
using ::llvm::MemoryEffects;
using ::llvm::FunctionModRefBehavior;
using ::llvm::llvm_is_multithreaded;
using ::llvm::call_once;
using ::llvm::ThreadPoolStrategy;
using ::llvm::get_threadpool_strategy;
using ::llvm::heavyweight_hardware_concurrency;
using ::llvm::hardware_concurrency;
using ::llvm::optimal_concurrency;
using ::llvm::get_threadid;
using ::llvm::get_max_thread_name_length;
using ::llvm::set_thread_name;
using ::llvm::get_thread_name;
using ::llvm::get_thread_affinity_mask;
using ::llvm::get_cpus;
using ::llvm::get_physical_cores;
using ::llvm::ThreadPriority;
using ::llvm::SetThreadPriorityResult;
using ::llvm::set_thread_priority;
using ::llvm::OnDiskChainedHashTableGenerator;
using ::llvm::OnDiskChainedHashTable;
using ::llvm::OnDiskIterableChainedHashTable;
using ::llvm::OptimizedStructLayoutField;
using ::llvm::performOptimizedStructLayout;
using ::llvm::PGOOptions;
namespace parallel {
using ::llvm::parallel::strategy;
using ::llvm::parallel::threadIndex;
using ::llvm::parallel::getThreadIndex;
using ::llvm::parallel::getThreadCount;
namespace detail {
using ::llvm::parallel::detail::Latch;
using ::llvm::parallel::detail::medianOf3;
using ::llvm::parallel::detail::parallel_quick_sort;
using ::llvm::parallel::detail::parallel_sort;
using ::llvm::parallel::detail::parallel_transform_reduce;
} // namespace detail
using ::llvm::parallel::TaskGroup;
using ::llvm::parallel::PerThreadAllocator;
using ::llvm::parallel::PerThreadBumpPtrAllocator;
} // namespace parallel
using ::llvm::parallelSort;
using ::llvm::parallelFor;
using ::llvm::parallelForEach;
using ::llvm::parallelTransformReduce;
using ::llvm::parallelForEachError;
using ::llvm::PluginLoader;
using ::llvm::Printable;
using ::llvm::BitVector;
namespace RISCVAttrs {
using ::llvm::RISCVAttrs::getRISCVAttributeTags;
using ::llvm::RISCVAttrs::AttrType;
using ::llvm::RISCVAttrs::StackAlign;
} // namespace RISCVAttrs
using ::llvm::RISCVAttributeParser;
using ::llvm::RISCVExtensionInfo;
using ::llvm::RISCVISAInfo;
using ::llvm::RandomNumberGenerator;
using ::llvm::getRandomBytes;
using ::llvm::PrintRecyclerStats;
using ::llvm::Recycler;
using ::llvm::RecyclingAllocator;
using ::llvm::Regex;
using ::llvm::SimpleRegistryEntry;
using ::llvm::Registry;
using ::llvm::SHA1;
using ::llvm::SHA256;
using ::llvm::SMTSort;
using ::llvm::SMTSortRef;
using ::llvm::SMTExpr;
using ::llvm::SMTExprRef;
using ::llvm::SMTSolver;
using ::llvm::SMTSolverRef;
using ::llvm::CreateZ3Solver;
using ::llvm::SaveAndRestore;
namespace ScaledNumbers {
using ::llvm::ScaledNumbers::getWidth;
using ::llvm::ScaledNumbers::getRounded;
using ::llvm::ScaledNumbers::getRounded32;
using ::llvm::ScaledNumbers::getRounded64;
using ::llvm::ScaledNumbers::getAdjusted;
using ::llvm::ScaledNumbers::getAdjusted32;
using ::llvm::ScaledNumbers::getAdjusted64;
using ::llvm::ScaledNumbers::multiply64;
using ::llvm::ScaledNumbers::getProduct;
using ::llvm::ScaledNumbers::getProduct32;
using ::llvm::ScaledNumbers::getProduct64;
using ::llvm::ScaledNumbers::divide64;
using ::llvm::ScaledNumbers::divide32;
using ::llvm::ScaledNumbers::getQuotient;
using ::llvm::ScaledNumbers::getQuotient32;
using ::llvm::ScaledNumbers::getQuotient64;
using ::llvm::ScaledNumbers::getLgImpl;
using ::llvm::ScaledNumbers::getLg;
using ::llvm::ScaledNumbers::getLgFloor;
using ::llvm::ScaledNumbers::getLgCeiling;
using ::llvm::ScaledNumbers::compareImpl;
using ::llvm::ScaledNumbers::compare;
using ::llvm::ScaledNumbers::matchScales;
using ::llvm::ScaledNumbers::getSum;
using ::llvm::ScaledNumbers::getSum32;
using ::llvm::ScaledNumbers::getSum64;
using ::llvm::ScaledNumbers::getDifference;
using ::llvm::ScaledNumbers::getDifference32;
using ::llvm::ScaledNumbers::getDifference64;
} // namespace ScaledNumbers
using ::llvm::ScaledNumberBase;
using ::llvm::ScaledNumber;
using ::llvm::SignpostEmitterImpl;
using ::llvm::SignpostEmitter;
using ::llvm::SmallVectorMemoryBuffer;
using ::llvm::SpecialCaseList;
using ::llvm::SuffixTreeNode;
using ::llvm::SuffixTreeInternalNode;
using ::llvm::SuffixTreeLeafNode;
using ::llvm::SuffixTree;
using ::llvm::CheckBitcodeOutputToConsole;
using ::llvm::TarWriter;
using ::llvm::InitializeAllTargetInfos;
using ::llvm::InitializeAllTargets;
using ::llvm::InitializeAllTargetMCs;
using ::llvm::InitializeAllAsmPrinters;
using ::llvm::InitializeAllAsmParsers;
using ::llvm::InitializeAllDisassemblers;
using ::llvm::InitializeNativeTarget;
using ::llvm::InitializeNativeTargetAsmPrinter;
using ::llvm::InitializeNativeTargetAsmParser;
using ::llvm::InitializeNativeTargetDisassembler;
using ::llvm::InitializeAllTargetMCAs;
using ::llvm::thread;
using ::llvm::llvm_execute_on_thread_impl;
using ::llvm::llvm_thread_join_impl;
using ::llvm::llvm_thread_detach_impl;
using ::llvm::llvm_thread_get_id_impl;
using ::llvm::llvm_thread_get_current_id_impl;
namespace this_thread {
using ::llvm::this_thread::get_id;
} // namespace this_thread
using ::llvm::ThreadPoolTaskGroup;
using ::llvm::TimeTraceProfiler;
using ::llvm::getTimeTraceProfilerInstance;
using ::llvm::timeTraceProfilerInitialize;
using ::llvm::timeTraceProfilerCleanup;
using ::llvm::timeTraceProfilerFinishThread;
using ::llvm::timeTraceProfilerEnabled;
using ::llvm::timeTraceProfilerWrite;
using ::llvm::timeTraceProfilerBegin;
using ::llvm::timeTraceProfilerEnd;
using ::llvm::TimeTraceScope;
using ::llvm::TimerGroup;
using ::llvm::TimeRecord;
using ::llvm::Timer;
using ::llvm::TimeRegion;
using ::llvm::NamedRegionTimer;
using ::llvm::ToolOutputFile;
namespace trailing_objects_internal {
using ::llvm::trailing_objects_internal::AlignmentCalcHelper;
using ::llvm::trailing_objects_internal::TrailingObjectsBase;
using ::llvm::trailing_objects_internal::ExtractSecondType;
using ::llvm::trailing_objects_internal::TrailingObjectsImpl;
} // namespace trailing_objects_internal
using ::llvm::TrailingObjects;
using ::llvm::getTypeName;
using ::llvm::reportInvalidSizeRequest;
using ::llvm::StackOffset;
namespace details {
using ::llvm::details::FixedOrScalableQuantity;
} // namespace details
using ::llvm::ElementCount;
using ::llvm::TypeSize;
using ::llvm::VersionTuple;
namespace Win64EH {
using ::llvm::Win64EH::UnwindOpcodes;
using ::llvm::Win64EH::UnwindCode;
using ::llvm::Win64EH::RuntimeFunction;
using ::llvm::Win64EH::UnwindInfo;
} // namespace Win64EH
using ::llvm::mapWindowsError;
using ::llvm::getColorCategory;
using ::llvm::HighlightColor;
using ::llvm::ColorMode;
using ::llvm::WithColor;
namespace X86Disassembler {
using ::llvm::X86Disassembler::attributeBits;
using ::llvm::X86Disassembler::InstructionContext;
using ::llvm::X86Disassembler::OpcodeType;
using ::llvm::X86Disassembler::ModRMDecisionType;
using ::llvm::X86Disassembler::OperandEncoding;
using ::llvm::X86Disassembler::OperandType;
using ::llvm::X86Disassembler::OperandSpecifier;
using ::llvm::X86Disassembler::DisassemblerMode;
} // namespace X86Disassembler
namespace yaml {
using ::llvm::yaml::Document;
using ::llvm::yaml::document_iterator;
using ::llvm::yaml::Node;
using ::llvm::yaml::Scanner;
using ::llvm::yaml::Token;
using ::llvm::yaml::dumpTokens;
using ::llvm::yaml::scanTokens;
using ::llvm::yaml::escape;
using ::llvm::yaml::parseBool;
using ::llvm::yaml::Stream;
using ::llvm::yaml::NullNode;
using ::llvm::yaml::ScalarNode;
using ::llvm::yaml::BlockScalarNode;
using ::llvm::yaml::KeyValueNode;
using ::llvm::yaml::basic_collection_iterator;
using ::llvm::yaml::begin;
using ::llvm::yaml::skip;
using ::llvm::yaml::MappingNode;
using ::llvm::yaml::SequenceNode;
using ::llvm::yaml::AliasNode;
using ::llvm::yaml::NodeKind;
using ::llvm::yaml::EmptyContext;
using ::llvm::yaml::MappingTraits;
using ::llvm::yaml::MappingContextTraits;
using ::llvm::yaml::ScalarEnumerationTraits;
using ::llvm::yaml::ScalarBitSetTraits;
using ::llvm::yaml::QuotingType;
using ::llvm::yaml::ScalarTraits;
using ::llvm::yaml::BlockScalarTraits;
using ::llvm::yaml::TaggedScalarTraits;
using ::llvm::yaml::SequenceTraits;
using ::llvm::yaml::SequenceElementTraits;
using ::llvm::yaml::DocumentListTraits;
using ::llvm::yaml::CustomMappingTraits;
using ::llvm::yaml::PolymorphicTraits;
using ::llvm::yaml::MissingTrait;
using ::llvm::yaml::has_ScalarEnumerationTraits;
using ::llvm::yaml::has_ScalarBitSetTraits;
using ::llvm::yaml::has_ScalarTraits;
using ::llvm::yaml::has_BlockScalarTraits;
using ::llvm::yaml::has_TaggedScalarTraits;
using ::llvm::yaml::has_MappingTraits;
using ::llvm::yaml::has_MappingValidateTraits;
using ::llvm::yaml::has_MappingEnumInputTraits;
using ::llvm::yaml::has_SequenceMethodTraits;
using ::llvm::yaml::has_CustomMappingTraits;
using ::llvm::yaml::has_FlowTraits;
using ::llvm::yaml::has_SequenceTraits;
using ::llvm::yaml::has_DocumentListTraits;
using ::llvm::yaml::has_PolymorphicTraits;
using ::llvm::yaml::isNumeric;
using ::llvm::yaml::isNull;
using ::llvm::yaml::isBool;
using ::llvm::yaml::needsQuotes;
using ::llvm::yaml::missingTraits;
using ::llvm::yaml::validatedMappingTraits;
using ::llvm::yaml::unvalidatedMappingTraits;
using ::llvm::yaml::IO;
namespace detail {
using ::llvm::yaml::detail::doMapping;
} // namespace detail
using ::llvm::yaml::yamlize;
using ::llvm::yaml::yamlizeMappingEnumInput;
using ::llvm::yaml::MappingNormalization;
using ::llvm::yaml::MappingNormalizationHeap;
using ::llvm::yaml::Input;
using ::llvm::yaml::Output;
using ::llvm::yaml::IsFlowSequenceBase;
using ::llvm::yaml::IsResizable;
using ::llvm::yaml::IsResizableBase;
using ::llvm::yaml::SequenceTraitsImpl;
using ::llvm::yaml::CheckIsBool;
using ::llvm::yaml::StdMapStringCustomMappingTraitsImpl;
} // namespace yaml
using ::llvm::circular_raw_ostream;
using ::llvm::raw_os_ostream;
using ::llvm::raw_sha1_ostream;
using ::llvm::xxHash64;
using ::llvm::xxh3_64bits;
} // namespace llvm
namespace std {
using ::std::is_error_code_enum;
} // namespace std
using ::llvm_regex;
}
