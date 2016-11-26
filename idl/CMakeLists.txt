cmake_minimum_required (VERSION 3.3.0)

project (idl)

file (GLOB TOPICS_IDL "*.idl")

set (OPENDDS_IDL "opendds_idl.exe")
set (TAO_IDL "tao_idl.exe")

set (OPENDDS_IDL_OPTIONS " ")

message (STATUS "Process is ${DDS_ROOT_DIR}/bin/${OPENDDS_IDL}")


add_custom_command(
  OUTPUT TopicsC.h TopicsC.cpp TopicsC.inl TopicsS.h TopicsS.cpp TopicsTypeSupportC.h TopicsTypeSupportC.cpp TopicsTypeSupportS.h TopicsTypeSupport.cpp TopicsTypeSupportImpl.h TopicsTypeSupportImpl.cpp
    COMMAND "${DDS_ROOT_DIR}/bin/${OPENDDS_IDL}" ${OPENDDS_IDL_OPTIONS} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  VERBATIM
)

