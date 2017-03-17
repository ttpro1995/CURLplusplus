cmake_minimum_required(VERSION 2.8)
project(curlplusplus)

FIND_PACKAGE(CURL)
IF(CURL_FOUND)
    INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR})
ELSE(CURL_FOUND)
    MESSAGE(FATAL_ERROR "Could not find the CURL library and development files.")
ENDIF(CURL_FOUND)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES example.cpp CURLplusplus.h
        json/json-forwards.h json/json.h json/jsoncpp.cpp CURLplusplus.cpp utils.h utils.cpp)
add_executable(example ${SOURCE_FILES})
target_link_libraries(example ${CURL_LIBRARIES})