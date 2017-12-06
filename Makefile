CC=g++

Calc: main.o Calculator.o Expression.o Twoarg_op.o Onearg_op.o Argument.o
	g++ main.o Calculator.o Expression.o Twoarg_op.o Argument.o Onearg_op.o -o Calc

main.o: main.cpp Calculator.hpp Expression.hpp
	g++ -c main.cpp

Calculator.o: Calculator.hpp Calculator.cpp
	g++ -c Calculator.cpp

Expression.o: Expression.hpp Expression.cpp Node.hpp Argument.hpp Twoarg_op.hpp
	g++ -c Expression.cpp

Twoarg_op.o: Twoarg_op.hpp Twoarg_op.cpp Expression.hpp
	g++ -c Twoarg_op.cpp

Onearg_op.o: Onearg_op.hpp Onearg_op.cpp Expression.hpp
	g++ -c Onearg_op.cpp

Argument.o: Argument.hpp Argument.cpp
	g++ -c Argument.cpp

clean:
	rm *.o