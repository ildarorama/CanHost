# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.10.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.10.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/i386/CLionProjects/CanHost/scripts

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/i386/CLionProjects/CanHost/scripts

# Include any dependencies generated for this target.
include CMakeFiles/testscript.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testscript.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testscript.dir/flags.make

CMakeFiles/testscript.dir/testscript.cpp.o: CMakeFiles/testscript.dir/flags.make
CMakeFiles/testscript.dir/testscript.cpp.o: testscript.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/i386/CLionProjects/CanHost/scripts/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testscript.dir/testscript.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testscript.dir/testscript.cpp.o -c /Users/i386/CLionProjects/CanHost/scripts/testscript.cpp

CMakeFiles/testscript.dir/testscript.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testscript.dir/testscript.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/i386/CLionProjects/CanHost/scripts/testscript.cpp > CMakeFiles/testscript.dir/testscript.cpp.i

CMakeFiles/testscript.dir/testscript.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testscript.dir/testscript.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/i386/CLionProjects/CanHost/scripts/testscript.cpp -o CMakeFiles/testscript.dir/testscript.cpp.s

CMakeFiles/testscript.dir/testscript.cpp.o.requires:

.PHONY : CMakeFiles/testscript.dir/testscript.cpp.o.requires

CMakeFiles/testscript.dir/testscript.cpp.o.provides: CMakeFiles/testscript.dir/testscript.cpp.o.requires
	$(MAKE) -f CMakeFiles/testscript.dir/build.make CMakeFiles/testscript.dir/testscript.cpp.o.provides.build
.PHONY : CMakeFiles/testscript.dir/testscript.cpp.o.provides

CMakeFiles/testscript.dir/testscript.cpp.o.provides.build: CMakeFiles/testscript.dir/testscript.cpp.o


# Object files for target testscript
testscript_OBJECTS = \
"CMakeFiles/testscript.dir/testscript.cpp.o"

# External object files for target testscript
testscript_EXTERNAL_OBJECTS =

libtestscript.dylib: CMakeFiles/testscript.dir/testscript.cpp.o
libtestscript.dylib: CMakeFiles/testscript.dir/build.make
libtestscript.dylib: ../objects/libCanHostObject.a
libtestscript.dylib: CMakeFiles/testscript.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/i386/CLionProjects/CanHost/scripts/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libtestscript.dylib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testscript.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testscript.dir/build: libtestscript.dylib

.PHONY : CMakeFiles/testscript.dir/build

CMakeFiles/testscript.dir/requires: CMakeFiles/testscript.dir/testscript.cpp.o.requires

.PHONY : CMakeFiles/testscript.dir/requires

CMakeFiles/testscript.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testscript.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testscript.dir/clean

CMakeFiles/testscript.dir/depend:
	cd /Users/i386/CLionProjects/CanHost/scripts && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/i386/CLionProjects/CanHost/scripts /Users/i386/CLionProjects/CanHost/scripts /Users/i386/CLionProjects/CanHost/scripts /Users/i386/CLionProjects/CanHost/scripts /Users/i386/CLionProjects/CanHost/scripts/CMakeFiles/testscript.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testscript.dir/depend
