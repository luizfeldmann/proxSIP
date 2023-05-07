cmake_minimum_required(VERSION 3.0.0)

project(proxSIP CXX)

# Find dependency: Boost
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS log json)

# -------------------------------------
# Library
# -------------------------------------

# List of SRCs
set(${CMAKE_PROJECT_NAME}_LIB_SOURCES
    "src/proxSIP/CAsioUdpServer.cpp"
    "src/proxSIP/ESipMethod.cpp"
    "src/proxSIP/CSipParser.cpp"
    "src/proxSIP/CSipMessageHandler.cpp"
    "src/proxSIP/CEndpoint.cpp"
    "src/proxSIP/CSIPRequest.cpp"
    "src/proxSIP/CSipResponse.cpp")

# List of headers
set(${CMAKE_PROJECT_NAME}_LIB_HEADERS
    "include/proxSIP/IUserAccount.h"
    "include/proxSIP/IUserAccountCollection.h"
    "include/proxSIP/IUdpServer.h"
    "include/proxSIP/CAsioUdpServer.h"
    "include/proxSIP/IUdpMessageHandler.h"
    "include/proxSIP/ISIPRequest.h"
    "include/proxSIP/CSIPRequest.h"
    "include/proxSIP/ISipRequestHandler.h"
    "include/proxSIP/ISIPResponse.h"
    "include/proxSIP/CSIPResponse.h"
    "include/proxSIP/ISipResponseHandler.h" 
    "include/proxSIP/ESipMethods.h"
    "include/proxSIP/CSipParser.h"
    "include/proxSIP/CSipMessageHandler.h"
    "include/proxSIP/IEndpoint.h"
    "include/proxSIP/CEndpoint.h" "include/proxSIP/proxSIPExports.h")

# Create and configure the library
add_library(${CMAKE_PROJECT_NAME}_LIB SHARED
    ${${CMAKE_PROJECT_NAME}_LIB_SOURCES}
    ${${CMAKE_PROJECT_NAME}_LIB_HEADERS}
 )

target_compile_definitions(${CMAKE_PROJECT_NAME}_LIB PRIVATE
    -DPROXSIP_EXPORT)

set_target_properties(${CMAKE_PROJECT_NAME}_LIB PROPERTIES
    OUTPUT_NAME "${CMAKE_PROJECT_NAME}")

target_include_directories(${CMAKE_PROJECT_NAME}_LIB PRIVATE
    "include/proxSIP")

target_include_directories(${CMAKE_PROJECT_NAME}_LIB INTERFACE
    "include")

target_link_libraries(${CMAKE_PROJECT_NAME}_LIB PRIVATE Boost::boost Boost::log Boost::json)

# -------------------------------------
# Application
# -------------------------------------

# List of SRCs
set(${CMAKE_PROJECT_NAME}_APP_SOURCES
    "src/Application/main.cpp")

# List of headers
set(${CMAKE_PROJECT_NAME}_APP_HEADERS
    )

# Create and configure the application
add_executable(${CMAKE_PROJECT_NAME}_APP
    ${${CMAKE_PROJECT_NAME}_APP_SOURCES}
    ${${CMAKE_PROJECT_NAME}_APP_HEADERS}
 )

set_target_properties(${CMAKE_PROJECT_NAME}_APP PROPERTIES
    OUTPUT_NAME "${CMAKE_PROJECT_NAME}")

target_include_directories(${CMAKE_PROJECT_NAME}_APP PUBLIC
    "include/Application")

target_link_libraries(${CMAKE_PROJECT_NAME}_APP ${CMAKE_PROJECT_NAME}_LIB)

# -------------------------------------
# Global
# -------------------------------------

if (WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
endif()