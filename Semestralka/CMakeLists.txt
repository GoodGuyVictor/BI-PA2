cmake_minimum_required(VERSION 3.9)
project(Semestralka)

set(CMAKE_CXX_STANDARD 11)

add_executable(Semestralka main.cpp CCalculator.h CCparser.h COperand.h CInteger.h CLongInteger.h CDecimal.h CVariable.h CCalculator.cpp CParser.cpp COperand.cpp CInteger.cpp)