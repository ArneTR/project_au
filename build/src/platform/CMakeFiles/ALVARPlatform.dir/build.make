# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/roboto/Downloads/alvar-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/roboto/Downloads/alvar-master/build

# Include any dependencies generated for this target.
include src/platform/CMakeFiles/ALVARPlatform.dir/depend.make

# Include the progress variables for this target.
include src/platform/CMakeFiles/ALVARPlatform.dir/progress.make

# Include the compile flags for this target's objects.
include src/platform/CMakeFiles/ALVARPlatform.dir/flags.make

src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory.cpp.o: src/platform/CMakeFiles/ALVARPlatform.dir/flags.make
src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory.cpp.o: ../src/platform/CaptureFactory.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/roboto/Downloads/alvar-master/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory.cpp.o"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ALVARPlatform.dir/CaptureFactory.cpp.o -c /home/roboto/Downloads/alvar-master/src/platform/CaptureFactory.cpp

src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ALVARPlatform.dir/CaptureFactory.cpp.i"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/roboto/Downloads/alvar-master/src/platform/CaptureFactory.cpp > CMakeFiles/ALVARPlatform.dir/CaptureFactory.cpp.i

src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ALVARPlatform.dir/CaptureFactory.cpp.s"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/roboto/Downloads/alvar-master/src/platform/CaptureFactory.cpp -o CMakeFiles/ALVARPlatform.dir/CaptureFactory.cpp.s

src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory.cpp.o.requires:
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory.cpp.o.requires

src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory.cpp.o.provides: src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory.cpp.o.requires
	$(MAKE) -f src/platform/CMakeFiles/ALVARPlatform.dir/build.make src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory.cpp.o.provides.build
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory.cpp.o.provides

src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory.cpp.o.provides.build: src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory.cpp.o

src/platform/CMakeFiles/ALVARPlatform.dir/CaptureDevice.cpp.o: src/platform/CMakeFiles/ALVARPlatform.dir/flags.make
src/platform/CMakeFiles/ALVARPlatform.dir/CaptureDevice.cpp.o: ../src/platform/CaptureDevice.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/roboto/Downloads/alvar-master/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/platform/CMakeFiles/ALVARPlatform.dir/CaptureDevice.cpp.o"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ALVARPlatform.dir/CaptureDevice.cpp.o -c /home/roboto/Downloads/alvar-master/src/platform/CaptureDevice.cpp

src/platform/CMakeFiles/ALVARPlatform.dir/CaptureDevice.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ALVARPlatform.dir/CaptureDevice.cpp.i"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/roboto/Downloads/alvar-master/src/platform/CaptureDevice.cpp > CMakeFiles/ALVARPlatform.dir/CaptureDevice.cpp.i

src/platform/CMakeFiles/ALVARPlatform.dir/CaptureDevice.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ALVARPlatform.dir/CaptureDevice.cpp.s"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/roboto/Downloads/alvar-master/src/platform/CaptureDevice.cpp -o CMakeFiles/ALVARPlatform.dir/CaptureDevice.cpp.s

src/platform/CMakeFiles/ALVARPlatform.dir/CaptureDevice.cpp.o.requires:
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/CaptureDevice.cpp.o.requires

src/platform/CMakeFiles/ALVARPlatform.dir/CaptureDevice.cpp.o.provides: src/platform/CMakeFiles/ALVARPlatform.dir/CaptureDevice.cpp.o.requires
	$(MAKE) -f src/platform/CMakeFiles/ALVARPlatform.dir/build.make src/platform/CMakeFiles/ALVARPlatform.dir/CaptureDevice.cpp.o.provides.build
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/CaptureDevice.cpp.o.provides

src/platform/CMakeFiles/ALVARPlatform.dir/CaptureDevice.cpp.o.provides.build: src/platform/CMakeFiles/ALVARPlatform.dir/CaptureDevice.cpp.o

src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator.cpp.o: src/platform/CMakeFiles/ALVARPlatform.dir/flags.make
src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator.cpp.o: ../src/platform/DirectoryIterator.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/roboto/Downloads/alvar-master/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator.cpp.o"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ALVARPlatform.dir/DirectoryIterator.cpp.o -c /home/roboto/Downloads/alvar-master/src/platform/DirectoryIterator.cpp

