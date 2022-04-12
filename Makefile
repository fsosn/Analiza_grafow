#CFLAGS = -ggdb3 -Wall -Wextra

graf: main.o incidence.o randval.o to_file.o from_file.o dijkstra.o bfs.o cohesion.o
	$(CC) -ggdb3 -o graf $^

test:
	
	$(CC) -ggdb3 -o test_in_out test_in_out.c
	$(CC) -ggdb3 -o test_kolejka test_kolejka.c bfs.c
	./test_in_out test_data/compare_bfs1 test_data/compare_bfs2 test_data/compare_dij1 test_data/compare_dij2
	./test_kolejka

test_in_out: test_in_out.o
	$(CC) -ggdb3 -o test_in_out $^
	./test_in_out test_data/compare_bfs1 test_data/compare_bfs2 test_data/compare_dij1 test_data/compare_dij2

test_kolejka: test_kolejka.o bfs.o
	$(CC) -ggdb3 -o test_kolejka $^
	./test_kolejka

.PHONY: clean

clean:
	rm -f *.o graf test_in_out test_kolejka test
