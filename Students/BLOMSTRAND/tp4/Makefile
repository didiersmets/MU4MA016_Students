CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

all: main_pq main_avl

main_pq: main_pq.o prio_q.o
	$(CC) $(CFLAGS) -o $@ $^

main_avl: main_avl.o avl_tree.o
	$(CC) $(CFLAGS) -o $@ $^

main_pq.o: main_pq.c prio_q.h
	$(CC) $(CFLAGS) -c main_pq.c

prio_q.o: prio_q.c prio_q.h
	$(CC) $(CFLAGS) -c prio_q.c

main_avl.o: main_avl.c avl_tree.h
	$(CC) $(CFLAGS) -c main_avl.c

avl_tree.o: avl_tree.c avl_tree.h
	$(CC) $(CFLAGS) -c avl_tree.c

clean:
	rm -f *.o main_pq main_avl
