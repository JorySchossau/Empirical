# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bocajnotnef/git/Empirical/third-party/doxygen

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bocajnotnef/git/Empirical/third-party/doxygen/build

# Include any dependencies generated for this target.
include libmd5/CMakeFiles/md5.dir/depend.make

# Include the progress variables for this target.
include libmd5/CMakeFiles/md5.dir/progress.make

# Include the compile flags for this target's objects.
include libmd5/CMakeFiles/md5.dir/flags.make

libmd5/CMakeFiles/md5.dir/md5.c.o: libmd5/CMakeFiles/md5.dir/flags.make
libmd5/CMakeFiles/md5.dir/md5.c.o: ../libmd5/md5.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/bocajnotnef/git/Empirical/third-party/doxygen/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object libmd5/CMakeFiles/md5.dir/md5.c.o"
	cd /home/bocajnotnef/git/Empirical/third-party/doxygen/build/libmd5 && /usr/lib/ccache/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/md5.dir/md5.c.o   -c /home/bocajnotnef/git/Empirical/third-party/doxygen/libmd5/md5.c

libmd5/CMakeFiles/md5.dir/md5.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/md5.dir/md5.c.i"
	cd /home/bocajnotnef/git/Empirical/third-party/doxygen/build/libmd5 && /usr/lib/ccache/cc  $(C_DEFINES) $(C_FLAGS) -E /home/bocajnotnef/git/Empirical/third-party/doxygen/libmd5/md5.c > CMakeFiles/md5.dir/md5.c.i

libmd5/CMakeFiles/md5.dir/md5.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/md5.dir/md5.c.s"
	cd /home/bocajnotnef/git/Empirical/third-party/doxygen/build/libmd5 && /usr/lib/ccache/cc  $(C_DEFINES) $(C_FLAGS) -S /home/bocajnotnef/git/Empirical/third-party/doxygen/libmd5/md5.c -o CMakeFiles/md5.dir/md5.c.s

libmd5/CMakeFiles/md5.dir/md5.c.o.requires:
.PHONY : libmd5/CMakeFiles/md5.dir/md5.c.o.requires

libmd5/CMakeFiles/md5.dir/md5.c.o.provides: libmd5/CMakeFiles/md5.dir/md5.c.o.requires
	$(MAKE) -f libmd5/CMakeFiles/md5.dir/build.make libmd5/CMakeFiles/md5.dir/md5.c.o.provides.build
.PHONY : libmd5/CMakeFiles/md5.dir/md5.c.o.provides

libmd5/CMakeFiles/md5.dir/md5.c.o.provides.build: libmd5/CMakeFiles/md5.dir/md5.c.o

# Object files for target md5
md5_OBJECTS = \
"CMakeFiles/md5.dir/md5.c.o"

# External object files for target md5
md5_EXTERNAL_OBJECTS =

lib/libmd5.a: libmd5/CMakeFiles/md5.dir/md5.c.o
lib/libmd5.a: libmd5/CMakeFiles/md5.dir/build.make
lib/libmd5.a: libmd5/CMakeFiles/md5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library ../lib/libmd5.a"
	cd /home/bocajnotnef/git/Empirical/third-party/doxygen/build/libmd5 && $(CMAKE_COMMAND) -P CMakeFiles/md5.dir/cmake_clean_target.cmake
	cd /home/bocajnotnef/git/Empirical/third-party/doxygen/build/libmd5 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/md5.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libmd5/CMakeFiles/md5.dir/build: lib/libmd5.a
.PHONY : libmd5/CMakeFiles/md5.dir/build

libmd5/CMakeFiles/md5.dir/requires: libmd5/CMakeFiles/md5.dir/md5.c.o.requires
.PHONY : libmd5/CMakeFiles/md5.dir/requires

libmd5/CMakeFiles/md5.dir/clean:
	cd /home/bocajnotnef/git/Empirical/third-party/doxygen/build/libmd5 && $(CMAKE_COMMAND) -P CMakeFiles/md5.dir/cmake_clean.cmake
.PHONY : libmd5/CMakeFiles/md5.dir/clean

libmd5/CMakeFiles/md5.dir/depend:
	cd /home/bocajnotnef/git/Empirical/third-party/doxygen/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bocajnotnef/git/Empirical/third-party/doxygen /home/bocajnotnef/git/Empirical/third-party/doxygen/libmd5 /home/bocajnotnef/git/Empirical/third-party/doxygen/build /home/bocajnotnef/git/Empirical/third-party/doxygen/build/libmd5 /home/bocajnotnef/git/Empirical/third-party/doxygen/build/libmd5/CMakeFiles/md5.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libmd5/CMakeFiles/md5.dir/depend
