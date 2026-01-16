CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -O2 -Iinclude
LDFLAGS =

SRC = tp3.c \
      src/mesh.c \
	  src/mesh_io.c \
      src/hash_tables.c \
      src/mesh_adj.c
	  

OBJ = $(SRC:.c=.o)

.PHONY: all clean

all: tp3

tp3: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) tp3
 