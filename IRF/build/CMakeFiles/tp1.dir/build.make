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
CMAKE_SOURCE_DIR = /users/home/21400676/MU4MA016_Students/IRF

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /users/home/21400676/MU4MA016_Students/IRF/build

# Include any dependencies generated for this target.
include CMakeFiles/tp1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/tp1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/tp1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tp1.dir/flags.make

CMakeFiles/tp1.dir/src/test_queue.c.o: CMakeFiles/tp1.dir/flags.make
CMakeFiles/tp1.dir/src/test_queue.c.o: ../src/test_queue.c
CMakeFiles/tp1.dir/src/test_queue.c.o: CMakeFiles/tp1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/users/home/21400676/MU4MA016_Students/IRF/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/tp1.dir/src/test_queue.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/tp1.dir/src/test_queue.c.o -MF CMakeFiles/tp1.dir/src/test_queue.c.o.d -o CMakeFiles/tp1.dir/src/test_queue.c.o -c /users/home/21400676/MU4MA016_Students/IRF/src/test_queue.c

CMakeFiles/tp1.dir/src/test_queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tp1.dir/src/test_queue.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /users/home/21400676/MU4MA016_Students/IRF/src/test_queue.c > CMakeFiles/tp1.dir/src/test_queue.c.i

CMakeFiles/tp1.dir/src/test_queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tp1.dir/src/test_queue.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /users/home/21400676/MU4MA016_Students/IRF/src/test_queue.c -o CMakeFiles/tp1.dir/src/test_queue.c.s

CMakeFiles/tp1.dir/src/circular_buffer_queue.c.o: CMakeFiles/tp1.dir/flags.make
CMakeFiles/tp1.dir/src/circular_buffer_queue.c.o: ../src/circular_buffer_queue.c
CMakeFiles/tp1.dir/src/circular_buffer_queue.c.o: CMakeFiles/tp1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/users/home/21400676/MU4MA016_Students/IRF/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/tp1.dir/src/circular_buffer_queue.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/tp1.dir/src/circular_buffer_queue.c.o -MF CMakeFiles/tp1.dir/src/circular_buffer_queue.c.o.d -o CMakeFiles/tp1.dir/src/circular_buffer_queue.c.o -c /users/home/21400676/MU4MA016_Students/IRF/src/circular_buffer_queue.c

CMakeFiles/tp1.dir/src/circular_buffer_queue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tp1.dir/src/circular_buffer_queue.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /users/home/21400676/MU4MA016_Students/IRF/src/circular_buffer_queue.c > CMakeFiles/tp1.dir/src/circular_buffer_queue.c.i

CMakeFiles/tp1.dir/src/circular_buffer_queue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tp1.dir/src/circular_buffer_queue.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /users/home/21400676/MU4MA016_Students/IRF/src/circular_buffer_queue.c -o CMakeFiles/tp1.dir/src/circular_buffer_queue.c.s

# Object files for target tp1
tp1_OBJECTS = \
"CMakeFiles/tp1.dir/src/test_queue.c.o" \
"CMakeFiles/tp1.dir/src/circular_buffer_queue.c.o"

# External object files for target tp1
tp1_EXTERNAL_OBJECTS =

tp1: CMakeFiles/tp1.dir/src/test_queue.c.o
tp1: CMakeFiles/tp1.dir/src/circular_buffer_queue.c.o
tp1: CMakeFiles/tp1.dir/build.make
tp1: CMakeFiles/tp1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/users/home/21400676/MU4MA016_Students/IRF/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable tp1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tp1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tp1.dir/build: tp1
.PHONY : CMakeFiles/tp1.dir/build

CMakeFiles/tp1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tp1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tp1.dir/clean

CMakeFiles/tp1.dir/depend:
	cd /users/home/21400676/MU4MA016_Students/IRF/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /users/home/21400676/MU4MA016_Students/IRF /users/home/21400676/MU4MA016_Students/IRF /users/home/21400676/MU4MA016_Students/IRF/build /users/home/21400676/MU4MA016_Students/IRF/build /users/home/21400676/MU4MA016_Students/IRF/build/CMakeFiles/tp1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tp1.dir/depend