src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ALVARPlatform.dir/DirectoryIterator.cpp.i"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/roboto/Downloads/alvar-master/src/platform/DirectoryIterator.cpp > CMakeFiles/ALVARPlatform.dir/DirectoryIterator.cpp.i

src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ALVARPlatform.dir/DirectoryIterator.cpp.s"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/roboto/Downloads/alvar-master/src/platform/DirectoryIterator.cpp -o CMakeFiles/ALVARPlatform.dir/DirectoryIterator.cpp.s

src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator.cpp.o.requires:
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator.cpp.o.requires

src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator.cpp.o.provides: src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator.cpp.o.requires
	$(MAKE) -f src/platform/CMakeFiles/ALVARPlatform.dir/build.make src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator.cpp.o.provides.build
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator.cpp.o.provides

src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator.cpp.o.provides.build: src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator.cpp.o

src/platform/CMakeFiles/ALVARPlatform.dir/Mutex.cpp.o: src/platform/CMakeFiles/ALVARPlatform.dir/flags.make
src/platform/CMakeFiles/ALVARPlatform.dir/Mutex.cpp.o: ../src/platform/Mutex.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/roboto/Downloads/alvar-master/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/platform/CMakeFiles/ALVARPlatform.dir/Mutex.cpp.o"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ALVARPlatform.dir/Mutex.cpp.o -c /home/roboto/Downloads/alvar-master/src/platform/Mutex.cpp

src/platform/CMakeFiles/ALVARPlatform.dir/Mutex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ALVARPlatform.dir/Mutex.cpp.i"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/roboto/Downloads/alvar-master/src/platform/Mutex.cpp > CMakeFiles/ALVARPlatform.dir/Mutex.cpp.i

src/platform/CMakeFiles/ALVARPlatform.dir/Mutex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ALVARPlatform.dir/Mutex.cpp.s"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/roboto/Downloads/alvar-master/src/platform/Mutex.cpp -o CMakeFiles/ALVARPlatform.dir/Mutex.cpp.s

src/platform/CMakeFiles/ALVARPlatform.dir/Mutex.cpp.o.requires:
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/Mutex.cpp.o.requires

src/platform/CMakeFiles/ALVARPlatform.dir/Mutex.cpp.o.provides: src/platform/CMakeFiles/ALVARPlatform.dir/Mutex.cpp.o.requires
	$(MAKE) -f src/platform/CMakeFiles/ALVARPlatform.dir/build.make src/platform/CMakeFiles/ALVARPlatform.dir/Mutex.cpp.o.provides.build
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/Mutex.cpp.o.provides

src/platform/CMakeFiles/ALVARPlatform.dir/Mutex.cpp.o.provides.build: src/platform/CMakeFiles/ALVARPlatform.dir/Mutex.cpp.o

src/platform/CMakeFiles/ALVARPlatform.dir/Platform.cpp.o: src/platform/CMakeFiles/ALVARPlatform.dir/flags.make
src/platform/CMakeFiles/ALVARPlatform.dir/Platform.cpp.o: ../src/platform/Platform.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/roboto/Downloads/alvar-master/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/platform/CMakeFiles/ALVARPlatform.dir/Platform.cpp.o"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ALVARPlatform.dir/Platform.cpp.o -c /home/roboto/Downloads/alvar-master/src/platform/Platform.cpp

src/platform/CMakeFiles/ALVARPlatform.dir/Platform.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ALVARPlatform.dir/Platform.cpp.i"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/roboto/Downloads/alvar-master/src/platform/Platform.cpp > CMakeFiles/ALVARPlatform.dir/Platform.cpp.i

src/platform/CMakeFiles/ALVARPlatform.dir/Platform.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ALVARPlatform.dir/Platform.cpp.s"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/roboto/Downloads/alvar-master/src/platform/Platform.cpp -o CMakeFiles/ALVARPlatform.dir/Platform.cpp.s

src/platform/CMakeFiles/ALVARPlatform.dir/Platform.cpp.o.requires:
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/Platform.cpp.o.requires

