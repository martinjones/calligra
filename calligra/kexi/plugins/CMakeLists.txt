add_definitions(-DKDE_DEFAULT_DEBUG_AREA=44021)

add_subdirectory( reports )
#add_subdirectory(autoforms)

if (KEXI_MOBILE)
  
    
else (KEXI_MOBILE)
  add_subdirectory( tables )
  add_subdirectory( queries )
  add_subdirectory( forms )
  add_subdirectory( migration )
  add_subdirectory( importexport )

  if(SHOULD_BUILD_SCRIPTING AND KEXI_SCRIPTS_SUPPORT)
     add_subdirectory(scripting)
  endif(SHOULD_BUILD_SCRIPTING AND KEXI_SCRIPTS_SUPPORT)
  add_subdirectory( shapes )
endif (KEXI_MOBILE)

#TODO add_subdirectory( relations )
#TODO add_subdirectory(macros)
