

set(kritaselectiontools_PART_SRCS
    selection_tools.cc
    kis_tool_select_rectangular.cc
    kis_tool_select_polygonal.cc
    kis_tool_select_elliptical.cc
    kis_tool_select_contiguous.cc
    kis_tool_select_outline.cc
    kis_tool_select_path.cc
    kis_tool_select_similar.cc
    kis_tool_select_brush.cc
#    kis_tool_select_magnetic.cc
#    kis_tool_select_magnetic_option_widget.cpp
    )

#kde4_add_ui_files(kritaselectiontools_PART_SRCS
#    kis_tool_select_magnetic_option_widget.ui
#)


kde4_add_plugin(kritaselectiontools ${kritaselectiontools_PART_SRCS})



target_link_libraries(kritaselectiontools kritaui basicflakes)

install(TARGETS kritaselectiontools  DESTINATION ${PLUGIN_INSTALL_DIR})


########### install files ###############

install( FILES  tool_path_selection.png
                tool_rect_selection.png
                tool_eraser_selection.png
                tool_brush_selection.png
                tool_contiguous_selection.png
                tool_elliptical_selection.png
                tool_outline_selection.png
                tool_polygonal_selection.png
                tool_rectangular_selection_cursor.png
                tool_eraser_selection_cursor.png
                tool_brush_selection_cursor.png
                tool_contiguous_selection_cursor.png
                tool_elliptical_selection_cursor.png
                tool_outline_selection_cursor.png
                tool_polygonal_selection_cursor.png
                tool_similar_selection.png
                tool_similar_selection_cursor.png
                tool_magneticoutline_selection.png
                tool_magneticoutline_selection_cursor.png
                DESTINATION ${DATA_INSTALL_DIR}/krita/pics)
install( FILES  kritaselectiontools.desktop  DESTINATION ${SERVICES_INSTALL_DIR})


