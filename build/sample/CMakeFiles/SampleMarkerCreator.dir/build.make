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
include sample/CMakeFiles/SampleMarkerCreator.dir/depend.make

# Include the progress variables for this target.
include sample/CMakeFiles/SampleMarkerCreator.dir/progress.make

# Include the compile flags for this target's objects.
include sample/CMakeFiles/SampleMarkerCreator.dir/flags.make

sample/CMakeFiles/SampleMarkerCreator.dir/SampleMarkerCreator.cpp.o: sample/CMakeFiles/SampleMarkerCreator.dir/flags.make
sample/CMakeFiles/SampleMarkerCreator.dir/SampleMarkerCreator.cpp.o: ../sample/SampleMarkerCreator.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/roboto/Downloads/alvar-master/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object sample/CMakeFiles/SampleMarkerCreator.dir/SampleMarkerCreator.cpp.o"
	cd /home/roboto/Downloads/alvar-master/build/sample && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/SampleMarkerCreator.dir/SampleMarkerCreator.cpp.o -c /home/roboto/Downloads/alvar-master/sample/SampleMarkerCreator.cpp

sample/CMakeFiles/SampleMarkerCreator.dir/SampleMarkerCreator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SampleMarkerCreator.dir/SampleMarkerCreator.cpp.i"
	cd /home/roboto/Downloads/alvar-master/build/sample && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/roboto/Downloads/alvar-master/sample/SampleMarkerCreator.cpp > CMakeFiles/SampleMarkerCreator.dir/SampleMarkerCreator.cpp.i

sample/CMakeFiles/SampleMarkerCreator.dir/SampleMarkerCreator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SampleMarkerCreator.dir/SampleMarkerCreator.cpp.s"
	cd /home/roboto/Downloads/alvar-master/build/sample && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/roboto/Downloads/alvar-master/sample/SampleMarkerCreator.cpp -o CMakeFiles/SampleMarkerCreator.dir/SampleMarkerCreator.cpp.s

sample/CMakeFiles/SampleMarkerCreator.dir/SampleMarkerCreator.cpp.o.requires:
.PHONY : sample/CMakeFiles/SampleMarkerCreator.dir/SampleMarkerCreator.cpp.o.requires

sample/CMakeFiles/SampleMarkerCreator.dir/SampleMarkerCreator.cpp.o.provides: sample/CMakeFiles/SampleMarkerCreator.dir/SampleMarkerCreator.cpp.o.requires
	$(MAKE) -f sample/CMakeFiles/SampleMarkerCreator.dir/build.make sample/CMakeFiles/SampleMarkerCreator.dir/SampleMarkerCreator.cpp.o.provides.build
.PHONY : sample/CMakeFiles/SampleMarkerCreator.dir/SampleMarkerCreator.cpp.o.provides

sample/CMakeFiles/SampleMarkerCreator.dir/SampleMarkerCreator.cpp.o.provides.build: sample/CMakeFiles/SampleMarkerCreator.dir/SampleMarkerCreator.cpp.o

# Object files for target SampleMarkerCreator
SampleMarkerCreator_OBJECTS = \
"CMakeFiles/SampleMarkerCreator.dir/SampleMarkerCreator.cpp.o"

# External object files for target SampleMarkerCreator
SampleMarkerCreator_EXTERNAL_OBJECTS =

sample/samplemarkercreator: sample/CMakeFiles/SampleMarkerCreator.dir/SampleMarkerCreator.cpp.o
sample/samplemarkercreator: sample/CMakeFiles/SampleMarkerCreator.dir/build.make
sample/samplemarkercreator: /usr/local/lib/libopencv_calib3d.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_core.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_features2d.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_flann.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_highgui.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_imgproc.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_legacy.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_ml.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_video.so.2.4.9
sample/samplemarkercreator: src/libalvar200.so
sample/samplemarkercreator: /usr/local/lib/libopencv_calib3d.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_core.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_features2d.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_flann.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_highgui.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_imgproc.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_legacy.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_ml.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_video.so.2.4.9
sample/samplemarkercreator: 3rdparty/libTinyXML.a
sample/samplemarkercreator: src/platform/libalvarplatform200.so
sample/samplemarkercreator: sample/libSharedSamples.a
sample/samplemarkercreator: src/libalvar200.so
sample/samplemarkercreator: /usr/local/lib/libopencv_legacy.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_calib3d.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_features2d.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_flann.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_highgui.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_ml.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_video.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_imgproc.so.2.4.9
sample/samplemarkercreator: /usr/local/lib/libopencv_core.so.2.4.9
sample/samplemarkercreator: 3rdparty/libTinyXML.a
sample/samplemarkercreator: sample/CMakeFiles/SampleMarkerCreator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable samplemarkercreator"
	cd /home/roboto/Downloads/alvar-master/build/sample && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SampleMarkerCreator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sample/CMakeFiles/SampleMarkerCreator.dir/build: sample/samplemarkercreator
.PHONY : sample/CMakeFiles/SampleMarkerCreator.dir/build

sample/CMakeFiles/SampleMarkerCreator.dir/requires: sample/CMakeFiles/SampleMarkerCreator.dir/SampleMarkerCreator.cpp.o.requires
.PHONY : sample/CMakeFiles/SampleMarkerCreator.dir/requires

sample/CMakeFiles/SampleMarkerCreator.dir/clean:
	cd /home/roboto/Downloads/alvar-master/build/sample && $(CMAKE_COMMAND) -P CMakeFiles/SampleMarkerCreator.dir/cmake_clean.cmake
.PHONY : sample/CMakeFiles/SampleMarkerCreator.dir/clean

sample/CMakeFiles/SampleMarkerCreator.dir/depend:
	cd /home/roboto/Downloads/alvar-master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/roboto/Downloads/alvar-master /home/roboto/Downloads/alvar-master/sample /home/roboto/Downloads/alvar-master/build /home/roboto/Downloads/alvar-master/build/sample /home/roboto/Downloads/alvar-master/build/sample/CMakeFiles/SampleMarkerCreator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sample/CMakeFiles/SampleMarkerCreator.dir/depend

