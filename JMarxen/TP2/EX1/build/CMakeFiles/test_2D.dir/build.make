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
CMAKE_SOURCE_DIR = /home/janmarxen/MU4MA016_Students/JMarxen/TP2/EX1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/janmarxen/MU4MA016_Students/JMarxen/TP2/EX1/build

# Include any dependencies generated for this target.
include CMakeFiles/test_2D.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_2D.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_2D.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_2D.dir/flags.make

CMakeFiles/test_2D.dir/src/test_2D.c.o: CMakeFiles/test_2D.dir/flags.make
CMakeFiles/test_2D.dir/src/test_2D.c.o: /home/janmarxen/MU4MA016_Students/JMarxen/TP2/EX1/src/test_2D.c
CMakeFiles/test_2D.dir/src/test_2D.c.o: CMakeFiles/test_2D.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/janmarxen/MU4MA016_Students/JMarxen/TP2/EX1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/test_2D.dir/src/test_2D.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/test_2D.dir/src/test_2D.c.o -MF CMakeFiles/test_2D.dir/src/test_2D.c.o.d -o CMakeFiles/test_2D.dir/src/test_2D.c.o -c /home/janmarxen/MU4MA016_Students/JMarxen/TP2/EX1/src/test_2D.c

CMakeFiles/test_2D.dir/src/test_2D.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/test_2D.dir/src/test_2D.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/janmarxen/MU4MA016_Students/JMarxen/TP2/EX1/src/test_2D.c > CMakeFiles/test_2D.dir/src/test_2D.c.i

CMakeFiles/test_2D.dir/src/test_2D.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/test_2D.dir/src/test_2D.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/janmarxen/MU4MA016_Students/JMarxen/TP2/EX1/src/test_2D.c -o CMakeFiles/test_2D.dir/src/test_2D.c.s

CMakeFiles/test_2D.dir/src/mesh_2D.c.o: CMakeFiles/test_2D.dir/flags.make
CMakeFiles/test_2D.dir/src/mesh_2D.c.o: /home/janmarxen/MU4MA016_Students/JMarxen/TP2/EX1/src/mesh_2D.c
CMakeFiles/test_2D.dir/src/mesh_2D.c.o: CMakeFiles/test_2D.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/janmarxen/MU4MA016_Students/JMarxen/TP2/EX1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/test_2D.dir/src/mesh_2D.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/test_2D.dir/src/mesh_2D.c.o -MF CMakeFiles/test_2D.dir/src/mesh_2D.c.o.d -o CMakeFiles/test_2D.dir/src/mesh_2D.c.o -c /home/janmarxen/MU4MA016_Students/JMarxen/TP2/EX1/src/mesh_2D.c

CMakeFiles/test_2D.dir/src/mesh_2D.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/test_2D.dir/src/mesh_2D.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/janmarxen/MU4MA016_Students/JMarxen/TP2/EX1/src/mesh_2D.c > CMakeFiles/test_2D.dir/src/mesh_2D.c.i

CMakeFiles/test_2D.dir/src/mesh_2D.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/test_2D.dir/src/mesh_2D.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/janmarxen/MU4MA016_Students/JMarxen/TP2/EX1/src/mesh_2D.c -o CMakeFiles/test_2D.dir/src/mesh_2D.c.s

# Object files for target test_2D
test_2D_OBJECTS = \
"CMakeFiles/test_2D.dir/src/test_2D.c.o" \
"CMakeFiles/test_2D.dir/src/mesh_2D.c.o"

# External object files for target test_2D
test_2D_EXTERNAL_OBJECTS =

test_2D: CMakeFiles/test_2D.dir/src/test_2D.c.o
test_2D: CMakeFiles/test_2D.dir/src/mesh_2D.c.o
test_2D: CMakeFiles/test_2D.dir/build.make
test_2D: CMakeFiles/test_2D.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/janmarxen/MU4MA016_Students/JMarxen/TP2/EX1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable test_2D"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_2D.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_2D.dir/build: test_2D
.PHONY : CMakeFiles/test_2D.dir/build

CMakeFiles/test_2D.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_2D.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_2D.dir/clean

CMakeFiles/test_2D.dir/depend:
	cd /home/janmarxen/MU4MA016_Students/JMarxen/TP2/EX1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/janmarxen/MU4MA016_Students/JMarxen/TP2/EX1 /home/janmarxen/MU4MA016_Students/JMarxen/TP2/EX1 /home/janmarxen/MU4MA016_Students/JMarxen/TP2/EX1/build /home/janmarxen/MU4MA016_Students/JMarxen/TP2/EX1/build /home/janmarxen/MU4MA016_Students/JMarxen/TP2/EX1/build/CMakeFiles/test_2D.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/test_2D.dir/depend

