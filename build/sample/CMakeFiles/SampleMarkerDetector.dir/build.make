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
include sample/CMakeFiles/SampleMarkerDetector.dir/depend.make

# Include the progress variables for this target.
include sample/CMakeFiles/SampleMarkerDetector.dir/progress.make

# Include the compile flags for this target's objects.
include sample/CMakeFiles/SampleMarkerDetector.dir/flags.make

sample/CMakeFiles/SampleMarkerDetector.dir/SampleMarkerDetector.cpp.o: sample/CMakeFiles/SampleMarkerDetector.dir/flags.make
sample/CMakeFiles/SampleMarkerDetector.dir/SampleMarkerDetector.cpp.o: ../sample/SampleMarkerDetector.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/roboto/Downloads/alvar-master/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object sample/CMakeFiles/SampleMarkerDetector.dir/SampleMarkerDetector.cpp.o"
	cd /home/roboto/Downloads/alvar-master/build/sample && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/SampleMarkerDetector.dir/SampleMarkerDetector.cpp.o -c /home/roboto/Downloads/alvar-master/sample/SampleMarkerDetector.cpp

sample/CMakeFiles/SampleMarkerDetector.dir/SampleMarkerDetector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SampleMarkerDetector.dir/SampleMarkerDetector.cpp.i"
	cd /home/roboto/Downloads/alvar-master/build/sample && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/roboto/Downloads/alvar-master/sample/SampleMarkerDetector.cpp > CMakeFiles/SampleMarkerDetector.dir/SampleMarkerDetector.cpp.i

sample/CMakeFiles/SampleMarkerDetector.dir/SampleMarkerDetector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SampleMarkerDetector.dir/SampleMarkerDetector.cpp.s"
	cd /home/roboto/Downloads/alvar-master/build/sample && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/roboto/Downloads/alvar-master/sample/SampleMarkerDetector.cpp -o CMakeFiles/SampleMarkerDetector.dir/SampleMarkerDetector.cpp.s

sample/CMakeFiles/SampleMarkerDetector.dir/SampleMarkerDetector.cpp.o.requires:
.PHONY : sample/CMakeFiles/SampleMarkerDetector.dir/SampleMarkerDetector.cpp.o.requires

sample/CMakeFiles/SampleMarkerDetector.dir/SampleMarkerDetector.cpp.o.provides: sample/CMakeFiles/SampleMarkerDetector.dir/SampleMarkerDetector.cpp.o.requires
	$(MAKE) -f sample/CMakeFiles/SampleMarkerDetector.dir/build.make sample/CMakeFiles/SampleMarkerDetector.dir/SampleMarkerDetector.cpp.o.provides.build
.PHONY : sample/CMakeFiles/SampleMarkerDetector.dir/SampleMarkerDetector.cpp.o.provides

sample/CMakeFiles/SampleMarkerDetector.dir/SampleMarkerDetector.cpp.o.provides.build: sample/CMakeFiles/SampleMarkerDetector.dir/SampleMarkerDetector.cpp.o

# Object files for target SampleMarkerDetector
SampleMarkerDetector_OBJECTS = \
"CMakeFiles/SampleMarkerDetector.dir/SampleMarkerDetector.cpp.o"

# External object files for target SampleMarkerDetector
SampleMarkerDetector_EXTERNAL_OBJECTS =

sample/samplemarkerdetector: sample/CMakeFiles/SampleMarkerDetector.dir/SampleMarkerDetector.cpp.o
sample/samplemarkerdetector: sample/CMakeFiles/SampleMarkerDetector.dir/build.make
sample/samplemarkerdetector: /usr/local/lib/libopencv_calib3d.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_core.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_features2d.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_flann.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_highgui.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_imgproc.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_legacy.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_ml.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_video.so.2.4.9
sample/samplemarkerdetector: src/libalvar200.so
sample/samplemarkerdetector: /usr/local/lib/libopencv_calib3d.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_core.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_features2d.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_flann.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_highgui.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_imgproc.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_legacy.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_ml.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_video.so.2.4.9
sample/samplemarkerdetector: 3rdparty/libTinyXML.a
sample/samplemarkerdetector: src/platform/libalvarplatform200.so
sample/samplemarkerdetector: sample/libSharedSamples.a
sample/samplemarkerdetector: sample/libSharedGlutViewer.a
sample/samplemarkerdetector: src/libalvar200.so
sample/samplemarkerdetector: /usr/local/lib/libopencv_legacy.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_calib3d.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_features2d.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_flann.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_highgui.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_ml.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_video.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_imgproc.so.2.4.9
sample/samplemarkerdetector: /usr/local/lib/libopencv_core.so.2.4.9
sample/samplemarkerdetector: 3rdparty/libTinyXML.a
sample/samplemarkerdetector: /usr/lib/x86_64-linux-gnu/libGLU.so
sample/samplemarkerdetector: /usr/lib/x86_64-linux-gnu/libGL.so
sample/samplemarkerdetector: /usr/lib/x86_64-linux-gnu/libSM.so
sample/samplemarkerdetector: /usr/lib/x86_64-linux-gnu/libICE.so
sample/samplemarkerdetector: /usr/lib/x86_64-linux-gnu/libX11.so
sample/samplemarkerdetector: /usr/lib/x86_64-linux-gnu/libXext.so
sample/samplemarkerdetector: /usr/lib/x86_64-linux-gnu/libglut.so
sample/samplemarkerdetector: sample/CMakeFiles/SampleMarkerDetector.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable samplemarkerdetector"
	cd /home/roboto/Downloads/alvar-master/build/sample && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SampleMarkerDetector.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sample/CMakeFiles/SampleMarkerDetector.dir/build: sample/samplemarkerdetector
.PHONY : sample/CMakeFiles/SampleMarkerDetector.dir/build

sample/CMakeFiles/SampleMarkerDetector.dir/requires: sample/CMakeFiles/SampleMarkerDetector.dir/SampleMarkerDetector.cpp.o.requires
.PHONY : sample/CMakeFiles/SampleMarkerDetector.dir/requires

sample/CMakeFiles/SampleMarkerDetector.dir/clean:
	cd /home/roboto/Downloads/alvar-master/build/sample && $(CMAKE_COMMAND) -P CMakeFiles/SampleMarkerDetector.dir/cmake_clean.cmake
.PHONY : sample/CMakeFiles/SampleMarkerDetector.dir/clean

sample/CMakeFiles/SampleMarkerDetector.dir/depend:
	cd /home/roboto/Downloads/alvar-master/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/roboto/Downloads/alvar-master /home/roboto/Downloads/alvar-master/sample /home/roboto/Downloads/alvar-master/build /home/roboto/Downloads/alvar-master/build/sample /home/roboto/Downloads/alvar-master/build/sample/CMakeFiles/SampleMarkerDetector.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sample/CMakeFiles/SampleMarkerDetector.dir/depend

