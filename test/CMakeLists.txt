add_library(utest STATIC)
target_sources(utest 
    PRIVATE
        utest.h utest.c
)
target_include_directories(utest
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)
set_target_properties(utest
    PROPERTIES FOLDER utest
)
