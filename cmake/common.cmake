
#Get STM32 HAL driver path
if(NOT DEFINED ENV{STM32F7XX_HAL_DRIVER_PATH})
    message(FATAL_ERROR "Please specify the STM32F7XX_HAL_DRIVER_PATH environment variable!\nFor example: export STM32F7XX_HAL_DRIVER_PATH=\"C:/Users/You/Desktop/stm32h7xx_hal_driver/\"")
else()
    message(STATUS "Received STM32F7XX_HAL_DRIVER_PATH: $ENV{STM32F7XX_HAL_DRIVER_PATH}")
endif()

#Get CMSIS device specific path
if(NOT DEFINED ENV{CMSIS_DEVICE_F7_PATH})
    message(FATAL_ERROR "Please specify the CMSIS_DEVICE_F7_PATH environment variable!\nFor example: export CMSIS_DEVICE_F7_PATH=\"C:/Users/You/Desktop/cmsis_device_f7/\"")
else()
    message(STATUS "Received CMSIS_DEVICE_F7_PATH: $ENV{CMSIS_DEVICE_F7_PATH}")
endif()

#Get CMSIS core path
if(NOT DEFINED ENV{CMSIS_CORE_PATH})
    message(FATAL_ERROR "Please specify the CMSIS_CORE_PATH environment variable!\nFor example: export CMSIS_CORE_PATH=\"C:/Users/You/Desktop/cmsis_core/\"")
else()
    message(STATUS "Received CMSIS_CORE_PATH: $ENV{CMSIS_CORE_PATH}")
endif()

add_definitions(-DSTM32F777xx)
add_definitions(-DUSE_HAL_DRIVER)
