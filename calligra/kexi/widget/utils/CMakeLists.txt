include_directories( ${CMAKE_SOURCE_DIR}/kexi ${CMAKE_SOURCE_DIR}/kexi/widget/utils ${KDE4_INCLUDES}  )


########### next target ###############

set(kexiguiutils_LIB_SRCS 
   kexisharedactionclient.cpp 
   kexirecordmarker.cpp 
   kexidisplayutils.cpp 
   kexitooltip.cpp
   kexicontextmenuutils.cpp
   kexidropdownbutton.cpp
   kexicomboboxdropdownbutton.cpp
   kexidatetimeformatter.cpp
   KexiDockableWidget.cpp
)

IF (KEXI_MOBILE)

ELSE (KEXI_MOBILE)
    LIST(APPEND kexiguiutils_LIB_SRCS
        kexirecordnavigator.cpp 
    )
ENDIF (KEXI_MOBILE)

kde4_add_library(kexiguiutils SHARED ${kexiguiutils_LIB_SRCS})

target_link_libraries(kexiguiutils
kexicore
kexiutils ${KDE4_KIO_LIBS}
)

IF (KEXI_MOBILE)

ELSE (KEXI_MOBILE)
  target_link_libraries(kexiguiutils
  ${QT_QT3SUPPORT_LIBRARY}
  )
ENDIF (KEXI_MOBILE)



set_target_properties(kexiguiutils PROPERTIES VERSION ${GENERIC_CALLIGRA_LIB_VERSION} SOVERSION ${GENERIC_CALLIGRA_LIB_SOVERSION} )
install(TARGETS kexiguiutils  ${INSTALL_TARGETS_DEFAULT_ARGS})


########### install files ###############






#original Makefile.am contents follow:

#include $(top_srcdir)/kexi/Makefile.global
#
#lib_LTLIBRARIES = libkexiguiutils.la
#libkexiguiutils_la_SOURCES = kexisharedactionclient.cpp kexirecordnavigator.cpp \
#	kexigradientwidget.cpp kexirecordmarker.cpp kexidisplayutils.cpp \
#	kexiflowlayout.cpp
#
#libkexiguiutils_la_LDFLAGS = $(all_libraries) $(VER_INFO) -Wnounresolved
#libkexiguiutils_la_LIBADD = $(LIB_KDEUI)
#
#SUBDIRS = .
#
## set the include path for X, qt and KDE - all_includes must remain last!
#INCLUDES = -I$(top_srcdir)/kexi -I$(top_srcdir)/kexi/widget/utils $(all_includes)
#
#METASOURCES = AUTO
#
#noinst_HEADERS = kexigradientwidget.h
