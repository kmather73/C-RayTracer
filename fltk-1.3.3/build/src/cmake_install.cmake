# Install script for directory: C:/Users/neilb_000/Desktop/Depot/Courses/4490/W16/assignments/A1VS2015/A1/A1/trace/trace_skel/Trace/fltk-1.3.3/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/FLTK")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/neilb_000/Desktop/Depot/Courses/4490/W16/assignments/A1VS2015/A1/A1/trace/trace_skel/Trace/fltk-1.3.3/build/lib/Debug/fltkd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/neilb_000/Desktop/Depot/Courses/4490/W16/assignments/A1VS2015/A1/A1/trace/trace_skel/Trace/fltk-1.3.3/build/lib/Release/fltk.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/neilb_000/Desktop/Depot/Courses/4490/W16/assignments/A1VS2015/A1/A1/trace/trace_skel/Trace/fltk-1.3.3/build/lib/MinSizeRel/fltk.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/neilb_000/Desktop/Depot/Courses/4490/W16/assignments/A1VS2015/A1/A1/trace/trace_skel/Trace/fltk-1.3.3/build/lib/RelWithDebInfo/fltk.lib")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/neilb_000/Desktop/Depot/Courses/4490/W16/assignments/A1VS2015/A1/A1/trace/trace_skel/Trace/fltk-1.3.3/build/lib/Debug/fltk_formsd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/neilb_000/Desktop/Depot/Courses/4490/W16/assignments/A1VS2015/A1/A1/trace/trace_skel/Trace/fltk-1.3.3/build/lib/Release/fltk_forms.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/neilb_000/Desktop/Depot/Courses/4490/W16/assignments/A1VS2015/A1/A1/trace/trace_skel/Trace/fltk-1.3.3/build/lib/MinSizeRel/fltk_forms.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/neilb_000/Desktop/Depot/Courses/4490/W16/assignments/A1VS2015/A1/A1/trace/trace_skel/Trace/fltk-1.3.3/build/lib/RelWithDebInfo/fltk_forms.lib")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/neilb_000/Desktop/Depot/Courses/4490/W16/assignments/A1VS2015/A1/A1/trace/trace_skel/Trace/fltk-1.3.3/build/lib/Debug/fltk_imagesd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/neilb_000/Desktop/Depot/Courses/4490/W16/assignments/A1VS2015/A1/A1/trace/trace_skel/Trace/fltk-1.3.3/build/lib/Release/fltk_images.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/neilb_000/Desktop/Depot/Courses/4490/W16/assignments/A1VS2015/A1/A1/trace/trace_skel/Trace/fltk-1.3.3/build/lib/MinSizeRel/fltk_images.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/neilb_000/Desktop/Depot/Courses/4490/W16/assignments/A1VS2015/A1/A1/trace/trace_skel/Trace/fltk-1.3.3/build/lib/RelWithDebInfo/fltk_images.lib")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/neilb_000/Desktop/Depot/Courses/4490/W16/assignments/A1VS2015/A1/A1/trace/trace_skel/Trace/fltk-1.3.3/build/lib/Debug/fltk_gld.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/neilb_000/Desktop/Depot/Courses/4490/W16/assignments/A1VS2015/A1/A1/trace/trace_skel/Trace/fltk-1.3.3/build/lib/Release/fltk_gl.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/neilb_000/Desktop/Depot/Courses/4490/W16/assignments/A1VS2015/A1/A1/trace/trace_skel/Trace/fltk-1.3.3/build/lib/MinSizeRel/fltk_gl.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/neilb_000/Desktop/Depot/Courses/4490/W16/assignments/A1VS2015/A1/A1/trace/trace_skel/Trace/fltk-1.3.3/build/lib/RelWithDebInfo/fltk_gl.lib")
  endif()
endif()

