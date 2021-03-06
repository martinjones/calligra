add_subdirectory( tests )

add_definitions(${KDE4_ENABLE_EXCEPTIONS})

if (APPLE)
    find_library(FOUNDATION_LIBRARY Foundation)
endif (APPLE)

include_directories( ${KOMAIN_INCLUDES})

########### next target ###############

if( QCA2_FOUND )
   add_definitions( -DQCA2 )
endif( QCA2_FOUND )

set(komain_LIB_SRCS
    KoAutoSaveRecoveryDialog.cpp
    KoApplication.cpp
    KoDockerManager.cpp
    KoDocument.cpp
    KoDocumentEntry.cpp
    KoDocumentInfo.cpp
    KoDocumentInfoDlg.cpp
    KoDocumentInfoPropsPage.cpp
    KoFileDialog.cpp
    KoGlobal.cpp
    KoGridData.cpp
    KoMainWindow.cpp
    KoPrintingDialog.cpp
    KoPrintJob.cpp
    KoRulerController.cpp
    KoRuler.cpp
    KoModeBox.cpp
    KoModeBoxDocker.cpp
    KoModeBoxFactory.cpp
    KoToolBox.cpp
    KoToolBoxDocker.cpp
    KoToolBoxFactory.cpp
    KoToolDocker_p.cpp
    KoVersionDialog.cpp
    KoView.cpp
    calligraversion.cpp
    KoFilterManager.cpp
    KoFilterChain.cpp
    KoFilter.cpp
    KoFilterEntry.cpp
    KoFilterManager_p.cpp
    KoFilterVertex.cpp
    KoFilterGraph.cpp
    KoFilterEdge.cpp
    KoFilterChainLink.cpp
    KoFilterChainLinkList.cpp
    KoStandardAction.cpp
    KoUndoStackAction.cpp
    config/KoConfigDocumentPage.cpp
    config/KoConfigGridPage.cpp
    config/KoConfigMiscPage.cpp
    config/KoConfigAuthorPage.cpp

    KoDocumentSectionDelegate.cpp
    KoDocumentSectionToolTip.cpp
    KoDocumentSectionView.cpp

    KoDetailsPane.cpp
    KoExistingDocumentPane.cpp
    KoOpenPane.cpp
    KoRecentDocumentsPane.cpp
    KoTemplate.cpp
    KoTemplateCreateDia.cpp
    KoTemplateGroup.cpp
    KoTemplates.cpp
    KoTemplatesPane.cpp
    KoTemplateTree.cpp

    KoFindBase.cpp
    KoFindMatch.cpp
    KoFindText.cpp
    KoFindToolbar.cpp
    KoFindOption.cpp
    KoFindOptionSet.cpp
    KoFindStyle.cpp

    KoPart.cpp

    thememanager.cpp
)

if( QT_QTDBUS_FOUND )
    set(komain_LIB_SRCS ${komain_LIB_SRCS}
        KoApplicationAdaptor.cpp
        KoViewAdaptor.cpp
        KoPartAdaptor.cpp
    )
endif( QT_QTDBUS_FOUND )

if (APPLE)
    set(komain_LIB_SRCS ${komain_LIB_SRCS}
        MacSupport.mm
    )
endif (APPLE)

kde4_add_ui_files( komain_LIB_SRCS
   koDocumentInfoAboutWidget.ui
   koDocumentInfoAuthorWidget.ui
   config/KoConfigAuthorPage.ui
   KoOpenPaneBase.ui
   KoDetailsPaneBase.ui
)

QT5_WRAP_CPP(komain_HEADERS_MOC KoDocumentSectionPropertyAction_p.h)


kde4_add_library(komain SHARED ${komain_HEADERS_MOC} ${komain_LIB_SRCS})

target_link_libraries(komain ${extra_libs}
    ${KDE4_KFILE_LIBRARY}
    kowidgets
    kotextlayout
    kofake
)

if( KActivities_FOUND )
    include_directories(${KACTIVITIES_INCLUDES})
    target_link_libraries(komain ${KACTIVITIES_LIBRARY})
    target_link_libraries(komain LINK_INTERFACE_LIBRARIES  ${KACTIVITIES_LIBRARY})
endif( KActivities_FOUND )

if (APPLE)
    target_link_libraries(komain ${FOUNDATION_LIBRARY})
endif (APPLE)

target_link_libraries(komain LINK_INTERFACE_LIBRARIES kotext kowidgets kofake)

set_target_properties(komain PROPERTIES
    VERSION ${GENERIC_CALLIGRA_LIB_VERSION} SOVERSION ${GENERIC_CALLIGRA_LIB_SOVERSION}
)
install(TARGETS komain ${INSTALL_TARGETS_DEFAULT_ARGS} )

########### install files ###############

install(FILES calligradocker.desktop DESTINATION ${SERVICETYPES_INSTALL_DIR} )
install(FILES calligra_shell.rc DESTINATION ${DATA_INSTALL_DIR}/calligra )

if (APPLE)
    install(FILES osx.stylesheet DESTINATION ${DATA_INSTALL_DIR}/calligra )
endif (APPLE)

install( FILES
    KoApplication.h
    KoDocument.h
    KoDocumentEntry.h
    KoDocumentInfo.h
    KoDocumentSectionModel.h
    KoFilter.h
    KoFilterChain.h
    KoFilterChainLinkList.h
    KoFilterEntry.h
    KoFilterGraph.h
    KoFilterManager.h
    KoFilterVertex.h
    KoFindBase.h
    KoFindText.h
    KoFindToolbar.h
    KoFindMatch.h
    KoFindOption.h
    KoFindOptionSet.h
    KoGlobal.h
    KoGridData.h
    KoMainWindow.h
    KoPageWidgetItem.h
    MacSupport.h
    KoModeBoxFactory.h
    KoPart.h
    KoPrintJob.h
    KoVersionDialog.h
    KoView.h
    calligraversion.h
    KoStandardAction.h
    KoDetailsPane.h
    komain_export.h
DESTINATION ${INCLUDE_INSTALL_DIR}/calligra COMPONENT Devel)

if( QT_QTDBUS_FOUND )
    install( FILES
        KoApplicationAdaptor.h
        KoViewAdaptor.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/calligra COMPONENT Devel)
endif( QT_QTDBUS_FOUND )
