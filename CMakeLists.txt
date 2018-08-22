#--------------------------------------------------------------
# Copyright 2018 Vibha Technologies.  All rights reserved.
# Vibha Technologies Proprietary Information.
#
# Build Parellel Compute
#--------------------------------------------------------------

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
SET(THIS_EXE_NAME ParellelCompute)
PROJECT(${THIS_EXE_NAME})
set (CMAKE_CXX_STANDARD 14)

#----------------------------
# Create source file listing
#----------------------------
FILE(GLOB_RECURSE APP_SRCS  ${CMAKE_CURRENT_LIST_DIR}/src/*.*)
LIST(REMOVE_ITEM APP_SRCS ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp)
#----------------------------
# Include application headers
#----------------------------
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_LIST_DIR}/src/*.*)

#----------------------------
# Set library dependencies
#----------------------------
SET(APP_LIBRARIES crypto pthread)
SET(TST_LIBRARIES gtest gtest_main gmock gmock_main)

#----------------------------
# Build application
#----------------------------

ADD_EXECUTABLE(${THIS_EXE_NAME} ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp ${APP_SRCS})
TARGET_LINK_LIBRARIES(${THIS_EXE_NAME} ${APP_LIBRARIES})

#----------------------------
# Build unit tests
#----------------------------
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_LIST_DIR}/test/*.*)
FILE(GLOB_RECURSE TEST_SRCS ${CMAKE_CURRENT_LIST_DIR}/test/main.cpp)
ADD_EXECUTABLE(test_${THIS_EXE_NAME} ${TEST_SRCS} ${APP_SRCS})
TARGET_LINK_LIBRARIES(test_${THIS_EXE_NAME}  ${TST_LIBRARIES} ${APP_LIBRARIES})	


