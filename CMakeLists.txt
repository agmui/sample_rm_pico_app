# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "rm_pico_dev/lib/pico-sdk")

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(pico_app C CXX ASM)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

set(PICO_CXX_ENABLE_RTTI 1)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()
# if (TARGET tinyusb_device)
# elseif(PICO_ON_DEVICE)
# message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in the SDK")
# endif()

# Add executable. Default name is the project name, version 0.1

#file(GLOB_RECURSE source_list "src/*.cpp" "src/*.hpp")
add_executable(${PROJECT_NAME} src/main.cpp)

pico_set_program_name(${PROJECT_NAME} "pico_app")
pico_set_program_version(${PROJECT_NAME} "0.1")

pico_enable_stdio_uart(${PROJECT_NAME} 1)
pico_enable_stdio_usb(${PROJECT_NAME} 1)

add_subdirectory(rm_pico_dev)

target_sources(${PROJECT_NAME}
      PRIVATE
        src/Core.h
        src/TurretController.h
        src/TurretController.cpp
        src/DriveTrainController.h
        src/DriveTrainController.cpp
)


# Add the standard library to the build
target_link_libraries(${PROJECT_NAME}
            rm_pico_dev)

# Add the standard include files to the build
target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

target_include_directories(${PROJECT_NAME} PRIVATE rm_pico_dev)

# Add any user requested libraries
# target_link_libraries(${PROJECT_NAME} 

#         )
target_include_directories(${PROJECT_NAME} PRIVATE rm_pico_dev/lib/icecream/)

pico_add_extra_outputs(${PROJECT_NAME})

