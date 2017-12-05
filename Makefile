CC=g++

Calc: main.o Calculator.o Expression.o Twoarg_op.o
	g++ main.o Calculator.o Expression.o Twoarg_op.o -o Calc

main.o: main.cpp Calculator.hpp Expression.hpp
	g++ -c main.cpp

Calculator.o: Calculator.hpp Calculator.cpp
	g++ -c Calculator.cpp

Expression.o: Expression.hpp Expression.cpp Node.hpp
	g++ -c Expression.cpp

Twoarg_op.o: Twoarg_op.hpp Twoarg_op.cpp Expression.hpp
	g++ -c Twoarg_op.cpp

clean:
	rm *.o