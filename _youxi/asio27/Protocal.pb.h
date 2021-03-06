// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Protocal.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Protocal_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Protocal_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3017000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3017003 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Protocal_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_Protocal_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[4]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Protocal_2eproto;
class PBindName;
struct PBindNameDefaultTypeInternal;
extern PBindNameDefaultTypeInternal _PBindName_default_instance_;
class PChat;
struct PChatDefaultTypeInternal;
extern PChatDefaultTypeInternal _PChat_default_instance_;
class PHeader;
struct PHeaderDefaultTypeInternal;
extern PHeaderDefaultTypeInternal _PHeader_default_instance_;
class PRoomInformation;
struct PRoomInformationDefaultTypeInternal;
extern PRoomInformationDefaultTypeInternal _PRoomInformation_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::PBindName* Arena::CreateMaybeMessage<::PBindName>(Arena*);
template<> ::PChat* Arena::CreateMaybeMessage<::PChat>(Arena*);
template<> ::PHeader* Arena::CreateMaybeMessage<::PHeader>(Arena*);
template<> ::PRoomInformation* Arena::CreateMaybeMessage<::PRoomInformation>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class PHeader final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:PHeader) */ {
 public:
  inline PHeader() : PHeader(nullptr) {}
  ~PHeader() override;
  explicit constexpr PHeader(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  PHeader(const PHeader& from);
  PHeader(PHeader&& from) noexcept
    : PHeader() {
    *this = ::std::move(from);
  }

  inline PHeader& operator=(const PHeader& from) {
    CopyFrom(from);
    return *this;
  }
  inline PHeader& operator=(PHeader&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const PHeader& default_instance() {
    return *internal_default_instance();
  }
  static inline const PHeader* internal_default_instance() {
    return reinterpret_cast<const PHeader*>(
               &_PHeader_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(PHeader& a, PHeader& b) {
    a.Swap(&b);
  }
  inline void Swap(PHeader* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(PHeader* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline PHeader* New() const final {
    return new PHeader();
  }

  PHeader* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<PHeader>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const PHeader& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const PHeader& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to, const ::PROTOBUF_NAMESPACE_ID::Message&from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(PHeader* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "PHeader";
  }
  protected:
  explicit PHeader(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kBodySizeFieldNumber = 1,
    kTypeFieldNumber = 2,
  };
  // int32 bodySize = 1;
  void clear_bodysize();
  ::PROTOBUF_NAMESPACE_ID::int32 bodysize() const;
  void set_bodysize(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_bodysize() const;
  void _internal_set_bodysize(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // int32 type = 2;
  void clear_type();
  ::PROTOBUF_NAMESPACE_ID::int32 type() const;
  void set_type(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_type() const;
  void _internal_set_type(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // @@protoc_insertion_point(class_scope:PHeader)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::int32 bodysize_;
  ::PROTOBUF_NAMESPACE_ID::int32 type_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Protocal_2eproto;
};
// -------------------------------------------------------------------

class PBindName final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:PBindName) */ {
 public:
  inline PBindName() : PBindName(nullptr) {}
  ~PBindName() override;
  explicit constexpr PBindName(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  PBindName(const PBindName& from);
  PBindName(PBindName&& from) noexcept
    : PBindName() {
    *this = ::std::move(from);
  }

  inline PBindName& operator=(const PBindName& from) {
    CopyFrom(from);
    return *this;
  }
  inline PBindName& operator=(PBindName&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const PBindName& default_instance() {
    return *internal_default_instance();
  }
  static inline const PBindName* internal_default_instance() {
    return reinterpret_cast<const PBindName*>(
               &_PBindName_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(PBindName& a, PBindName& b) {
    a.Swap(&b);
  }
  inline void Swap(PBindName* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(PBindName* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline PBindName* New() const final {
    return new PBindName();
  }

  PBindName* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<PBindName>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const PBindName& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const PBindName& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to, const ::PROTOBUF_NAMESPACE_ID::Message&from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(PBindName* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "PBindName";
  }
  protected:
  explicit PBindName(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kNameFieldNumber = 1,
  };
  // string name = 1;
  void clear_name();
  const std::string& name() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_name(ArgT0&& arg0, ArgT... args);
  std::string* mutable_name();
  PROTOBUF_MUST_USE_RESULT std::string* release_name();
  void set_allocated_name(std::string* name);
  private:
  const std::string& _internal_name() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_name(const std::string& value);
  std::string* _internal_mutable_name();
  public:

  // @@protoc_insertion_point(class_scope:PBindName)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr name_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Protocal_2eproto;
};
// -------------------------------------------------------------------

class PChat final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:PChat) */ {
 public:
  inline PChat() : PChat(nullptr) {}
  ~PChat() override;
  explicit constexpr PChat(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  PChat(const PChat& from);
  PChat(PChat&& from) noexcept
    : PChat() {
    *this = ::std::move(from);
  }

  inline PChat& operator=(const PChat& from) {
    CopyFrom(from);
    return *this;
  }
  inline PChat& operator=(PChat&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const PChat& default_instance() {
    return *internal_default_instance();
  }
  static inline const PChat* internal_default_instance() {
    return reinterpret_cast<const PChat*>(
               &_PChat_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(PChat& a, PChat& b) {
    a.Swap(&b);
  }
  inline void Swap(PChat* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(PChat* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline PChat* New() const final {
    return new PChat();
  }

  PChat* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<PChat>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const PChat& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const PChat& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to, const ::PROTOBUF_NAMESPACE_ID::Message&from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(PChat* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "PChat";
  }
  protected:
  explicit PChat(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kInformationFieldNumber = 1,
  };
  // string information = 1;
  void clear_information();
  const std::string& information() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_information(ArgT0&& arg0, ArgT... args);
  std::string* mutable_information();
  PROTOBUF_MUST_USE_RESULT std::string* release_information();
  void set_allocated_information(std::string* information);
  private:
  const std::string& _internal_information() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_information(const std::string& value);
  std::string* _internal_mutable_information();
  public:

  // @@protoc_insertion_point(class_scope:PChat)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr information_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Protocal_2eproto;
};
// -------------------------------------------------------------------

class PRoomInformation final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:PRoomInformation) */ {
 public:
  inline PRoomInformation() : PRoomInformation(nullptr) {}
  ~PRoomInformation() override;
  explicit constexpr PRoomInformation(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  PRoomInformation(const PRoomInformation& from);
  PRoomInformation(PRoomInformation&& from) noexcept
    : PRoomInformation() {
    *this = ::std::move(from);
  }

  inline PRoomInformation& operator=(const PRoomInformation& from) {
    CopyFrom(from);
    return *this;
  }
  inline PRoomInformation& operator=(PRoomInformation&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const PRoomInformation& default_instance() {
    return *internal_default_instance();
  }
  static inline const PRoomInformation* internal_default_instance() {
    return reinterpret_cast<const PRoomInformation*>(
               &_PRoomInformation_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  friend void swap(PRoomInformation& a, PRoomInformation& b) {
    a.Swap(&b);
  }
  inline void Swap(PRoomInformation* other) {
    if (other == this) return;
    if (GetOwningArena() == other->GetOwningArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(PRoomInformation* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline PRoomInformation* New() const final {
    return new PRoomInformation();
  }

  PRoomInformation* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<PRoomInformation>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const PRoomInformation& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const PRoomInformation& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message*to, const ::PROTOBUF_NAMESPACE_ID::Message&from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(PRoomInformation* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "PRoomInformation";
  }
  protected:
  explicit PRoomInformation(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kNameFieldNumber = 1,
    kInformationFieldNumber = 2,
  };
  // string name = 1;
  void clear_name();
  const std::string& name() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_name(ArgT0&& arg0, ArgT... args);
  std::string* mutable_name();
  PROTOBUF_MUST_USE_RESULT std::string* release_name();
  void set_allocated_name(std::string* name);
  private:
  const std::string& _internal_name() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_name(const std::string& value);
  std::string* _internal_mutable_name();
  public:

  // string information = 2;
  void clear_information();
  const std::string& information() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_information(ArgT0&& arg0, ArgT... args);
  std::string* mutable_information();
  PROTOBUF_MUST_USE_RESULT std::string* release_information();
  void set_allocated_information(std::string* information);
  private:
  const std::string& _internal_information() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_information(const std::string& value);
  std::string* _internal_mutable_information();
  public:

  // @@protoc_insertion_point(class_scope:PRoomInformation)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr name_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr information_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Protocal_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// PHeader

// int32 bodySize = 1;
inline void PHeader::clear_bodysize() {
  bodysize_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 PHeader::_internal_bodysize() const {
  return bodysize_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 PHeader::bodysize() const {
  // @@protoc_insertion_point(field_get:PHeader.bodySize)
  return _internal_bodysize();
}
inline void PHeader::_internal_set_bodysize(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  bodysize_ = value;
}
inline void PHeader::set_bodysize(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_bodysize(value);
  // @@protoc_insertion_point(field_set:PHeader.bodySize)
}

// int32 type = 2;
inline void PHeader::clear_type() {
  type_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 PHeader::_internal_type() const {
  return type_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 PHeader::type() const {
  // @@protoc_insertion_point(field_get:PHeader.type)
  return _internal_type();
}
inline void PHeader::_internal_set_type(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  type_ = value;
}
inline void PHeader::set_type(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_type(value);
  // @@protoc_insertion_point(field_set:PHeader.type)
}

// -------------------------------------------------------------------

// PBindName

// string name = 1;
inline void PBindName::clear_name() {
  name_.ClearToEmpty();
}
inline const std::string& PBindName::name() const {
  // @@protoc_insertion_point(field_get:PBindName.name)
  return _internal_name();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void PBindName::set_name(ArgT0&& arg0, ArgT... args) {
 
 name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:PBindName.name)
}
inline std::string* PBindName::mutable_name() {
  std::string* _s = _internal_mutable_name();
  // @@protoc_insertion_point(field_mutable:PBindName.name)
  return _s;
}
inline const std::string& PBindName::_internal_name() const {
  return name_.Get();
}
inline void PBindName::_internal_set_name(const std::string& value) {
  
  name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* PBindName::_internal_mutable_name() {
  
  return name_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* PBindName::release_name() {
  // @@protoc_insertion_point(field_release:PBindName.name)
  return name_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void PBindName::set_allocated_name(std::string* name) {
  if (name != nullptr) {
    
  } else {
    
  }
  name_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), name,
      GetArenaForAllocation());
  // @@protoc_insertion_point(field_set_allocated:PBindName.name)
}

// -------------------------------------------------------------------

// PChat

// string information = 1;
inline void PChat::clear_information() {
  information_.ClearToEmpty();
}
inline const std::string& PChat::information() const {
  // @@protoc_insertion_point(field_get:PChat.information)
  return _internal_information();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void PChat::set_information(ArgT0&& arg0, ArgT... args) {
 
 information_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:PChat.information)
}
inline std::string* PChat::mutable_information() {
  std::string* _s = _internal_mutable_information();
  // @@protoc_insertion_point(field_mutable:PChat.information)
  return _s;
}
inline const std::string& PChat::_internal_information() const {
  return information_.Get();
}
inline void PChat::_internal_set_information(const std::string& value) {
  
  information_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* PChat::_internal_mutable_information() {
  
  return information_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* PChat::release_information() {
  // @@protoc_insertion_point(field_release:PChat.information)
  return information_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void PChat::set_allocated_information(std::string* information) {
  if (information != nullptr) {
    
  } else {
    
  }
  information_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), information,
      GetArenaForAllocation());
  // @@protoc_insertion_point(field_set_allocated:PChat.information)
}

// -------------------------------------------------------------------

// PRoomInformation

// string name = 1;
inline void PRoomInformation::clear_name() {
  name_.ClearToEmpty();
}
inline const std::string& PRoomInformation::name() const {
  // @@protoc_insertion_point(field_get:PRoomInformation.name)
  return _internal_name();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void PRoomInformation::set_name(ArgT0&& arg0, ArgT... args) {
 
 name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:PRoomInformation.name)
}
inline std::string* PRoomInformation::mutable_name() {
  std::string* _s = _internal_mutable_name();
  // @@protoc_insertion_point(field_mutable:PRoomInformation.name)
  return _s;
}
inline const std::string& PRoomInformation::_internal_name() const {
  return name_.Get();
}
inline void PRoomInformation::_internal_set_name(const std::string& value) {
  
  name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* PRoomInformation::_internal_mutable_name() {
  
  return name_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* PRoomInformation::release_name() {
  // @@protoc_insertion_point(field_release:PRoomInformation.name)
  return name_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void PRoomInformation::set_allocated_name(std::string* name) {
  if (name != nullptr) {
    
  } else {
    
  }
  name_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), name,
      GetArenaForAllocation());
  // @@protoc_insertion_point(field_set_allocated:PRoomInformation.name)
}

// string information = 2;
inline void PRoomInformation::clear_information() {
  information_.ClearToEmpty();
}
inline const std::string& PRoomInformation::information() const {
  // @@protoc_insertion_point(field_get:PRoomInformation.information)
  return _internal_information();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void PRoomInformation::set_information(ArgT0&& arg0, ArgT... args) {
 
 information_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:PRoomInformation.information)
}
inline std::string* PRoomInformation::mutable_information() {
  std::string* _s = _internal_mutable_information();
  // @@protoc_insertion_point(field_mutable:PRoomInformation.information)
  return _s;
}
inline const std::string& PRoomInformation::_internal_information() const {
  return information_.Get();
}
inline void PRoomInformation::_internal_set_information(const std::string& value) {
  
  information_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* PRoomInformation::_internal_mutable_information() {
  
  return information_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* PRoomInformation::release_information() {
  // @@protoc_insertion_point(field_release:PRoomInformation.information)
  return information_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void PRoomInformation::set_allocated_information(std::string* information) {
  if (information != nullptr) {
    
  } else {
    
  }
  information_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), information,
      GetArenaForAllocation());
  // @@protoc_insertion_point(field_set_allocated:PRoomInformation.information)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Protocal_2eproto
