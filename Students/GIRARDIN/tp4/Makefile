TARGET_NAME	:= tp4
TARGET := $(TARGET_NAME)


CFLAGS   += -O2 -Wall

# Source directories
SRC_DIRS := src

# Create build directories
$(shell mkdir -p build)

# Collect all source files
SOURCES_C := $(wildcard $(addsuffix /*.c, $(SRC_DIRS)))

# Generate object file paths
OBJECTS := $(patsubst src/%.c,build/%.o,$(SOURCES_C))

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