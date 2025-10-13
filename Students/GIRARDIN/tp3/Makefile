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