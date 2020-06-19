cmake_minimum_required(VERSION 3.16)
project(mysql_test)
set(CMAKE_CXX_STANDARD 17)

message(STATUS "--------------------------------------------------------------")
message(STATUS "start ${PROJECT_NAME} build.")
message(STATUS "--------------------------------------------------------------")

if (UNIX AND NOT APPLE)
    # linux
    message(STATUS "check unix(not osx) setting values")

    set(BOOST_DIR "")
    set(Boost_INCLUDE_DIRS "")
    set(MYSQL_LIB_ROOT_DIR "/usr/local")
    set(MYSQL_LIB_DIR "${MYSQL_LIB_ROOT_DIR}/lib")
    set(MYSQL_LIB_INCLUDE_DIR "${MYSQL_LIB_ROOT_DIR}/include")
    set(MYSQL_LIB_NAME "mysqlcppconn")
elseif(APPLE)
    set(BOOST_DIR "/usr/local/Cellar/boost/1.72.0_3")
    set(Boost_INCLUDE_DIRS ${BOOST_DIR}/include)
    set(MYSQL_LIB_ROOT_DIR "/usr/local/Cellar/mysql-connector-c++@1.1/1.1.13_1")
    set(MYSQL_LIB_DIR "${MYSQL_LIB_ROOT_DIR}/lib")
    set(MYSQL_LIB_INCLUDE_DIR "${MYSQL_LIB_ROOT_DIR}/include")
    set(MYSQL_LIB_NAME "mysqlcppconn")
elseif(LINUX)
endif()

# -----------------------------------------------------------------------------------
# boost
# -----------------------------------------------------------------------------------
find_package(Boost REQUIRED)

if (NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found.")
else()
    message(STATUS "Boost found!")
    include_directories(${Boost_INCLUDE_DIRS})
endif()

# -----------------------------------------------------------------------------------
# mysql link
# -----------------------------------------------------------------------------------
find_library(
    LIB_MYSQL_CPP
    NAMES ${MYSQL_LIB_NAME}
    HINTS ${MYSQL_LIB_DIR}
    NO_DEFAULT_PATH
    REQUIRED
)

include_directories(${MYSQL_LIB_INCLUDE_DIR})

add_library(LIB_MYSQL_CPP STATIC IMPORTED)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${LIB_MYSQL_CPP} ${Boost_LIBRARIES})
