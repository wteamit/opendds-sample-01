cmake_minimum_required (VERSION 3.3.0)

project (publisher)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

include_directories (${DDS_ROOT_DIR} "${DDS_ROOT_DIR}/ACE_wrappers" "${DDS_ROOT_DIR}/ACE_wrappers/TAO" ${CMAKE_SOURCE_DIR})

file (GLOB_RECURSE PUBLISHER_SRC *.cpp)
file (GLOB_RECURSE IDL_SRC ${CMAKE_SOURCE_DIR}/idl/*.cpp)
configure_file("${CMAKE_SOURCE_DIR}/configuration/configuration.ini" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/configuration.ini" COPYONLY)
add_executable (${PROJECT_NAME} ${PUBLISHER_SRC} ${IDL_SRC})
message (STATUS "input configutation: ${CMAKE_SOURCE_DIR}/configuration/configuration.ini")
message (STATUS "output configuration: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/configuration.ini")

# Adding DDS link_libraries

file (GLOB OpenDDS_LIBS "${DDS_ROOT_DIR}/lib/*d.dll")
foreach (i ${OpenDDS_LIBS})
  get_filename_component (BASE_NAME_DLL ${i} NAME_WE)
  add_library (${BASE_NAME_DLL} SHARED IMPORTED)
  set_property (TARGET ${BASE_NAME_DLL} PROPERTY IMPORTED_LOCATION "${DDS_ROOT_DIR}/lib/${BASE_NAME_DLL}.dll")
  set_property (TARGET ${BASE_NAME_DLL} PROPERTY IMPORTED_IMPLIB "${DDS_ROOT_DIR}/lib/${BASE_NAME_DLL}.lib")
  target_link_libraries (${PROJECT_NAME} ${BASE_NAME_DLL})
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${BASE_NAME_DLL}> $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endforeach()

file (GLOB OpenDDS_LIBS "${DDS_ROOT_DIR}/ACE_wrappers/lib/*d.dll")
foreach (i ${OpenDDS_LIBS})
  get_filename_component (BASE_NAME_DLL ${i} NAME_WE)
  add_library (${BASE_NAME_DLL} SHARED IMPORTED)
  set_property (TARGET ${BASE_NAME_DLL} PROPERTY IMPORTED_LOCATION "${DDS_ROOT_DIR}/ACE_wrappers/lib/${BASE_NAME_DLL}.dll")
  set_property (TARGET ${BASE_NAME_DLL} PROPERTY IMPORTED_IMPLIB "${DDS_ROOT_DIR}/ACE_wrappers/lib/${BASE_NAME_DLL}.lib")
  target_link_libraries (${PROJECT_NAME} ${BASE_NAME_DLL})
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${BASE_NAME_DLL}> $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endforeach()
