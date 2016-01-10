cmake_minimum_required(VERSION 2.8)

PROJECT(DERIVATIVES)

SET(CMAKE_BUILD_TYPE Debug)
SET(GCC_COVERAGE_COMPILE_FLAGS "--std=c++11")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

FIND_PACKAGE(Boost 1.55.0 COMPONENTS shared_ptr)

INCLUDE_DIRECTORIES(${DERIVATIVES_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

ADD_EXECUTABLE(derivatives
                    main
                    Derivatives
                    Parameter
                    Result
                    ConstantResult
                    MathFunctions
                    Variable

                    FunctionalTests
                    PerformanceTests
              )

TARGET_LINK_LIBRARIES(derivatives ${Boost_LIBRARIES})
