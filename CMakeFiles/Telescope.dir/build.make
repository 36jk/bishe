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
CMAKE_SOURCE_DIR = /home/user/bishe

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/bishe

# Include any dependencies generated for this target.
include CMakeFiles/Telescope.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Telescope.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Telescope.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Telescope.dir/flags.make

CMakeFiles/Telescope.dir/Telescope.cpp.o: CMakeFiles/Telescope.dir/flags.make
CMakeFiles/Telescope.dir/Telescope.cpp.o: Telescope.cpp
CMakeFiles/Telescope.dir/Telescope.cpp.o: CMakeFiles/Telescope.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/bishe/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Telescope.dir/Telescope.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Telescope.dir/Telescope.cpp.o -MF CMakeFiles/Telescope.dir/Telescope.cpp.o.d -o CMakeFiles/Telescope.dir/Telescope.cpp.o -c /home/user/bishe/Telescope.cpp

CMakeFiles/Telescope.dir/Telescope.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Telescope.dir/Telescope.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/bishe/Telescope.cpp > CMakeFiles/Telescope.dir/Telescope.cpp.i

CMakeFiles/Telescope.dir/Telescope.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Telescope.dir/Telescope.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/bishe/Telescope.cpp -o CMakeFiles/Telescope.dir/Telescope.cpp.s

# Object files for target Telescope
Telescope_OBJECTS = \
"CMakeFiles/Telescope.dir/Telescope.cpp.o"

# External object files for target Telescope
Telescope_EXTERNAL_OBJECTS =

Telescope: CMakeFiles/Telescope.dir/Telescope.cpp.o
Telescope: CMakeFiles/Telescope.dir/build.make
Telescope: /usr/lib/aarch64-linux-gnu/libindidriver.so
Telescope: /usr/lib/aarch64-linux-gnu/libindiAlignmentDriver.so
Telescope: /usr/lib/aarch64-linux-gnu/libnova.so
Telescope: /usr/lib/aarch64-linux-gnu/libgsl.so
Telescope: /usr/lib/aarch64-linux-gnu/libgslcblas.so
Telescope: CMakeFiles/Telescope.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/bishe/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Telescope"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Telescope.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Telescope.dir/build: Telescope
.PHONY : CMakeFiles/Telescope.dir/build

CMakeFiles/Telescope.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Telescope.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Telescope.dir/clean

CMakeFiles/Telescope.dir/depend:
	cd /home/user/bishe && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/bishe /home/user/bishe /home/user/bishe /home/user/bishe /home/user/bishe/CMakeFiles/Telescope.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Telescope.dir/depend

