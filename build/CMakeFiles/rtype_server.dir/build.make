# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /home/e/Documents/tek3/github/t

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/e/Documents/tek3/github/t/build

# Include any dependencies generated for this target.
include CMakeFiles/rtype_server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/rtype_server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/rtype_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rtype_server.dir/flags.make

CMakeFiles/rtype_server.dir/src/server.cpp.o: CMakeFiles/rtype_server.dir/flags.make
CMakeFiles/rtype_server.dir/src/server.cpp.o: /home/e/Documents/tek3/github/t/src/server.cpp
CMakeFiles/rtype_server.dir/src/server.cpp.o: CMakeFiles/rtype_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/e/Documents/tek3/github/t/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rtype_server.dir/src/server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rtype_server.dir/src/server.cpp.o -MF CMakeFiles/rtype_server.dir/src/server.cpp.o.d -o CMakeFiles/rtype_server.dir/src/server.cpp.o -c /home/e/Documents/tek3/github/t/src/server.cpp

CMakeFiles/rtype_server.dir/src/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rtype_server.dir/src/server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/e/Documents/tek3/github/t/src/server.cpp > CMakeFiles/rtype_server.dir/src/server.cpp.i

CMakeFiles/rtype_server.dir/src/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rtype_server.dir/src/server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/e/Documents/tek3/github/t/src/server.cpp -o CMakeFiles/rtype_server.dir/src/server.cpp.s

# Object files for target rtype_server
rtype_server_OBJECTS = \
"CMakeFiles/rtype_server.dir/src/server.cpp.o"

# External object files for target rtype_server
rtype_server_EXTERNAL_OBJECTS =

rtype_server: CMakeFiles/rtype_server.dir/src/server.cpp.o
rtype_server: CMakeFiles/rtype_server.dir/build.make
rtype_server: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.74.0
rtype_server: CMakeFiles/rtype_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/e/Documents/tek3/github/t/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable rtype_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rtype_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rtype_server.dir/build: rtype_server
.PHONY : CMakeFiles/rtype_server.dir/build

CMakeFiles/rtype_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rtype_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rtype_server.dir/clean

CMakeFiles/rtype_server.dir/depend:
	cd /home/e/Documents/tek3/github/t/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/e/Documents/tek3/github/t /home/e/Documents/tek3/github/t /home/e/Documents/tek3/github/t/build /home/e/Documents/tek3/github/t/build /home/e/Documents/tek3/github/t/build/CMakeFiles/rtype_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rtype_server.dir/depend

