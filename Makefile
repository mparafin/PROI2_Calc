CC=g++

Calc: main.o Calculator.o Expression.o
	g++ main.o Calculator.o Expression.o -o Calc

main.o: main.cpp Calculator.hpp Expression.hpp
	g++ -c main.cpp

Calculator.o: Calculator.hpp Calculator.cpp
	g++ -c Calculator.cpp

Expression.o: Expression.hpp Expression.cpp Node.hpp
	g++ -c Expression.cpp

clean:
	rm *.o