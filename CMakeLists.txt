cmake_minimum_required(VERSION 3.2)
project(NumStr)

    set(SOURCE_FILES
            data.cpp
            data.h
            input.cpp
            input.h
            main.cpp
            metrics.cpp
            metrics.h
            output.cpp
            output.h
            setup.cpp
            setup.h
            solve.cpp
            solve.h
       )

add_executable(Hummingbird ${SOURCE_FILES})
install(TARGETS Hummingbird DESTINATION ${NUMSTR_INSTALL_BIN_DIR})
install(TARGETS Hummingbird DESTINATION ${NUMSTR_INSTALL_RUN_DIR})