src/platform/CMakeFiles/ALVARPlatform.dir/Platform.cpp.o.provides: src/platform/CMakeFiles/ALVARPlatform.dir/Platform.cpp.o.requires
	$(MAKE) -f src/platform/CMakeFiles/ALVARPlatform.dir/build.make src/platform/CMakeFiles/ALVARPlatform.dir/Platform.cpp.o.provides.build
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/Platform.cpp.o.provides

src/platform/CMakeFiles/ALVARPlatform.dir/Platform.cpp.o.provides.build: src/platform/CMakeFiles/ALVARPlatform.dir/Platform.cpp.o

src/platform/CMakeFiles/ALVARPlatform.dir/Plugin.cpp.o: src/platform/CMakeFiles/ALVARPlatform.dir/flags.make
src/platform/CMakeFiles/ALVARPlatform.dir/Plugin.cpp.o: ../src/platform/Plugin.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/roboto/Downloads/alvar-master/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/platform/CMakeFiles/ALVARPlatform.dir/Plugin.cpp.o"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ALVARPlatform.dir/Plugin.cpp.o -c /home/roboto/Downloads/alvar-master/src/platform/Plugin.cpp

src/platform/CMakeFiles/ALVARPlatform.dir/Plugin.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ALVARPlatform.dir/Plugin.cpp.i"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/roboto/Downloads/alvar-master/src/platform/Plugin.cpp > CMakeFiles/ALVARPlatform.dir/Plugin.cpp.i

src/platform/CMakeFiles/ALVARPlatform.dir/Plugin.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ALVARPlatform.dir/Plugin.cpp.s"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/roboto/Downloads/alvar-master/src/platform/Plugin.cpp -o CMakeFiles/ALVARPlatform.dir/Plugin.cpp.s

src/platform/CMakeFiles/ALVARPlatform.dir/Plugin.cpp.o.requires:
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/Plugin.cpp.o.requires

src/platform/CMakeFiles/ALVARPlatform.dir/Plugin.cpp.o.provides: src/platform/CMakeFiles/ALVARPlatform.dir/Plugin.cpp.o.requires
	$(MAKE) -f src/platform/CMakeFiles/ALVARPlatform.dir/build.make src/platform/CMakeFiles/ALVARPlatform.dir/Plugin.cpp.o.provides.build
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/Plugin.cpp.o.provides

src/platform/CMakeFiles/ALVARPlatform.dir/Plugin.cpp.o.provides.build: src/platform/CMakeFiles/ALVARPlatform.dir/Plugin.cpp.o

src/platform/CMakeFiles/ALVARPlatform.dir/Threads.cpp.o: src/platform/CMakeFiles/ALVARPlatform.dir/flags.make
src/platform/CMakeFiles/ALVARPlatform.dir/Threads.cpp.o: ../src/platform/Threads.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/roboto/Downloads/alvar-master/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/platform/CMakeFiles/ALVARPlatform.dir/Threads.cpp.o"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ALVARPlatform.dir/Threads.cpp.o -c /home/roboto/Downloads/alvar-master/src/platform/Threads.cpp

src/platform/CMakeFiles/ALVARPlatform.dir/Threads.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ALVARPlatform.dir/Threads.cpp.i"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/roboto/Downloads/alvar-master/src/platform/Threads.cpp > CMakeFiles/ALVARPlatform.dir/Threads.cpp.i

src/platform/CMakeFiles/ALVARPlatform.dir/Threads.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ALVARPlatform.dir/Threads.cpp.s"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/roboto/Downloads/alvar-master/src/platform/Threads.cpp -o CMakeFiles/ALVARPlatform.dir/Threads.cpp.s

src/platform/CMakeFiles/ALVARPlatform.dir/Threads.cpp.o.requires:
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/Threads.cpp.o.requires

src/platform/CMakeFiles/ALVARPlatform.dir/Threads.cpp.o.provides: src/platform/CMakeFiles/ALVARPlatform.dir/Threads.cpp.o.requires
	$(MAKE) -f src/platform/CMakeFiles/ALVARPlatform.dir/build.make src/platform/CMakeFiles/ALVARPlatform.dir/Threads.cpp.o.provides.build
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/Threads.cpp.o.provides

src/platform/CMakeFiles/ALVARPlatform.dir/Threads.cpp.o.provides.build: src/platform/CMakeFiles/ALVARPlatform.dir/Threads.cpp.o

