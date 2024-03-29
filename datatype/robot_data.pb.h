// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: robot_data.proto

#ifndef PROTOBUF_robot_5fdata_2eproto__INCLUDED
#define PROTOBUF_robot_5fdata_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_robot_5fdata_2eproto();
void protobuf_AssignDesc_robot_5fdata_2eproto();
void protobuf_ShutdownFile_robot_5fdata_2eproto();

class RobotData;
class RobotDataFrameList;

// ===================================================================

class RobotData : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:RobotData) */ {
 public:
  RobotData();
  virtual ~RobotData();

  RobotData(const RobotData& from);

  inline RobotData& operator=(const RobotData& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const RobotData& default_instance();

  void Swap(RobotData* other);

  // implements Message ----------------------------------------------

  inline RobotData* New() const { return New(NULL); }

  RobotData* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RobotData& from);
  void MergeFrom(const RobotData& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(RobotData* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated float joint_positions = 1;
  int joint_positions_size() const;
  void clear_joint_positions();
  static const int kJointPositionsFieldNumber = 1;
  float joint_positions(int index) const;
  void set_joint_positions(int index, float value);
  void add_joint_positions(float value);
  const ::google::protobuf::RepeatedField< float >&
      joint_positions() const;
  ::google::protobuf::RepeatedField< float >*
      mutable_joint_positions();

  // repeated float joint_actions = 2;
  int joint_actions_size() const;
  void clear_joint_actions();
  static const int kJointActionsFieldNumber = 2;
  float joint_actions(int index) const;
  void set_joint_actions(int index, float value);
  void add_joint_actions(float value);
  const ::google::protobuf::RepeatedField< float >&
      joint_actions() const;
  ::google::protobuf::RepeatedField< float >*
      mutable_joint_actions();

  // repeated float EE_positions = 3;
  int ee_positions_size() const;
  void clear_ee_positions();
  static const int kEEPositionsFieldNumber = 3;
  float ee_positions(int index) const;
  void set_ee_positions(int index, float value);
  void add_ee_positions(float value);
  const ::google::protobuf::RepeatedField< float >&
      ee_positions() const;
  ::google::protobuf::RepeatedField< float >*
      mutable_ee_positions();

  // repeated float target_EE_positions = 4;
  int target_ee_positions_size() const;
  void clear_target_ee_positions();
  static const int kTargetEEPositionsFieldNumber = 4;
  float target_ee_positions(int index) const;
  void set_target_ee_positions(int index, float value);
  void add_target_ee_positions(float value);
  const ::google::protobuf::RepeatedField< float >&
      target_ee_positions() const;
  ::google::protobuf::RepeatedField< float >*
      mutable_target_ee_positions();

  // optional float reward = 5;
  void clear_reward();
  static const int kRewardFieldNumber = 5;
  float reward() const;
  void set_reward(float value);

  // optional bool collision_flag = 6;
  void clear_collision_flag();
  static const int kCollisionFlagFieldNumber = 6;
  bool collision_flag() const;
  void set_collision_flag(bool value);

  // optional bool done_flag = 7;
  void clear_done_flag();
  static const int kDoneFlagFieldNumber = 7;
  bool done_flag() const;
  void set_done_flag(bool value);

  // @@protoc_insertion_point(class_scope:RobotData)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::RepeatedField< float > joint_positions_;
  mutable int _joint_positions_cached_byte_size_;
  ::google::protobuf::RepeatedField< float > joint_actions_;
  mutable int _joint_actions_cached_byte_size_;
  ::google::protobuf::RepeatedField< float > ee_positions_;
  mutable int _ee_positions_cached_byte_size_;
  ::google::protobuf::RepeatedField< float > target_ee_positions_;
  mutable int _target_ee_positions_cached_byte_size_;
  float reward_;
  bool collision_flag_;
  bool done_flag_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_robot_5fdata_2eproto();
  friend void protobuf_AssignDesc_robot_5fdata_2eproto();
  friend void protobuf_ShutdownFile_robot_5fdata_2eproto();

  void InitAsDefaultInstance();
  static RobotData* default_instance_;
};
// -------------------------------------------------------------------

class RobotDataFrameList : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:RobotDataFrameList) */ {
 public:
  RobotDataFrameList();
  virtual ~RobotDataFrameList();

  RobotDataFrameList(const RobotDataFrameList& from);

