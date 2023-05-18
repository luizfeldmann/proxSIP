cmake_minimum_required(VERSION 3.0.0)

project(proxSIP
    VERSION 1.0.0.0
    DESCRIPTION "A lightweight SIP proxy"
    LANGUAGES CXX)

# Find dependency: Boost
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS log json)

# Configure resources file
if (WIN32)
    SET(RESOURCES_FILE "resources.rc")
    configure_file("resources/resources.in.rc" "${RESOURCES_FILE}")
endif()

# -------------------------------------
# Library
# -------------------------------------

# List of SRCs
set(${CMAKE_PROJECT_NAME}_LIB_SOURCES
    # Internal
    "src/proxSIP/Internal/CEndpointImpl.cpp"
    "src/proxSIP/Internal/CSIPRequestImpl.cpp"
    "src/proxSIP/Internal/CSIPResponseImpl.cpp"
    "src/proxSIP/Internal/CKeyValuePairImpl.cpp"
    "src/proxSIP/Internal/CKeyValueCollectionImpl.cpp"
    "src/proxSIP/Internal/CAuthValidatorImpl.cpp"
    "src/proxSIP/Internal/CAuthDigestImpl.cpp"
    "src/proxSIP/Internal/CSipContactImpl.cpp"
    "src/proxSIP/Internal/TSIPFieldImpl.cpp"
    "src/proxSIP/Internal/CSipViaImpl.cpp"
    "src/proxSIP/Internal/CSipURIImpl.cpp"
    "src/proxSIP/Internal/CSipRegistryImpl.cpp"
    "src/proxSIP/Internal/CSipServerImpl.cpp"
    "src/proxSIP/Internal/CAsioUdpServerImpl.cpp"
    # Public
    "${RESOURCES_FILE}"
    "src/proxSIP/CAsioUdpServer.cpp"
    "src/proxSIP/ESipMethod.cpp"
    "src/proxSIP/ESipField.cpp"
    "src/proxSIP/ESipParameter.cpp"
    "src/proxSIP/ESipStatusCode.cpp"
    "src/proxSIP/ESipURIComponents.cpp"
    "src/proxSIP/CSipSerializer.cpp"
    "src/proxSIP/CSipParser.cpp"
    "src/proxSIP/CSipMessageHandler.cpp"
    "src/proxSIP/CEndpoint.cpp"
    "src/proxSIP/CKeyValuePair.cpp"
    "src/proxSIP/CKeyValueCollection.cpp"
    "src/proxSIP/CSIPRequest.cpp"
    "src/proxSIP/CSipResponse.cpp"
    "src/proxSIP/CAuthValidator.cpp"
    "src/proxSIP/CSipURI.cpp"
    "src/proxSIP/CSipContact.cpp"
    "src/proxSIP/CSipVia.cpp"
    "src/proxSIP/CSipRegistry.cpp"
    "src/proxSIP/CSipServer.cpp" )

