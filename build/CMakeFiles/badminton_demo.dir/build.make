# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Mac/Downloads/Coding/HCMUS/OOP/Project/Badminton-Rental-System

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Mac/Downloads/Coding/HCMUS/OOP/Project/Badminton-Rental-System/build

# Include any dependencies generated for this target.
include CMakeFiles/badminton_demo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/badminton_demo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/badminton_demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/badminton_demo.dir/flags.make

CMakeFiles/badminton_demo.dir/codegen:
.PHONY : CMakeFiles/badminton_demo.dir/codegen

CMakeFiles/badminton_demo.dir/src/demo.cpp.o: CMakeFiles/badminton_demo.dir/flags.make
CMakeFiles/badminton_demo.dir/src/demo.cpp.o: /Users/Mac/Downloads/Coding/HCMUS/OOP/Project/Badminton-Rental-System/src/demo.cpp
CMakeFiles/badminton_demo.dir/src/demo.cpp.o: CMakeFiles/badminton_demo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/Mac/Downloads/Coding/HCMUS/OOP/Project/Badminton-Rental-System/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/badminton_demo.dir/src/demo.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/badminton_demo.dir/src/demo.cpp.o -MF CMakeFiles/badminton_demo.dir/src/demo.cpp.o.d -o CMakeFiles/badminton_demo.dir/src/demo.cpp.o -c /Users/Mac/Downloads/Coding/HCMUS/OOP/Project/Badminton-Rental-System/src/demo.cpp

CMakeFiles/badminton_demo.dir/src/demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/badminton_demo.dir/src/demo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Mac/Downloads/Coding/HCMUS/OOP/Project/Badminton-Rental-System/src/demo.cpp > CMakeFiles/badminton_demo.dir/src/demo.cpp.i

CMakeFiles/badminton_demo.dir/src/demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/badminton_demo.dir/src/demo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Mac/Downloads/Coding/HCMUS/OOP/Project/Badminton-Rental-System/src/demo.cpp -o CMakeFiles/badminton_demo.dir/src/demo.cpp.s

# Object files for target badminton_demo
badminton_demo_OBJECTS = \
"CMakeFiles/badminton_demo.dir/src/demo.cpp.o"

# External object files for target badminton_demo
badminton_demo_EXTERNAL_OBJECTS =

badminton_demo: CMakeFiles/badminton_demo.dir/src/demo.cpp.o
badminton_demo: CMakeFiles/badminton_demo.dir/build.make
badminton_demo: CMakeFiles/badminton_demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/Mac/Downloads/Coding/HCMUS/OOP/Project/Badminton-Rental-System/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable badminton_demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/badminton_demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/badminton_demo.dir/build: badminton_demo
.PHONY : CMakeFiles/badminton_demo.dir/build

CMakeFiles/badminton_demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/badminton_demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/badminton_demo.dir/clean

CMakeFiles/badminton_demo.dir/depend:
	cd /Users/Mac/Downloads/Coding/HCMUS/OOP/Project/Badminton-Rental-System/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Mac/Downloads/Coding/HCMUS/OOP/Project/Badminton-Rental-System /Users/Mac/Downloads/Coding/HCMUS/OOP/Project/Badminton-Rental-System /Users/Mac/Downloads/Coding/HCMUS/OOP/Project/Badminton-Rental-System/build /Users/Mac/Downloads/Coding/HCMUS/OOP/Project/Badminton-Rental-System/build /Users/Mac/Downloads/Coding/HCMUS/OOP/Project/Badminton-Rental-System/build/CMakeFiles/badminton_demo.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/badminton_demo.dir/depend