  inline RobotDataFrameList& operator=(const RobotDataFrameList& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const RobotDataFrameList& default_instance();

  void Swap(RobotDataFrameList* other);

  // implements Message ----------------------------------------------

  inline RobotDataFrameList* New() const { return New(NULL); }

  RobotDataFrameList* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RobotDataFrameList& from);
  void MergeFrom(const RobotDataFrameList& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(RobotDataFrameList* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .RobotData robot_data_frames = 1;
  int robot_data_frames_size() const;
  void clear_robot_data_frames();
  static const int kRobotDataFramesFieldNumber = 1;
  const ::RobotData& robot_data_frames(int index) const;
  ::RobotData* mutable_robot_data_frames(int index);
  ::RobotData* add_robot_data_frames();
  ::google::protobuf::RepeatedPtrField< ::RobotData >*
      mutable_robot_data_frames();
  const ::google::protobuf::RepeatedPtrField< ::RobotData >&
      robot_data_frames() const;

  // @@protoc_insertion_point(class_scope:RobotDataFrameList)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  bool _is_default_instance_;
  ::google::protobuf::RepeatedPtrField< ::RobotData > robot_data_frames_;
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_robot_5fdata_2eproto();
  friend void protobuf_AssignDesc_robot_5fdata_2eproto();
  friend void protobuf_ShutdownFile_robot_5fdata_2eproto();

  void InitAsDefaultInstance();
  static RobotDataFrameList* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// RobotData

// repeated float joint_positions = 1;
inline int RobotData::joint_positions_size() const {
  return joint_positions_.size();
}
inline void RobotData::clear_joint_positions() {
  joint_positions_.Clear();
}
inline float RobotData::joint_positions(int index) const {
  // @@protoc_insertion_point(field_get:RobotData.joint_positions)
  return joint_positions_.Get(index);
}
inline void RobotData::set_joint_positions(int index, float value) {
  joint_positions_.Set(index, value);
  // @@protoc_insertion_point(field_set:RobotData.joint_positions)
}
inline void RobotData::add_joint_positions(float value) {
  joint_positions_.Add(value);
  // @@protoc_insertion_point(field_add:RobotData.joint_positions)
}
inline const ::google::protobuf::RepeatedField< float >&
RobotData::joint_positions() const {
  // @@protoc_insertion_point(field_list:RobotData.joint_positions)
  return joint_positions_;
}
inline ::google::protobuf::RepeatedField< float >*
RobotData::mutable_joint_positions() {
  // @@protoc_insertion_point(field_mutable_list:RobotData.joint_positions)
  return &joint_positions_;
}

// repeated float joint_actions = 2;
inline int RobotData::joint_actions_size() const {
  return joint_actions_.size();
}
inline void RobotData::clear_joint_actions() {
  joint_actions_.Clear();
}
inline float RobotData::joint_actions(int index) const {
  // @@protoc_insertion_point(field_get:RobotData.joint_actions)
  return joint_actions_.Get(index);
}
inline void RobotData::set_joint_actions(int index, float value) {
  joint_actions_.Set(index, value);
  // @@protoc_insertion_point(field_set:RobotData.joint_actions)
}
inline void RobotData::add_joint_actions(float value) {
  joint_actions_.Add(value);
  // @@protoc_insertion_point(field_add:RobotData.joint_actions)
}
inline const ::google::protobuf::RepeatedField< float >&
RobotData::joint_actions() const {
  // @@protoc_insertion_point(field_list:RobotData.joint_actions)
  return joint_actions_;
}
inline ::google::protobuf::RepeatedField< float >*
RobotData::mutable_joint_actions() {
  // @@protoc_insertion_point(field_mutable_list:RobotData.joint_actions)
  return &joint_actions_;
}

// repeated float EE_positions = 3;
inline int RobotData::ee_positions_size() const {
  return ee_positions_.size();
}
inline void RobotData::clear_ee_positions() {
  ee_positions_.Clear();
}
inline float RobotData::ee_positions(int index) const {
  // @@protoc_insertion_point(field_get:RobotData.EE_positions)
  return ee_positions_.Get(index);
}
inline void RobotData::set_ee_positions(int index, float value) {
  ee_positions_.Set(index, value);
  // @@protoc_insertion_point(field_set:RobotData.EE_positions)
}
inline void RobotData::add_ee_positions(float value) {
  ee_positions_.Add(value);
  // @@protoc_insertion_point(field_add:RobotData.EE_positions)
}
inline const ::google::protobuf::RepeatedField< float >&
RobotData::ee_positions() const {
  // @@protoc_insertion_point(field_list:RobotData.EE_positions)
  return ee_positions_;
}
inline ::google::protobuf::RepeatedField< float >*
RobotData::mutable_ee_positions() {
  // @@protoc_insertion_point(field_mutable_list:RobotData.EE_positions)
  return &ee_positions_;
}

// repeated float target_EE_positions = 4;
inline int RobotData::target_ee_positions_size() const {
  return target_ee_positions_.size();
}
inline void RobotData::clear_target_ee_positions() {
  target_ee_positions_.Clear();
}
inline float RobotData::target_ee_positions(int index) const {
  // @@protoc_insertion_point(field_get:RobotData.target_EE_positions)
  return target_ee_positions_.Get(index);
}
inline void RobotData::set_target_ee_positions(int index, float value) {
  target_ee_positions_.Set(index, value);
  // @@protoc_insertion_point(field_set:RobotData.target_EE_positions)
}
inline void RobotData::add_target_ee_positions(float value) {
  target_ee_positions_.Add(value);
  // @@protoc_insertion_point(field_add:RobotData.target_EE_positions)
}
inline const ::google::protobuf::RepeatedField< float >&
RobotData::target_ee_positions() const {
  // @@protoc_insertion_point(field_list:RobotData.target_EE_positions)
  return target_ee_positions_;
}
inline ::google::protobuf::RepeatedField< float >*
RobotData::mutable_target_ee_positions() {
  // @@protoc_insertion_point(field_mutable_list:RobotData.target_EE_positions)
  return &target_ee_positions_;
}

// optional float reward = 5;
inline void RobotData::clear_reward() {
  reward_ = 0;
}
inline float RobotData::reward() const {
  // @@protoc_insertion_point(field_get:RobotData.reward)
  return reward_;
}
inline void RobotData::set_reward(float value) {
  
  reward_ = value;
  // @@protoc_insertion_point(field_set:RobotData.reward)
}

// optional bool collision_flag = 6;
inline void RobotData::clear_collision_flag() {
  collision_flag_ = false;
}
inline bool RobotData::collision_flag() const {
  // @@protoc_insertion_point(field_get:RobotData.collision_flag)
  return collision_flag_;
}
inline void RobotData::set_collision_flag(bool value) {
  
  collision_flag_ = value;
  // @@protoc_insertion_point(field_set:RobotData.collision_flag)
}

// optional bool done_flag = 7;
inline void RobotData::clear_done_flag() {
  done_flag_ = false;
}
inline bool RobotData::done_flag() const {
  // @@protoc_insertion_point(field_get:RobotData.done_flag)
  return done_flag_;
}
inline void RobotData::set_done_flag(bool value) {
  
  done_flag_ = value;
  // @@protoc_insertion_point(field_set:RobotData.done_flag)
}

// -------------------------------------------------------------------

// RobotDataFrameList

// repeated .RobotData robot_data_frames = 1;
inline int RobotDataFrameList::robot_data_frames_size() const {
  return robot_data_frames_.size();
}
inline void RobotDataFrameList::clear_robot_data_frames() {
  robot_data_frames_.Clear();
}
inline const ::RobotData& RobotDataFrameList::robot_data_frames(int index) const {
  // @@protoc_insertion_point(field_get:RobotDataFrameList.robot_data_frames)
  return robot_data_frames_.Get(index);
}
inline ::RobotData* RobotDataFrameList::mutable_robot_data_frames(int index) {
  // @@protoc_insertion_point(field_mutable:RobotDataFrameList.robot_data_frames)
  return robot_data_frames_.Mutable(index);
}
inline ::RobotData* RobotDataFrameList::add_robot_data_frames() {
  // @@protoc_insertion_point(field_add:RobotDataFrameList.robot_data_frames)
  return robot_data_frames_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::RobotData >*
RobotDataFrameList::mutable_robot_data_frames() {
  // @@protoc_insertion_point(field_mutable_list:RobotDataFrameList.robot_data_frames)
  return &robot_data_frames_;
}
inline const ::google::protobuf::RepeatedPtrField< ::RobotData >&
RobotDataFrameList::robot_data_frames() const {
  // @@protoc_insertion_point(field_list:RobotDataFrameList.robot_data_frames)
  return robot_data_frames_;
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_robot_5fdata_2eproto__INCLUDED
