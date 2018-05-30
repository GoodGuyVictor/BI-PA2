cmake_minimum_required(VERSION 3.9)
project(Semestralka)

set(CMAKE_CXX_STANDARD 11)

add_executable(Semestralka main.cpp CCalculator.h CParser.h CCalculator.cpp CParser.cpp CExpression.h CBigNum.h CBinOperator.h CInteger.h CLongInteger.h CDecimal.h CVariable.h CAddExp.h CSubtractExp.h CMultiplyExp.h CDevideExpr.h CBigNum.cpp CLongInteger.cpp CAddExp.cpp CMultiplyExp.cpp CInteger.cpp CDevideExpr.cpp CDecimal.cpp CSubtract.cpp CModExp.cpp CModExp.h CVariable.cpp)