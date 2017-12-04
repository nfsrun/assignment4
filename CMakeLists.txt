cmake_minimum_required(VERSION 3.8)
project(assignment4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Launcher.cpp Validator.h BinarySearchTree.h
        Contact.h Contact.cpp cmake-build-debug/phonebook.txt cmake-build-debug/phonebook1.txt)
add_executable(assignment4 ${SOURCE_FILES})