src/platform/CMakeFiles/ALVARPlatform.dir/Timer.cpp.o: src/platform/CMakeFiles/ALVARPlatform.dir/flags.make
src/platform/CMakeFiles/ALVARPlatform.dir/Timer.cpp.o: ../src/platform/Timer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/roboto/Downloads/alvar-master/build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/platform/CMakeFiles/ALVARPlatform.dir/Timer.cpp.o"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ALVARPlatform.dir/Timer.cpp.o -c /home/roboto/Downloads/alvar-master/src/platform/Timer.cpp

src/platform/CMakeFiles/ALVARPlatform.dir/Timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ALVARPlatform.dir/Timer.cpp.i"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/roboto/Downloads/alvar-master/src/platform/Timer.cpp > CMakeFiles/ALVARPlatform.dir/Timer.cpp.i

src/platform/CMakeFiles/ALVARPlatform.dir/Timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ALVARPlatform.dir/Timer.cpp.s"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/roboto/Downloads/alvar-master/src/platform/Timer.cpp -o CMakeFiles/ALVARPlatform.dir/Timer.cpp.s

src/platform/CMakeFiles/ALVARPlatform.dir/Timer.cpp.o.requires:
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/Timer.cpp.o.requires

src/platform/CMakeFiles/ALVARPlatform.dir/Timer.cpp.o.provides: src/platform/CMakeFiles/ALVARPlatform.dir/Timer.cpp.o.requires
	$(MAKE) -f src/platform/CMakeFiles/ALVARPlatform.dir/build.make src/platform/CMakeFiles/ALVARPlatform.dir/Timer.cpp.o.provides.build
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/Timer.cpp.o.provides

src/platform/CMakeFiles/ALVARPlatform.dir/Timer.cpp.o.provides.build: src/platform/CMakeFiles/ALVARPlatform.dir/Timer.cpp.o

src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory_unix.cpp.o: src/platform/CMakeFiles/ALVARPlatform.dir/flags.make
src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory_unix.cpp.o: ../src/platform/CaptureFactory_unix.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/roboto/Downloads/alvar-master/build/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory_unix.cpp.o"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ALVARPlatform.dir/CaptureFactory_unix.cpp.o -c /home/roboto/Downloads/alvar-master/src/platform/CaptureFactory_unix.cpp

src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory_unix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ALVARPlatform.dir/CaptureFactory_unix.cpp.i"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/roboto/Downloads/alvar-master/src/platform/CaptureFactory_unix.cpp > CMakeFiles/ALVARPlatform.dir/CaptureFactory_unix.cpp.i

src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory_unix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ALVARPlatform.dir/CaptureFactory_unix.cpp.s"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/roboto/Downloads/alvar-master/src/platform/CaptureFactory_unix.cpp -o CMakeFiles/ALVARPlatform.dir/CaptureFactory_unix.cpp.s

src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory_unix.cpp.o.requires:
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory_unix.cpp.o.requires

src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory_unix.cpp.o.provides: src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory_unix.cpp.o.requires
	$(MAKE) -f src/platform/CMakeFiles/ALVARPlatform.dir/build.make src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory_unix.cpp.o.provides.build
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory_unix.cpp.o.provides

src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory_unix.cpp.o.provides.build: src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory_unix.cpp.o

src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator_unix.cpp.o: src/platform/CMakeFiles/ALVARPlatform.dir/flags.make
src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator_unix.cpp.o: ../src/platform/DirectoryIterator_unix.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/roboto/Downloads/alvar-master/build/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator_unix.cpp.o"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ALVARPlatform.dir/DirectoryIterator_unix.cpp.o -c /home/roboto/Downloads/alvar-master/src/platform/DirectoryIterator_unix.cpp

src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator_unix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ALVARPlatform.dir/DirectoryIterator_unix.cpp.i"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/roboto/Downloads/alvar-master/src/platform/DirectoryIterator_unix.cpp > CMakeFiles/ALVARPlatform.dir/DirectoryIterator_unix.cpp.i

src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator_unix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ALVARPlatform.dir/DirectoryIterator_unix.cpp.s"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/roboto/Downloads/alvar-master/src/platform/DirectoryIterator_unix.cpp -o CMakeFiles/ALVARPlatform.dir/DirectoryIterator_unix.cpp.s

