cmake_minimum_required(VERSION 3.9)
project(Semestralka)

set(CMAKE_CXX_STANDARD 11)

add_executable(Semestralka main.cpp Calculator.h Parser.h Calculator.cpp Parser.cpp Expression.h BigNum.h BinOperator.h Integer.h LongInteger.h Decimal.h Variable.h AddExp.h SubtractExp.h MultiplyExp.h DevideExpr.h BigNum.cpp LongInteger.cpp AddExp.cpp MultiplyExp.cpp Integer.cpp DevideExpr.cpp Decimal.cpp Subtract.cpp Mod.cpp Mod.h Variable.cpp)