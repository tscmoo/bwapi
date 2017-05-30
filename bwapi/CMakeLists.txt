
option(USE_OPENBW "Use OpenBW" ON)

include_directories(include)

if (USE_OPENBW)
  include_directories(OpenBWData)
  add_subdirectory(OpenBWData)
  add_library(BWData ALIAS OpenBWData)
endif()

add_subdirectory(BWAPICore)
add_subdirectory(BWAPILIB)
add_subdirectory(BWAPI)
add_subdirectory(BWAPILauncher)
add_subdirectory(BWAPIClient)

add_subdirectory(ExampleAIModule)
add_subdirectory(TestAIModule)

install(FILES "./include/BWAPI.h" DESTINATION include)
install(DIRECTORY "./include/BWAPI" DESTINATION include)
