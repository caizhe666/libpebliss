file(GLOB SRC_CPP_FILES "./*.cpp")

add_library(libpebliss ${SRC_CPP_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET libpebliss PROPERTY CXX_STANDARD 20)
endif()
