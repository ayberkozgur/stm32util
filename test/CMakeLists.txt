cmake_minimum_required(VERSION 3.6)

project(stm32util-tests C CXX)

include("../cmake/common.cmake")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -fpermissive")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14 -fno-exceptions -fno-rtti -fno-threadsafe-statics -fpermissive")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

set(TEST_LIBS "-lgtest -lgtest_main -lpthread")

include_directories($ENV{STM32F7XX_HAL_DRIVER_PATH}/Inc)
include_directories($ENV{STM32F7XX_HAL_DRIVER_PATH}/Legacy/Inc)
include_directories($ENV{CMSIS_DEVICE_F7_PATH}/Include)
include_directories($ENV{CMSIS_CORE_PATH}/Include)
include_directories(../include)

set(GPIO_UTIL_TEST_SOURCES
    gpio/GPIOUtilTest.cpp
)

add_executable(gpio-util-test ${GPIO_UTIL_TEST_SOURCES})
target_link_libraries(gpio-util-test "${TEST_LIBS}")

set(REGISTER_UTIL_TEST_SOURCES
    reg/RegisterUtilTest.cpp
)

add_executable(register-util-test ${REGISTER_UTIL_TEST_SOURCES})
target_link_libraries(register-util-test "${TEST_LIBS}")
