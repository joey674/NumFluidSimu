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
       )

add_executable(Spider ${SOURCE_FILES})
install(TARGETS Spider DESTINATION ${NUMSTR_INSTALL_BIN_DIR})
install(TARGETS Spider DESTINATION ${NUMSTR_INSTALL_RUN_DIR})