src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator_unix.cpp.o.requires:
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator_unix.cpp.o.requires

src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator_unix.cpp.o.provides: src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator_unix.cpp.o.requires
	$(MAKE) -f src/platform/CMakeFiles/ALVARPlatform.dir/build.make src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator_unix.cpp.o.provides.build
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator_unix.cpp.o.provides

src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator_unix.cpp.o.provides.build: src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator_unix.cpp.o

src/platform/CMakeFiles/ALVARPlatform.dir/Mutex_unix.cpp.o: src/platform/CMakeFiles/ALVARPlatform.dir/flags.make
src/platform/CMakeFiles/ALVARPlatform.dir/Mutex_unix.cpp.o: ../src/platform/Mutex_unix.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/roboto/Downloads/alvar-master/build/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/platform/CMakeFiles/ALVARPlatform.dir/Mutex_unix.cpp.o"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ALVARPlatform.dir/Mutex_unix.cpp.o -c /home/roboto/Downloads/alvar-master/src/platform/Mutex_unix.cpp

src/platform/CMakeFiles/ALVARPlatform.dir/Mutex_unix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ALVARPlatform.dir/Mutex_unix.cpp.i"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/roboto/Downloads/alvar-master/src/platform/Mutex_unix.cpp > CMakeFiles/ALVARPlatform.dir/Mutex_unix.cpp.i

src/platform/CMakeFiles/ALVARPlatform.dir/Mutex_unix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ALVARPlatform.dir/Mutex_unix.cpp.s"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/roboto/Downloads/alvar-master/src/platform/Mutex_unix.cpp -o CMakeFiles/ALVARPlatform.dir/Mutex_unix.cpp.s

src/platform/CMakeFiles/ALVARPlatform.dir/Mutex_unix.cpp.o.requires:
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/Mutex_unix.cpp.o.requires

src/platform/CMakeFiles/ALVARPlatform.dir/Mutex_unix.cpp.o.provides: src/platform/CMakeFiles/ALVARPlatform.dir/Mutex_unix.cpp.o.requires
	$(MAKE) -f src/platform/CMakeFiles/ALVARPlatform.dir/build.make src/platform/CMakeFiles/ALVARPlatform.dir/Mutex_unix.cpp.o.provides.build
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/Mutex_unix.cpp.o.provides

src/platform/CMakeFiles/ALVARPlatform.dir/Mutex_unix.cpp.o.provides.build: src/platform/CMakeFiles/ALVARPlatform.dir/Mutex_unix.cpp.o

src/platform/CMakeFiles/ALVARPlatform.dir/Plugin_unix.cpp.o: src/platform/CMakeFiles/ALVARPlatform.dir/flags.make
src/platform/CMakeFiles/ALVARPlatform.dir/Plugin_unix.cpp.o: ../src/platform/Plugin_unix.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/roboto/Downloads/alvar-master/build/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/platform/CMakeFiles/ALVARPlatform.dir/Plugin_unix.cpp.o"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ALVARPlatform.dir/Plugin_unix.cpp.o -c /home/roboto/Downloads/alvar-master/src/platform/Plugin_unix.cpp

src/platform/CMakeFiles/ALVARPlatform.dir/Plugin_unix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ALVARPlatform.dir/Plugin_unix.cpp.i"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/roboto/Downloads/alvar-master/src/platform/Plugin_unix.cpp > CMakeFiles/ALVARPlatform.dir/Plugin_unix.cpp.i

src/platform/CMakeFiles/ALVARPlatform.dir/Plugin_unix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ALVARPlatform.dir/Plugin_unix.cpp.s"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/roboto/Downloads/alvar-master/src/platform/Plugin_unix.cpp -o CMakeFiles/ALVARPlatform.dir/Plugin_unix.cpp.s

src/platform/CMakeFiles/ALVARPlatform.dir/Plugin_unix.cpp.o.requires:
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/Plugin_unix.cpp.o.requires

src/platform/CMakeFiles/ALVARPlatform.dir/Plugin_unix.cpp.o.provides: src/platform/CMakeFiles/ALVARPlatform.dir/Plugin_unix.cpp.o.requires
	$(MAKE) -f src/platform/CMakeFiles/ALVARPlatform.dir/build.make src/platform/CMakeFiles/ALVARPlatform.dir/Plugin_unix.cpp.o.provides.build
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/Plugin_unix.cpp.o.provides

