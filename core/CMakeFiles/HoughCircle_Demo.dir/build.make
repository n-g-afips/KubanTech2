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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kolyan/opencv/opencv/samples/cpp/tutorial_code/ImgTrans

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kolyan/opencv/opencv/samples/cpp/tutorial_code/ImgTrans

# Include any dependencies generated for this target.
include CMakeFiles/HoughCircle_Demo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HoughCircle_Demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HoughCircle_Demo.dir/flags.make

CMakeFiles/HoughCircle_Demo.dir/HoughCircle_Demo.cpp.o: CMakeFiles/HoughCircle_Demo.dir/flags.make
CMakeFiles/HoughCircle_Demo.dir/HoughCircle_Demo.cpp.o: HoughCircle_Demo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kolyan/opencv/opencv/samples/cpp/tutorial_code/ImgTrans/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HoughCircle_Demo.dir/HoughCircle_Demo.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HoughCircle_Demo.dir/HoughCircle_Demo.cpp.o -c /home/kolyan/opencv/opencv/samples/cpp/tutorial_code/ImgTrans/HoughCircle_Demo.cpp

CMakeFiles/HoughCircle_Demo.dir/HoughCircle_Demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HoughCircle_Demo.dir/HoughCircle_Demo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kolyan/opencv/opencv/samples/cpp/tutorial_code/ImgTrans/HoughCircle_Demo.cpp > CMakeFiles/HoughCircle_Demo.dir/HoughCircle_Demo.cpp.i

CMakeFiles/HoughCircle_Demo.dir/HoughCircle_Demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HoughCircle_Demo.dir/HoughCircle_Demo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kolyan/opencv/opencv/samples/cpp/tutorial_code/ImgTrans/HoughCircle_Demo.cpp -o CMakeFiles/HoughCircle_Demo.dir/HoughCircle_Demo.cpp.s

CMakeFiles/HoughCircle_Demo.dir/HoughCircle_Demo.cpp.o.requires:

.PHONY : CMakeFiles/HoughCircle_Demo.dir/HoughCircle_Demo.cpp.o.requires

CMakeFiles/HoughCircle_Demo.dir/HoughCircle_Demo.cpp.o.provides: CMakeFiles/HoughCircle_Demo.dir/HoughCircle_Demo.cpp.o.requires
	$(MAKE) -f CMakeFiles/HoughCircle_Demo.dir/build.make CMakeFiles/HoughCircle_Demo.dir/HoughCircle_Demo.cpp.o.provides.build
.PHONY : CMakeFiles/HoughCircle_Demo.dir/HoughCircle_Demo.cpp.o.provides

CMakeFiles/HoughCircle_Demo.dir/HoughCircle_Demo.cpp.o.provides.build: CMakeFiles/HoughCircle_Demo.dir/HoughCircle_Demo.cpp.o


# Object files for target HoughCircle_Demo
HoughCircle_Demo_OBJECTS = \
"CMakeFiles/HoughCircle_Demo.dir/HoughCircle_Demo.cpp.o"

# External object files for target HoughCircle_Demo
HoughCircle_Demo_EXTERNAL_OBJECTS =

HoughCircle_Demo: CMakeFiles/HoughCircle_Demo.dir/HoughCircle_Demo.cpp.o
HoughCircle_Demo: CMakeFiles/HoughCircle_Demo.dir/build.make
HoughCircle_Demo: /usr/local/lib/libopencv_dnn.so.4.4.0
HoughCircle_Demo: /usr/local/lib/libopencv_gapi.so.4.4.0
HoughCircle_Demo: /usr/local/lib/libopencv_highgui.so.4.4.0
HoughCircle_Demo: /usr/local/lib/libopencv_ml.so.4.4.0
HoughCircle_Demo: /usr/local/lib/libopencv_objdetect.so.4.4.0
HoughCircle_Demo: /usr/local/lib/libopencv_photo.so.4.4.0
HoughCircle_Demo: /usr/local/lib/libopencv_stitching.so.4.4.0
HoughCircle_Demo: /usr/local/lib/libopencv_video.so.4.4.0
HoughCircle_Demo: /usr/local/lib/libopencv_videoio.so.4.4.0
HoughCircle_Demo: /usr/local/lib/libopencv_imgcodecs.so.4.4.0
HoughCircle_Demo: /usr/local/lib/libopencv_calib3d.so.4.4.0
HoughCircle_Demo: /usr/local/lib/libopencv_features2d.so.4.4.0
HoughCircle_Demo: /usr/local/lib/libopencv_flann.so.4.4.0
HoughCircle_Demo: /usr/local/lib/libopencv_imgproc.so.4.4.0
HoughCircle_Demo: /usr/local/lib/libopencv_core.so.4.4.0
HoughCircle_Demo: CMakeFiles/HoughCircle_Demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kolyan/opencv/opencv/samples/cpp/tutorial_code/ImgTrans/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HoughCircle_Demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HoughCircle_Demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HoughCircle_Demo.dir/build: HoughCircle_Demo

.PHONY : CMakeFiles/HoughCircle_Demo.dir/build

CMakeFiles/HoughCircle_Demo.dir/requires: CMakeFiles/HoughCircle_Demo.dir/HoughCircle_Demo.cpp.o.requires

.PHONY : CMakeFiles/HoughCircle_Demo.dir/requires

CMakeFiles/HoughCircle_Demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HoughCircle_Demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HoughCircle_Demo.dir/clean

CMakeFiles/HoughCircle_Demo.dir/depend:
	cd /home/kolyan/opencv/opencv/samples/cpp/tutorial_code/ImgTrans && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kolyan/opencv/opencv/samples/cpp/tutorial_code/ImgTrans /home/kolyan/opencv/opencv/samples/cpp/tutorial_code/ImgTrans /home/kolyan/opencv/opencv/samples/cpp/tutorial_code/ImgTrans /home/kolyan/opencv/opencv/samples/cpp/tutorial_code/ImgTrans /home/kolyan/opencv/opencv/samples/cpp/tutorial_code/ImgTrans/CMakeFiles/HoughCircle_Demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HoughCircle_Demo.dir/depend

