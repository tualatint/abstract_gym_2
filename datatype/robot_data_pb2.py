# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: robot_data.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='robot_data.proto',
  package='',
  syntax='proto3',
  serialized_pb=_b('\n\x10robot_data.proto\"\xa9\x01\n\tRobotData\x12\x17\n\x0fjoint_positions\x18\x01 \x03(\x02\x12\x15\n\rjoint_actions\x18\x02 \x03(\x02\x12\x14\n\x0c\x45\x45_positions\x18\x03 \x03(\x02\x12\x1b\n\x13target_EE_positions\x18\x04 \x03(\x02\x12\x0e\n\x06reward\x18\x05 \x01(\x02\x12\x16\n\x0e\x63ollision_flag\x18\x06 \x01(\x08\x12\x11\n\tdone_flag\x18\x07 \x01(\x08\";\n\x12RobotDataFrameList\x12%\n\x11robot_data_frames\x18\x01 \x03(\x0b\x32\n.RobotDatab\x06proto3')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_ROBOTDATA = _descriptor.Descriptor(
  name='RobotData',
  full_name='RobotData',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='joint_positions', full_name='RobotData.joint_positions', index=0,
      number=1, type=2, cpp_type=6, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='joint_actions', full_name='RobotData.joint_actions', index=1,
      number=2, type=2, cpp_type=6, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='EE_positions', full_name='RobotData.EE_positions', index=2,
      number=3, type=2, cpp_type=6, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='target_EE_positions', full_name='RobotData.target_EE_positions', index=3,
      number=4, type=2, cpp_type=6, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='reward', full_name='RobotData.reward', index=4,
      number=5, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='collision_flag', full_name='RobotData.collision_flag', index=5,
      number=6, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='done_flag', full_name='RobotData.done_flag', index=6,
      number=7, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=21,
  serialized_end=190,
)


_ROBOTDATAFRAMELIST = _descriptor.Descriptor(
  name='RobotDataFrameList',
  full_name='RobotDataFrameList',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='robot_data_frames', full_name='RobotDataFrameList.robot_data_frames', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=192,
  serialized_end=251,
)

_ROBOTDATAFRAMELIST.fields_by_name['robot_data_frames'].message_type = _ROBOTDATA
DESCRIPTOR.message_types_by_name['RobotData'] = _ROBOTDATA
DESCRIPTOR.message_types_by_name['RobotDataFrameList'] = _ROBOTDATAFRAMELIST

RobotData = _reflection.GeneratedProtocolMessageType('RobotData', (_message.Message,), dict(
  DESCRIPTOR = _ROBOTDATA,
  __module__ = 'robot_data_pb2'
  # @@protoc_insertion_point(class_scope:RobotData)
  ))
_sym_db.RegisterMessage(RobotData)

RobotDataFrameList = _reflection.GeneratedProtocolMessageType('RobotDataFrameList', (_message.Message,), dict(
  DESCRIPTOR = _ROBOTDATAFRAMELIST,
  __module__ = 'robot_data_pb2'
  # @@protoc_insertion_point(class_scope:RobotDataFrameList)
  ))
_sym_db.RegisterMessage(RobotDataFrameList)


# @@protoc_insertion_point(module_scope)
