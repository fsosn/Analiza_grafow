#CFLAGS = -ggdb3 -Wall -Wextra

graf: main.o incidence.o randval.o to_file.o from_file.o dijkstra.o bfs.o cohesion.o
	$(CC) -ggdb3 -o graf $^

test_in_out: test_in_out.o
	$(CC) -ggdb3 -o test_in_out $^
	./test_in_out dane/compare_bfs1 dane/compare_bfs2 dane/compare_dij1 dane/compare_dij2

.PHONY: clean

clean:
	rm -f *.o graf test_in_out
