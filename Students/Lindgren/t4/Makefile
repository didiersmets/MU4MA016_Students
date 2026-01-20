CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -std=c11

TARGET  = tp4.exe
OBJS    = main.o priority_queue.o avl_tree.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

main.o: main.c priority_queue.h avl_tree.h
	$(CC) $(CFLAGS) -c main.c

priority_queue.o: priority_queue.c priority_queue.h
	$(CC) $(CFLAGS) -c priority_queue.c

avl_tree.o: avl_tree.c avl_tree.h
	$(CC) $(CFLAGS) -c avl_tree.c

clean:
	rm -f $(OBJS) $(TARGET)
