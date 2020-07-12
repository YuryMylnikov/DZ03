cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
    set(VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    set(VERSION 0.0.0)
endif()

project(UserAllocator VERSION ${VERSION})

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

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)