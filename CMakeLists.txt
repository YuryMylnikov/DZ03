cmake_minimum_required(VERSION 3.2)

project(UserAllocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

configure_file(version.h.in version.h)

add_executable(UserAllocator main.cpp)

set_target_properties(UserAllocator  PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(UserAllocator PRIVATE
        /W4
    )
else ()
    target_compile_options(UserAllocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS UserAllocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)