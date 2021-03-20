CC=gcc
CFLAGS=-Wall -std=c99 -g
BUILD=build
SRC=src
TST=tst
OBJ=sort.o optimization.o
T_EXE=test_sort test_optimization

all:src
	gcc -Wall -std=c99 enonce/src/decrypt.c -o decrypt
	gcc -Wall -std=c99 enonce_pascal/src/stock_diff.c -o stock_diff

src: defi

sort.o:
	${CC} ${CFLAGS} -c stock/${SRC}/sort.c -o stock/${BUILD}/$@

optimization.o:
	${CC} ${CFLAGS} -c stock/${SRC}/optimization.c -o stock/${BUILD}/$@

defi:${OBJ}
	${CC} ${CFLAGS} stock/${BUILD}/* stock/${SRC}/defi.c -o $@

tst:${T_EXE}

test_sort:sort.o
	${CC} ${CFLAGS} stock/${BUILD}/sort.o stock/${TST}/test_sort.c -o $@

test_optimization:${OBJ}
	${CC} ${CFLAGS} stock/${BUILD}/* stock/${TST}/test_optimization.c -o $@

clean:
	rm *~ enonce/*~ enonce/src/*~ enonce/txt/*~ enonce_pascal/*~ enonce_pascal/src/*~ enonce_pascal/txt/*~ stock/*~ stock/build/*~ stock/src/*~ stock/tst/*~ stock/build/*.o
