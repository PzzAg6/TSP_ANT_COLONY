# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/pangyusheng/Desktop/PROG/C++/TSP_AC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/pangyusheng/Desktop/PROG/C++/TSP_AC/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TSP_AC.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TSP_AC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TSP_AC.dir/flags.make

CMakeFiles/TSP_AC.dir/main.cpp.o: CMakeFiles/TSP_AC.dir/flags.make
CMakeFiles/TSP_AC.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/pangyusheng/Desktop/PROG/C++/TSP_AC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TSP_AC.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TSP_AC.dir/main.cpp.o -c /Users/pangyusheng/Desktop/PROG/C++/TSP_AC/main.cpp

CMakeFiles/TSP_AC.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TSP_AC.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/pangyusheng/Desktop/PROG/C++/TSP_AC/main.cpp > CMakeFiles/TSP_AC.dir/main.cpp.i

CMakeFiles/TSP_AC.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TSP_AC.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/pangyusheng/Desktop/PROG/C++/TSP_AC/main.cpp -o CMakeFiles/TSP_AC.dir/main.cpp.s

# Object files for target TSP_AC
TSP_AC_OBJECTS = \
"CMakeFiles/TSP_AC.dir/main.cpp.o"

# External object files for target TSP_AC
TSP_AC_EXTERNAL_OBJECTS =

TSP_AC: CMakeFiles/TSP_AC.dir/main.cpp.o
TSP_AC: CMakeFiles/TSP_AC.dir/build.make
TSP_AC: CMakeFiles/TSP_AC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/pangyusheng/Desktop/PROG/C++/TSP_AC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TSP_AC"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TSP_AC.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TSP_AC.dir/build: TSP_AC

.PHONY : CMakeFiles/TSP_AC.dir/build

CMakeFiles/TSP_AC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TSP_AC.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TSP_AC.dir/clean

CMakeFiles/TSP_AC.dir/depend:
	cd /Users/pangyusheng/Desktop/PROG/C++/TSP_AC/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pangyusheng/Desktop/PROG/C++/TSP_AC /Users/pangyusheng/Desktop/PROG/C++/TSP_AC /Users/pangyusheng/Desktop/PROG/C++/TSP_AC/cmake-build-debug /Users/pangyusheng/Desktop/PROG/C++/TSP_AC/cmake-build-debug /Users/pangyusheng/Desktop/PROG/C++/TSP_AC/cmake-build-debug/CMakeFiles/TSP_AC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TSP_AC.dir/depend