src/platform/CMakeFiles/ALVARPlatform.dir/Plugin_unix.cpp.o.provides.build: src/platform/CMakeFiles/ALVARPlatform.dir/Plugin_unix.cpp.o

src/platform/CMakeFiles/ALVARPlatform.dir/Threads_unix.cpp.o: src/platform/CMakeFiles/ALVARPlatform.dir/flags.make
src/platform/CMakeFiles/ALVARPlatform.dir/Threads_unix.cpp.o: ../src/platform/Threads_unix.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/roboto/Downloads/alvar-master/build/CMakeFiles $(CMAKE_PROGRESS_13)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/platform/CMakeFiles/ALVARPlatform.dir/Threads_unix.cpp.o"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ALVARPlatform.dir/Threads_unix.cpp.o -c /home/roboto/Downloads/alvar-master/src/platform/Threads_unix.cpp

src/platform/CMakeFiles/ALVARPlatform.dir/Threads_unix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ALVARPlatform.dir/Threads_unix.cpp.i"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/roboto/Downloads/alvar-master/src/platform/Threads_unix.cpp > CMakeFiles/ALVARPlatform.dir/Threads_unix.cpp.i

src/platform/CMakeFiles/ALVARPlatform.dir/Threads_unix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ALVARPlatform.dir/Threads_unix.cpp.s"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/roboto/Downloads/alvar-master/src/platform/Threads_unix.cpp -o CMakeFiles/ALVARPlatform.dir/Threads_unix.cpp.s

src/platform/CMakeFiles/ALVARPlatform.dir/Threads_unix.cpp.o.requires:
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/Threads_unix.cpp.o.requires

src/platform/CMakeFiles/ALVARPlatform.dir/Threads_unix.cpp.o.provides: src/platform/CMakeFiles/ALVARPlatform.dir/Threads_unix.cpp.o.requires
	$(MAKE) -f src/platform/CMakeFiles/ALVARPlatform.dir/build.make src/platform/CMakeFiles/ALVARPlatform.dir/Threads_unix.cpp.o.provides.build
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/Threads_unix.cpp.o.provides

src/platform/CMakeFiles/ALVARPlatform.dir/Threads_unix.cpp.o.provides.build: src/platform/CMakeFiles/ALVARPlatform.dir/Threads_unix.cpp.o

src/platform/CMakeFiles/ALVARPlatform.dir/Timer_unix.cpp.o: src/platform/CMakeFiles/ALVARPlatform.dir/flags.make
src/platform/CMakeFiles/ALVARPlatform.dir/Timer_unix.cpp.o: ../src/platform/Timer_unix.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/roboto/Downloads/alvar-master/build/CMakeFiles $(CMAKE_PROGRESS_14)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/platform/CMakeFiles/ALVARPlatform.dir/Timer_unix.cpp.o"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ALVARPlatform.dir/Timer_unix.cpp.o -c /home/roboto/Downloads/alvar-master/src/platform/Timer_unix.cpp

src/platform/CMakeFiles/ALVARPlatform.dir/Timer_unix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ALVARPlatform.dir/Timer_unix.cpp.i"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/roboto/Downloads/alvar-master/src/platform/Timer_unix.cpp > CMakeFiles/ALVARPlatform.dir/Timer_unix.cpp.i

src/platform/CMakeFiles/ALVARPlatform.dir/Timer_unix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ALVARPlatform.dir/Timer_unix.cpp.s"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/roboto/Downloads/alvar-master/src/platform/Timer_unix.cpp -o CMakeFiles/ALVARPlatform.dir/Timer_unix.cpp.s

src/platform/CMakeFiles/ALVARPlatform.dir/Timer_unix.cpp.o.requires:
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/Timer_unix.cpp.o.requires

src/platform/CMakeFiles/ALVARPlatform.dir/Timer_unix.cpp.o.provides: src/platform/CMakeFiles/ALVARPlatform.dir/Timer_unix.cpp.o.requires
	$(MAKE) -f src/platform/CMakeFiles/ALVARPlatform.dir/build.make src/platform/CMakeFiles/ALVARPlatform.dir/Timer_unix.cpp.o.provides.build
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/Timer_unix.cpp.o.provides