# List of headers
set(${CMAKE_PROJECT_NAME}_LIB_HEADERS
    # Internal
    "include/proxSIP/Internal/CEndpointImpl.h"
    "include/proxSIP/Internal/TContainer.h"
    "include/proxSIP/Internal/TSIPMessageImpl.h"
    "include/proxSIP/Internal/TSIPFieldImpl.h"
    "include/proxSIP/Internal/TEndpoint.h"
    "include/proxSIP/Internal/CSIPRequestImpl.h"
    "include/proxSIP/Internal/CSIPResponseImpl.h"
    "include/proxSIP/Internal/CSipURIImpl.h"
    "include/proxSIP/Internal/CSipContactImpl.h"
    "include/proxSIP/Internal/CSipViaImpl.h"
    "include/proxSIP/Internal/CKeyValuePairImpl.h"
    "include/proxSIP/Internal/CKeyValueCollectionImpl.h"
    "include/proxSIP/Internal/CAuthValidatorImpl.h"
    "include/proxSIP/Internal/CAuthDigestImpl.h"
    "include/proxSIP/Internal/CSipRegistryImpl.h"
    "include/proxSIP/Internal/CAsioUdpServerImpl.h"
    "include/proxSIP/Internal/CSipServerImpl.h"
    # Public
    "include/proxSIP/proxSIPExports.h"
    "include/proxSIP/IAuthValidator.h"
    "include/proxSIP/CAuthValidator.h"
    "include/proxSIP/ISipRegistry.h"
    "include/proxSIP/CSipRegistry.h"
    "include/proxSIP/IAuthDigest.h"
    "include/proxSIP/ISipURI.h"
    "include/proxSIP/CSipURI.h"
    "include/proxSIP/ISipContact.h"
    "include/proxSIP/CSipContact.h"
    "include/proxSIP/ISipVia.h"
    "include/proxSIP/CSipVia.h"
    "include/proxSIP/IContainer.h"
    "include/proxSIP/IUserAccountCollection.h"
    "include/proxSIP/IUdpServer.h"
    "include/proxSIP/CAsioUdpServer.h"
    "include/proxSIP/IOutputBuffer.h"
    "include/proxSIP/IBuffer.h"
    "include/proxSIP/TBuffer.h"
    "include/proxSIP/IKeyValuePair.h"
    "include/proxSIP/CKeyValuePair.h"
    "include/proxSIP/IKeyValueCollection.h"
    "include/proxSIP/CKeyValueCollection.h"
    "include/proxSIP/IUdpMessageHandler.h"
    "include/proxSIP/IUdpMessageSender.h"
    "include/proxSIP/ISIPMessage.h"
    "include/proxSIP/ISIPRequest.h"
    "include/proxSIP/CSIPRequest.h"
    "include/proxSIP/ISipRequestHandler.h"
    "include/proxSIP/ISIPResponse.h"
    "include/proxSIP/CSIPResponse.h"
    "include/proxSIP/ISipMessageSender.h"
    "include/proxSIP/ISipResponseHandler.h" 
    "include/proxSIP/ESipMethods.h"
    "include/proxSIP/ISipField.h"
    "include/proxSIP/ESipField.h"
    "include/proxSIP/ESipParameter.h"
    "include/proxSIP/ESipStatusCode.h"
    "include/proxSIP/ESipURIComponents.h"
    "include/proxSIP/CSipSerializer.h"
    "include/proxSIP/CSipParser.h"
    "include/proxSIP/CSipMessageHandler.h"
    "include/proxSIP/IEndpoint.h"
    "include/proxSIP/CEndpoint.h"
    "include/proxSIP/CSipServer.h" )

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

target_link_libraries(${CMAKE_PROJECT_NAME}_LIB PRIVATE Boost::boost Boost::log)

# -------------------------------------
# Application
# -------------------------------------

# Configure pre-processed file containing version information
SET(VERSION_FILE "version.h")
configure_file("include/Application/version.in.h" "${VERSION_FILE}" @ONLY)

# List of SRCs
set(${CMAKE_PROJECT_NAME}_APP_SOURCES
    "${RESOURCES_FILE}"
    "src/Application/main.cpp"
    "src/Application/CAppConfig.cpp" )

# List of headers
set(${CMAKE_PROJECT_NAME}_APP_HEADERS
    "${VERSION_FILE}"
    "include/Application/CAppConfig.h")

# Create and configure the application
add_executable(${CMAKE_PROJECT_NAME}_APP
    ${${CMAKE_PROJECT_NAME}_APP_SOURCES}
    ${${CMAKE_PROJECT_NAME}_APP_HEADERS}
 )

set_target_properties(${CMAKE_PROJECT_NAME}_APP PROPERTIES
    OUTPUT_NAME "${CMAKE_PROJECT_NAME}")

target_include_directories(${CMAKE_PROJECT_NAME}_APP PUBLIC
    "${CMAKE_CURRENT_BINARY_DIR}"
    "include/Application")

target_link_libraries(${CMAKE_PROJECT_NAME}_APP PRIVATE 
    ${CMAKE_PROJECT_NAME}_LIB
    Boost::boost Boost::log Boost::json)

# Copy configuration file to the output location
set(APP_CFG_FILE "${CMAKE_CURRENT_LIST_DIR}/resources/${CMAKE_PROJECT_NAME}.json")

add_custom_command(TARGET ${CMAKE_PROJECT_NAME}_APP POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${APP_CFG_FILE}" "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}_APP>")

# -------------------------------------
# Global
# -------------------------------------

if (WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
endif()