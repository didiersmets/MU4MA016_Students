# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/cmake/1417/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1417/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/janmarxen/MU4MA016_Students/JMarxen/TP1/EX2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/janmarxen/MU4MA016_Students/JMarxen/TP1/EX2/build

# Include any dependencies generated for this target.
include CMakeFiles/test_routines.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_routines.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_routines.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_routines.dir/flags.make

CMakeFiles/test_routines.dir/src/test_routines.c.o: CMakeFiles/test_routines.dir/flags.make
CMakeFiles/test_routines.dir/src/test_routines.c.o: /home/janmarxen/MU4MA016_Students/JMarxen/TP1/EX2/src/test_routines.c
CMakeFiles/test_routines.dir/src/test_routines.c.o: CMakeFiles/test_routines.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/janmarxen/MU4MA016_Students/JMarxen/TP1/EX2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/test_routines.dir/src/test_routines.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/test_routines.dir/src/test_routines.c.o -MF CMakeFiles/test_routines.dir/src/test_routines.c.o.d -o CMakeFiles/test_routines.dir/src/test_routines.c.o -c /home/janmarxen/MU4MA016_Students/JMarxen/TP1/EX2/src/test_routines.c

CMakeFiles/test_routines.dir/src/test_routines.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/test_routines.dir/src/test_routines.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/janmarxen/MU4MA016_Students/JMarxen/TP1/EX2/src/test_routines.c > CMakeFiles/test_routines.dir/src/test_routines.c.i

CMakeFiles/test_routines.dir/src/test_routines.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/test_routines.dir/src/test_routines.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/janmarxen/MU4MA016_Students/JMarxen/TP1/EX2/src/test_routines.c -o CMakeFiles/test_routines.dir/src/test_routines.c.s

CMakeFiles/test_routines.dir/src/sorting.c.o: CMakeFiles/test_routines.dir/flags.make
CMakeFiles/test_routines.dir/src/sorting.c.o: /home/janmarxen/MU4MA016_Students/JMarxen/TP1/EX2/src/sorting.c
CMakeFiles/test_routines.dir/src/sorting.c.o: CMakeFiles/test_routines.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/janmarxen/MU4MA016_Students/JMarxen/TP1/EX2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/test_routines.dir/src/sorting.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/test_routines.dir/src/sorting.c.o -MF CMakeFiles/test_routines.dir/src/sorting.c.o.d -o CMakeFiles/test_routines.dir/src/sorting.c.o -c /home/janmarxen/MU4MA016_Students/JMarxen/TP1/EX2/src/sorting.c

CMakeFiles/test_routines.dir/src/sorting.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/test_routines.dir/src/sorting.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/janmarxen/MU4MA016_Students/JMarxen/TP1/EX2/src/sorting.c > CMakeFiles/test_routines.dir/src/sorting.c.i

CMakeFiles/test_routines.dir/src/sorting.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/test_routines.dir/src/sorting.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/janmarxen/MU4MA016_Students/JMarxen/TP1/EX2/src/sorting.c -o CMakeFiles/test_routines.dir/src/sorting.c.s

# Object files for target test_routines
test_routines_OBJECTS = \
"CMakeFiles/test_routines.dir/src/test_routines.c.o" \
"CMakeFiles/test_routines.dir/src/sorting.c.o"

# External object files for target test_routines
test_routines_EXTERNAL_OBJECTS =

test_routines: CMakeFiles/test_routines.dir/src/test_routines.c.o
test_routines: CMakeFiles/test_routines.dir/src/sorting.c.o
test_routines: CMakeFiles/test_routines.dir/build.make
test_routines: CMakeFiles/test_routines.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/janmarxen/MU4MA016_Students/JMarxen/TP1/EX2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable test_routines"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_routines.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_routines.dir/build: test_routines
.PHONY : CMakeFiles/test_routines.dir/build

CMakeFiles/test_routines.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_routines.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_routines.dir/clean

CMakeFiles/test_routines.dir/depend:
	cd /home/janmarxen/MU4MA016_Students/JMarxen/TP1/EX2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/janmarxen/MU4MA016_Students/JMarxen/TP1/EX2 /home/janmarxen/MU4MA016_Students/JMarxen/TP1/EX2 /home/janmarxen/MU4MA016_Students/JMarxen/TP1/EX2/build /home/janmarxen/MU4MA016_Students/JMarxen/TP1/EX2/build /home/janmarxen/MU4MA016_Students/JMarxen/TP1/EX2/build/CMakeFiles/test_routines.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/test_routines.dir/depend

