#CFLAGS = -ggdb3 -Wall -Wextra

graf: main.o incidence.o randval.o to_file.o
	$(CC) -ggdb3 -o graf $^

.PHONY: clean

clean:
	rm -f *.o graf
