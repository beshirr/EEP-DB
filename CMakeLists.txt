cmake_minimum_required(VERSION 4.1)
project(EEPDB)

set(CMAKE_CXX_STANDARD 23)

add_executable(EEPDB main.cpp
        include/execution/parser.h
        include/index/BpNode.h
        include/storage/disk_manager.h
        src/execution/parser.cpp
        src/index/BpNode.cpp
        src/storage/disk_manager.cpp
        src/table/table_heap.cpp
        include/storage/page.h
        include/storage/buffer_pool_manager.h
        include/config.h
        include/index/BpTree.h
        src/index/BpTree.cpp
        src/index/PageManager.cpp
        include/index/PageManager.h)
