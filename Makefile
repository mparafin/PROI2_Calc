CC=g++

Calc: main.o Node.o Operation.o Onearg_op.o Expression.o
	$(CC) main.o Node.o Operation.o Onearg_op.o Expression.o -o Calc

clean:
	rm *.o