cmake_minimum_required(VERSION 3.2)
project(NumStr)

    set(SOURCE_FILES    
        source/*.cpp
        source/*.h
    )

add_executable(Hummingbird ${SOURCE_FILES})
install(TARGETS Hummingbird DESTINATION ${NUMSTR_INSTALL_BIN_DIR})
install(TARGETS Hummingbird DESTINATION ${NUMSTR_INSTALL_RUN_DIR})
