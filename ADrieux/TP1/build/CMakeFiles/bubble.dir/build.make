# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /users/home/28624202/MU4MA016_Students/ADrieux/TP1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /users/home/28624202/MU4MA016_Students/ADrieux/TP1/build

# Include any dependencies generated for this target.
include CMakeFiles/bubble.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/bubble.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bubble.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bubble.dir/flags.make

CMakeFiles/bubble.dir/bubble_sort.c.o: CMakeFiles/bubble.dir/flags.make
CMakeFiles/bubble.dir/bubble_sort.c.o: ../bubble_sort.c
CMakeFiles/bubble.dir/bubble_sort.c.o: CMakeFiles/bubble.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/users/home/28624202/MU4MA016_Students/ADrieux/TP1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/bubble.dir/bubble_sort.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/bubble.dir/bubble_sort.c.o -MF CMakeFiles/bubble.dir/bubble_sort.c.o.d -o CMakeFiles/bubble.dir/bubble_sort.c.o -c /users/home/28624202/MU4MA016_Students/ADrieux/TP1/bubble_sort.c

CMakeFiles/bubble.dir/bubble_sort.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bubble.dir/bubble_sort.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /users/home/28624202/MU4MA016_Students/ADrieux/TP1/bubble_sort.c > CMakeFiles/bubble.dir/bubble_sort.c.i

CMakeFiles/bubble.dir/bubble_sort.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bubble.dir/bubble_sort.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /users/home/28624202/MU4MA016_Students/ADrieux/TP1/bubble_sort.c -o CMakeFiles/bubble.dir/bubble_sort.c.s

# Object files for target bubble
bubble_OBJECTS = \
"CMakeFiles/bubble.dir/bubble_sort.c.o"

# External object files for target bubble
bubble_EXTERNAL_OBJECTS =

bubble: CMakeFiles/bubble.dir/bubble_sort.c.o
bubble: CMakeFiles/bubble.dir/build.make
bubble: CMakeFiles/bubble.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/users/home/28624202/MU4MA016_Students/ADrieux/TP1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bubble"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bubble.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bubble.dir/build: bubble
.PHONY : CMakeFiles/bubble.dir/build

CMakeFiles/bubble.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bubble.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bubble.dir/clean

CMakeFiles/bubble.dir/depend:
	cd /users/home/28624202/MU4MA016_Students/ADrieux/TP1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /users/home/28624202/MU4MA016_Students/ADrieux/TP1 /users/home/28624202/MU4MA016_Students/ADrieux/TP1 /users/home/28624202/MU4MA016_Students/ADrieux/TP1/build /users/home/28624202/MU4MA016_Students/ADrieux/TP1/build /users/home/28624202/MU4MA016_Students/ADrieux/TP1/build/CMakeFiles/bubble.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bubble.dir/depend