src/platform/CMakeFiles/ALVARPlatform.dir/Timer_unix.cpp.o.provides.build: src/platform/CMakeFiles/ALVARPlatform.dir/Timer_unix.cpp.o

# Object files for target ALVARPlatform
ALVARPlatform_OBJECTS = \
"CMakeFiles/ALVARPlatform.dir/CaptureFactory.cpp.o" \
"CMakeFiles/ALVARPlatform.dir/CaptureDevice.cpp.o" \
"CMakeFiles/ALVARPlatform.dir/DirectoryIterator.cpp.o" \
"CMakeFiles/ALVARPlatform.dir/Mutex.cpp.o" \
"CMakeFiles/ALVARPlatform.dir/Platform.cpp.o" \
"CMakeFiles/ALVARPlatform.dir/Plugin.cpp.o" \
"CMakeFiles/ALVARPlatform.dir/Threads.cpp.o" \
"CMakeFiles/ALVARPlatform.dir/Timer.cpp.o" \
"CMakeFiles/ALVARPlatform.dir/CaptureFactory_unix.cpp.o" \
"CMakeFiles/ALVARPlatform.dir/DirectoryIterator_unix.cpp.o" \
"CMakeFiles/ALVARPlatform.dir/Mutex_unix.cpp.o" \
"CMakeFiles/ALVARPlatform.dir/Plugin_unix.cpp.o" \
"CMakeFiles/ALVARPlatform.dir/Threads_unix.cpp.o" \
"CMakeFiles/ALVARPlatform.dir/Timer_unix.cpp.o"

# External object files for target ALVARPlatform
ALVARPlatform_EXTERNAL_OBJECTS =

src/platform/libalvarplatform200.so: src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory.cpp.o
src/platform/libalvarplatform200.so: src/platform/CMakeFiles/ALVARPlatform.dir/CaptureDevice.cpp.o
src/platform/libalvarplatform200.so: src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator.cpp.o
src/platform/libalvarplatform200.so: src/platform/CMakeFiles/ALVARPlatform.dir/Mutex.cpp.o
src/platform/libalvarplatform200.so: src/platform/CMakeFiles/ALVARPlatform.dir/Platform.cpp.o
src/platform/libalvarplatform200.so: src/platform/CMakeFiles/ALVARPlatform.dir/Plugin.cpp.o
src/platform/libalvarplatform200.so: src/platform/CMakeFiles/ALVARPlatform.dir/Threads.cpp.o
src/platform/libalvarplatform200.so: src/platform/CMakeFiles/ALVARPlatform.dir/Timer.cpp.o
src/platform/libalvarplatform200.so: src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory_unix.cpp.o
src/platform/libalvarplatform200.so: src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator_unix.cpp.o
src/platform/libalvarplatform200.so: src/platform/CMakeFiles/ALVARPlatform.dir/Mutex_unix.cpp.o
src/platform/libalvarplatform200.so: src/platform/CMakeFiles/ALVARPlatform.dir/Plugin_unix.cpp.o
src/platform/libalvarplatform200.so: src/platform/CMakeFiles/ALVARPlatform.dir/Threads_unix.cpp.o
src/platform/libalvarplatform200.so: src/platform/CMakeFiles/ALVARPlatform.dir/Timer_unix.cpp.o
src/platform/libalvarplatform200.so: src/platform/CMakeFiles/ALVARPlatform.dir/build.make
src/platform/libalvarplatform200.so: src/libalvar200.so
src/platform/libalvarplatform200.so: /usr/local/lib/libopencv_calib3d.so.2.4.9
src/platform/libalvarplatform200.so: /usr/local/lib/libopencv_core.so.2.4.9
src/platform/libalvarplatform200.so: /usr/local/lib/libopencv_features2d.so.2.4.9
src/platform/libalvarplatform200.so: /usr/local/lib/libopencv_flann.so.2.4.9
src/platform/libalvarplatform200.so: /usr/local/lib/libopencv_highgui.so.2.4.9
src/platform/libalvarplatform200.so: /usr/local/lib/libopencv_imgproc.so.2.4.9
src/platform/libalvarplatform200.so: /usr/local/lib/libopencv_legacy.so.2.4.9
src/platform/libalvarplatform200.so: /usr/local/lib/libopencv_ml.so.2.4.9
src/platform/libalvarplatform200.so: /usr/local/lib/libopencv_video.so.2.4.9
src/platform/libalvarplatform200.so: /usr/local/lib/libopencv_calib3d.so.2.4.9
src/platform/libalvarplatform200.so: /usr/local/lib/libopencv_features2d.so.2.4.9
src/platform/libalvarplatform200.so: /usr/local/lib/libopencv_flann.so.2.4.9
src/platform/libalvarplatform200.so: /usr/local/lib/libopencv_highgui.so.2.4.9
src/platform/libalvarplatform200.so: /usr/local/lib/libopencv_imgproc.so.2.4.9
src/platform/libalvarplatform200.so: /usr/local/lib/libopencv_core.so.2.4.9
src/platform/libalvarplatform200.so: 3rdparty/libTinyXML.a
src/platform/libalvarplatform200.so: src/platform/CMakeFiles/ALVARPlatform.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libalvarplatform200.so"
	cd /home/roboto/Downloads/alvar-master/build/src/platform && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ALVARPlatform.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/platform/CMakeFiles/ALVARPlatform.dir/build: src/platform/libalvarplatform200.so
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/build

