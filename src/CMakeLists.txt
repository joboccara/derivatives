cmake_minimum_required(VERSION 2.8)

PROJECT(DERIVATIVES)

set(CMAKE_BUILD_TYPE Debug)

FIND_PACKAGE(Boost 1.55.0 COMPONENTS shared_ptr)

INCLUDE_DIRECTORIES(${DERIVATIVES_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

ADD_EXECUTABLE(derivatives
                    main
                    Derivatives
                    Parameter
                    Result
                    ConstantAdditionerResult
                    ConstantMultiplierResult
                    ConstantResult
                    DivisionResult
                    PlusResult
                    MinusResult
                    MultiplyResult
                    Variable

                    FunctionalTests
              )

TARGET_LINK_LIBRARIES(derivatives ${Boost_LIBRARIES})
