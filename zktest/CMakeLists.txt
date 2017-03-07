
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(ZKTEST)
SET(SRC_LIST main.cpp ZkLock.cpp zoo_lock.c)

INCLUDE_DIRECTORIES(/usr/local/include/zookeeper)
LINK_DIRECTORIES(/usr/local/lib)

ADD_EXECUTABLE(zktest ${SRC_LIST})
TARGET_LINK_LIBRARIES(zktest pthread libzookeeper_mt.a)

