

include_directories( ${KOMAIN_INCLUDES} )

## add_subdirectory(demo)


########### library target ###############

set(libemf_LIB_SRCS 
     EmfRecords.cpp
     EmfObjects.cpp
     EmfHeader.cpp
     BitmapHeader.cpp
     EmfParser.cpp
     EmfOutput.cpp
     EmfOutputDebugStrategy.cpp
     EmfOutputPainterStrategy.cpp
)

#kde4_add_library(libemf SHARED ${libemf_LIB_SRCS})

#target_link_libraries(libemf  ${KDE4_KDECORE_LIBS} ${QT_QTGUI_LIBRARY} )

#set_target_properties(libemf PROPERTIES VERSION ${GENERIC_CALLIGRA_LIB_VERSION} SOVERSION ${GENERIC_CALLIGRA_LIB_SOVERSION} )


########### install files ###############

#install(TARGETS libemf  ${INSTALL_TARGETS_DEFAULT_ARGS})

#install(
#    FILES
#    EmfEnums.h
#    EmfRecords.h
#    EmfObjects.h
#    EmfHeader.h
#    Bitmap.h
#    EmfParser.h
#    EmfOutput.h
#    EmfOutputDebugStrategy.h
#    EmfOutputPainterStrategy.h
#    emf_export.h
#    DESTINATION ${INCLUDE_INSTALL_DIR} COMPONENT Devel
#)
