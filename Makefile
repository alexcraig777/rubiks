CFLAGS = -g -Wall
DEPS = queue.h

%.o: %.c $(DEPS)
	gcc -c $(CFLAGS) -o $@ $<

test: queue.o pocket.o
	gcc $(CFLAGS) -o pocket_test pocket_test.c $^
	valgrind --leak-check=full ./pocket_test

clean:
	rm pocket_test *.o *~
