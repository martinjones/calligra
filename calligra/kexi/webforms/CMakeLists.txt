#
# Kexi Web Forms build script
#
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules )

include_directories(
    ${CMAKE_SOURCE_DIR}/kexi/3rdparty/shttpd/src
    ${GOOGLE_CTEMPLATE_INCLUDE_DIR}
    ${PionNet_INCLUDE_DIR})

add_definitions(-DKDE_DEFAULT_DEBUG_AREA=44000)

# Workaround, exceptions are needed for pion-net
# FIXME: This won't work for other compilers
add_definitions(${KDE4_ENABLE_EXCEPTIONS})


# Alternatives
# - ExtJS-based view: a web2.0-ish approach to web forms
#   NOTE: ExtJS is dual licensed, we are using the copy of ExtJS licensed under
#   *GPLv3* License. You can't use the KWebforms with this view in a commercial
#   environment without paying the license, just like Qt.
#   This experimental view is disabled by default
# - Standard HTML based view: this is the standard and most stable view, built by
#   default.
if (WITH_EXTJS_WEBFORMS)
  set(USED_VIEW extjs)
  message(STATUS "Kexi Web Forms: enabled ExtJS view")
  message(STATUS "ExtJS-based view CANNOT be used in commercial environment without paying the license")
  message(STATUS "For more information: http://www.extjs.com/products/license.php")
else (WITH_EXTJS_WEBFORMS)
  set(USED_VIEW default)
  message(STATUS "Kexi Web Forms: enabled default view")
endif (WITH_EXTJS_WEBFORMS)

# Ugly, isn't it?
file(GLOB webforms_view_SRCS view/${USED_VIEW}/*.cpp)
file(GLOB webforms_controller_SRCS controller/${USED_VIEW}/*.cpp)
file(WRITE controller.h.in "#include \"controller/${USED_VIEW}/Controller.h\"")

kde4_add_executable(kwebforms NOGUI
# Other
  ${webforms_controller_SRCS}
  ${webforms_view_SRCS}
# Model
  model/Cache.cpp
  model/DataProvider.cpp
  model/Database.cpp
# Other services
  BlobService.cpp
# Authentication framework
  auth/Authenticator.cpp
  auth/User.cpp
# Main
  main.cpp)

target_link_libraries(kwebforms
    ${KDE4_KDECORE_LIBS}
    ${KDE4_KDEUI_LIBS}
    ${GOOGLE_CTEMPLATE_THREAD_LIB}
    ${PionNet_LIBRARY}
    kexidb
    kexicore
    keximain)

install(TARGETS kwebforms ${INSTALL_TARGETS_DEFAULT_ARGS})
