IF(BINARY)
    ADD_LIBRARY(binary MODULE
        binary.cpp)

    TARGET_LINK_LIBRARIES(binary
        cocaine-core)

    SET_TARGET_PROPERTIES(binary PROPERTIES
        PREFIX ""
        SUFFIX ".cocaine-plugin"
        COMPILE_FLAGS "-std=c++0x")

    INSTALL(TARGETS binary
        LIBRARY DESTINATION lib/cocaine
        COMPONENT runtime)

    INSTALL(
        FILES
            binary.hpp
        DESTINATION include/cocaine/)
ENDIF(BINARY)
