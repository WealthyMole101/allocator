cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(allocator VERSION ${PROJECT_VESRION})

# find_package(Boost COMPONENTS system unit_test_framework REQUIRED)
find_package(GTest REQUIRED)

configure_file(version.h.in version.h)

add_executable(allocator_cli main.cpp)
add_library(allocator lib.cpp)
#add_executable(test_version test_version.cpp)
#add_executable(test_version_gtest test_version_gtest.cpp)

#set_target_properties(allocator_cli allocator test_version PROPERTIES
#    CXX_STANDARD 14
#    CXX_STANDARD_REQUIRED ON
#)

set_target_properties(allocator_cli allocator PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(allocator
    PRIVATE "${CMAKE_BINARY_DIR}"
)
#set_target_properties(test_version PROPERTIES
#    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
#    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
#)

target_link_libraries(allocator_cli PRIVATE
    allocator
#    boost_system
)
#target_link_libraries(test_version
#    ${Boost_LIBRARIES}
#    allocator
#    pthread
#)

target_link_libraries(
    allocator
    pthread
)

#target_include_directories(test_version_gtest
#    PRIVATE ${GTEST_INCLUDE_DIRS}
#)
#target_link_libraries(
#    test_version_gtest
#    ${GTEST_BOTH_LIBRARIES}
#    allocator
#    pthread
#)

target_link_libraries(
    allocator
    pthread
)

if (MSVC)
    target_compile_options(allocator_cli PRIVATE
        /W4
    )
    target_compile_options(allocator PRIVATE
        /W4
    )
    target_compile_options(test_version PRIVATE
        /W4
    )
else ()
    target_compile_options(allocator_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    #target_compile_options(test_version PRIVATE
    #    -Wall -Wextra -pedantic -Werror
    #)
endif()



install(TARGETS allocator_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT vbespalov@astralinux.ru)

include(CPack)

enable_testing()

#add_test(test_version test_version)
#add_test(test_version_gtest test_version_gtest) 