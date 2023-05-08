cmake_minimum_required(VERSION 3.2)
project(NumStr)

    set(SOURCE_FILES
            data.h
            input.cpp
            input.h
            main.cpp
            output.cpp
            output.h
            setup.cpp
            setup.h
            solve.cpp
            solve.h
       )

add_executable(Dragonfly ${SOURCE_FILES})
install(TARGETS Dragonfly DESTINATION ${NUMSTR_INSTALL_BIN_DIR})
install(TARGETS Dragonfly DESTINATION ${NUMSTR_INSTALL_RUN_DIR})
