TARGET_NAME	:= tp3
TARGET := $(TARGET_NAME)

# INCFLAGS += -Iinclude -Isrc
# LIBS += #-Wl,-Bstatic -lSDL -lSDLmain -Wl,-Bdynamic -lpthread
# fpic := #-fPIC

CFLAGS   += -O2 -Wall #$(fpic) $(INCFLAGS) -g
#CXXFLAGS += -Wall $(fpic) $(INCFLAGS) -g

# Source directories
SRC_DIRS := src

# Create build directories
$(shell mkdir -p build)

# Collect all source files
SOURCES_C := $(wildcard $(addsuffix /*.c, $(SRC_DIRS)))
#SOURCES_CXX := $(wildcard $(addsuffix /*.cpp, $(SRC_DIRS)))

# Generate object file paths
OBJECTS := $(patsubst src/%.c,build/%.o,$(SOURCES_C)) #$(patsubst src/%.cpp,build/%.o,$(SOURCES_CXX))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LIBS)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean




# Target : tp3

# tp3 : tp3.o hashtable.o mesh.o mesh_io.o hash_tables.o
# 	gcc -O3 -o tp3 hashtable.o tp3.o mesh.o mesh_io.o hash_tables.o

# tp3.o: ./src/tp3.c ./include/hashtable.h ./include/mesh.h ./include/mesh_io.h
# 	gcc -c -O3 ./src/tp3.c

# hashtable.o: ./src/hashtable.c ./include/mesh.h ./include/hash_tables.h
# 	gcc -c -O3 ./src/hashtable.c

# mesh.o: ./src/mesh.c
# 	gcc -c -O3 ./src/mesh.c

# mesh_io.o: ./src/mesh_io.c ./include/mesh.h
# 	gcc -c -O3 ./src/mesh_io.c

# hash_tables.o : ./src/hash_tables.c
# 	gcc -c -O3 ./src/hash_tables.c

# .PHONY: clean
# clean:
# 	rm -f .o tp3
