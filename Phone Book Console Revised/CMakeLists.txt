cmake_minimum_required(VERSION 3.9)
project(Phone_Book_Console_Revised)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE FILES launcher.cpp Contact.h Contact.cpp)
add_executable(Phone_Book_Console_Revised launcher.cpp Contact.h Contact.cpp)