src/platform/CMakeFiles/ALVARPlatform.dir/requires: src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory.cpp.o.requires
src/platform/CMakeFiles/ALVARPlatform.dir/requires: src/platform/CMakeFiles/ALVARPlatform.dir/CaptureDevice.cpp.o.requires
src/platform/CMakeFiles/ALVARPlatform.dir/requires: src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator.cpp.o.requires
src/platform/CMakeFiles/ALVARPlatform.dir/requires: src/platform/CMakeFiles/ALVARPlatform.dir/Mutex.cpp.o.requires
src/platform/CMakeFiles/ALVARPlatform.dir/requires: src/platform/CMakeFiles/ALVARPlatform.dir/Platform.cpp.o.requires
src/platform/CMakeFiles/ALVARPlatform.dir/requires: src/platform/CMakeFiles/ALVARPlatform.dir/Plugin.cpp.o.requires
src/platform/CMakeFiles/ALVARPlatform.dir/requires: src/platform/CMakeFiles/ALVARPlatform.dir/Threads.cpp.o.requires
src/platform/CMakeFiles/ALVARPlatform.dir/requires: src/platform/CMakeFiles/ALVARPlatform.dir/Timer.cpp.o.requires
src/platform/CMakeFiles/ALVARPlatform.dir/requires: src/platform/CMakeFiles/ALVARPlatform.dir/CaptureFactory_unix.cpp.o.requires
src/platform/CMakeFiles/ALVARPlatform.dir/requires: src/platform/CMakeFiles/ALVARPlatform.dir/DirectoryIterator_unix.cpp.o.requires
src/platform/CMakeFiles/ALVARPlatform.dir/requires: src/platform/CMakeFiles/ALVARPlatform.dir/Mutex_unix.cpp.o.requires
src/platform/CMakeFiles/ALVARPlatform.dir/requires: src/platform/CMakeFiles/ALVARPlatform.dir/Plugin_unix.cpp.o.requires
src/platform/CMakeFiles/ALVARPlatform.dir/requires: src/platform/CMakeFiles/ALVARPlatform.dir/Threads_unix.cpp.o.requires
src/platform/CMakeFiles/ALVARPlatform.dir/requires: src/platform/CMakeFiles/ALVARPlatform.dir/Timer_unix.cpp.o.requires
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/requires

src/platform/CMakeFiles/ALVARPlatform.dir/clean:
	cd /home/roboto/Downloads/alvar-master/build/src/platform && $(CMAKE_COMMAND) -P CMakeFiles/ALVARPlatform.dir/cmake_clean.cmake
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/clean

src/platform/CMakeFiles/ALVARPlatform.dir/depend:
	cd /home/roboto/Downloads/alvar-master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/roboto/Downloads/alvar-master /home/roboto/Downloads/alvar-master/src/platform /home/roboto/Downloads/alvar-master/build /home/roboto/Downloads/alvar-master/build/src/platform /home/roboto/Downloads/alvar-master/build/src/platform/CMakeFiles/ALVARPlatform.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/platform/CMakeFiles/ALVARPlatform.dir/depend

