# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.29.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.29.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sumeetsingh/Documents/sandbox

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sumeetsingh/Documents/sandbox/build

# Include any dependencies generated for this target.
include CMakeFiles/sandbox.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/sandbox.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/sandbox.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sandbox.dir/flags.make

CMakeFiles/sandbox.dir/main.cpp.o: CMakeFiles/sandbox.dir/flags.make
CMakeFiles/sandbox.dir/main.cpp.o: /Users/sumeetsingh/Documents/sandbox/main.cpp
CMakeFiles/sandbox.dir/main.cpp.o: CMakeFiles/sandbox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/sumeetsingh/Documents/sandbox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sandbox.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sandbox.dir/main.cpp.o -MF CMakeFiles/sandbox.dir/main.cpp.o.d -o CMakeFiles/sandbox.dir/main.cpp.o -c /Users/sumeetsingh/Documents/sandbox/main.cpp

CMakeFiles/sandbox.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sandbox.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sumeetsingh/Documents/sandbox/main.cpp > CMakeFiles/sandbox.dir/main.cpp.i

CMakeFiles/sandbox.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sandbox.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sumeetsingh/Documents/sandbox/main.cpp -o CMakeFiles/sandbox.dir/main.cpp.s

CMakeFiles/sandbox.dir/src/WebserverClient.cpp.o: CMakeFiles/sandbox.dir/flags.make
CMakeFiles/sandbox.dir/src/WebserverClient.cpp.o: /Users/sumeetsingh/Documents/sandbox/src/WebserverClient.cpp
CMakeFiles/sandbox.dir/src/WebserverClient.cpp.o: CMakeFiles/sandbox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/sumeetsingh/Documents/sandbox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sandbox.dir/src/WebserverClient.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sandbox.dir/src/WebserverClient.cpp.o -MF CMakeFiles/sandbox.dir/src/WebserverClient.cpp.o.d -o CMakeFiles/sandbox.dir/src/WebserverClient.cpp.o -c /Users/sumeetsingh/Documents/sandbox/src/WebserverClient.cpp

CMakeFiles/sandbox.dir/src/WebserverClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sandbox.dir/src/WebserverClient.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/sumeetsingh/Documents/sandbox/src/WebserverClient.cpp > CMakeFiles/sandbox.dir/src/WebserverClient.cpp.i

CMakeFiles/sandbox.dir/src/WebserverClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sandbox.dir/src/WebserverClient.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/sumeetsingh/Documents/sandbox/src/WebserverClient.cpp -o CMakeFiles/sandbox.dir/src/WebserverClient.cpp.s

# Object files for target sandbox
sandbox_OBJECTS = \
"CMakeFiles/sandbox.dir/main.cpp.o" \
"CMakeFiles/sandbox.dir/src/WebserverClient.cpp.o"

# External object files for target sandbox
sandbox_EXTERNAL_OBJECTS =

/Users/sumeetsingh/Documents/sandbox/sandbox: CMakeFiles/sandbox.dir/main.cpp.o
/Users/sumeetsingh/Documents/sandbox/sandbox: CMakeFiles/sandbox.dir/src/WebserverClient.cpp.o
/Users/sumeetsingh/Documents/sandbox/sandbox: CMakeFiles/sandbox.dir/build.make
/Users/sumeetsingh/Documents/sandbox/sandbox: /opt/homebrew/Cellar/sdl2/2.30.2/lib/libSDL2main.a
/Users/sumeetsingh/Documents/sandbox/sandbox: /opt/homebrew/Cellar/sdl2/2.30.2/lib/libSDL2.dylib
/Users/sumeetsingh/Documents/sandbox/sandbox: /opt/homebrew/Cellar/sdl2_image/2.8.2_1/lib/libSDL2_image.dylib
/Users/sumeetsingh/Documents/sandbox/sandbox: /opt/homebrew/Cellar/sdl2_ttf/2.22.0/lib/libSDL2_ttf.dylib
/Users/sumeetsingh/Documents/sandbox/sandbox: /opt/homebrew/Cellar/sdl2_mixer/2.8.0/lib/libSDL2_mixer.dylib
/Users/sumeetsingh/Documents/sandbox/sandbox: CMakeFiles/sandbox.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/sumeetsingh/Documents/sandbox/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable /Users/sumeetsingh/Documents/sandbox/sandbox"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sandbox.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sandbox.dir/build: /Users/sumeetsingh/Documents/sandbox/sandbox
.PHONY : CMakeFiles/sandbox.dir/build

CMakeFiles/sandbox.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sandbox.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sandbox.dir/clean

CMakeFiles/sandbox.dir/depend:
	cd /Users/sumeetsingh/Documents/sandbox/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sumeetsingh/Documents/sandbox /Users/sumeetsingh/Documents/sandbox /Users/sumeetsingh/Documents/sandbox/build /Users/sumeetsingh/Documents/sandbox/build /Users/sumeetsingh/Documents/sandbox/build/CMakeFiles/sandbox.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/sandbox.dir/depend

