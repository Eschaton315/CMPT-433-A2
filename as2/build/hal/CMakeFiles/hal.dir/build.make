# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /home/tony/.local/lib/python3.8/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/tony/.local/lib/python3.8/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tony/cmpt433/work/CMPT-433-A2/as2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tony/cmpt433/work/CMPT-433-A2/as2/build

# Include any dependencies generated for this target.
include hal/CMakeFiles/hal.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include hal/CMakeFiles/hal.dir/compiler_depend.make

# Include the progress variables for this target.
include hal/CMakeFiles/hal.dir/progress.make

# Include the compile flags for this target's objects.
include hal/CMakeFiles/hal.dir/flags.make

hal/CMakeFiles/hal.dir/src/i2c.c.o: hal/CMakeFiles/hal.dir/flags.make
hal/CMakeFiles/hal.dir/src/i2c.c.o: /home/tony/cmpt433/work/CMPT-433-A2/as2/hal/src/i2c.c
hal/CMakeFiles/hal.dir/src/i2c.c.o: hal/CMakeFiles/hal.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tony/cmpt433/work/CMPT-433-A2/as2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object hal/CMakeFiles/hal.dir/src/i2c.c.o"
	cd /home/tony/cmpt433/work/CMPT-433-A2/as2/build/hal && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT hal/CMakeFiles/hal.dir/src/i2c.c.o -MF CMakeFiles/hal.dir/src/i2c.c.o.d -o CMakeFiles/hal.dir/src/i2c.c.o -c /home/tony/cmpt433/work/CMPT-433-A2/as2/hal/src/i2c.c

hal/CMakeFiles/hal.dir/src/i2c.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/hal.dir/src/i2c.c.i"
	cd /home/tony/cmpt433/work/CMPT-433-A2/as2/build/hal && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/cmpt433/work/CMPT-433-A2/as2/hal/src/i2c.c > CMakeFiles/hal.dir/src/i2c.c.i

hal/CMakeFiles/hal.dir/src/i2c.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/hal.dir/src/i2c.c.s"
	cd /home/tony/cmpt433/work/CMPT-433-A2/as2/build/hal && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/cmpt433/work/CMPT-433-A2/as2/hal/src/i2c.c -o CMakeFiles/hal.dir/src/i2c.c.s

hal/CMakeFiles/hal.dir/src/led.c.o: hal/CMakeFiles/hal.dir/flags.make
hal/CMakeFiles/hal.dir/src/led.c.o: /home/tony/cmpt433/work/CMPT-433-A2/as2/hal/src/led.c
hal/CMakeFiles/hal.dir/src/led.c.o: hal/CMakeFiles/hal.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/tony/cmpt433/work/CMPT-433-A2/as2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object hal/CMakeFiles/hal.dir/src/led.c.o"
	cd /home/tony/cmpt433/work/CMPT-433-A2/as2/build/hal && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT hal/CMakeFiles/hal.dir/src/led.c.o -MF CMakeFiles/hal.dir/src/led.c.o.d -o CMakeFiles/hal.dir/src/led.c.o -c /home/tony/cmpt433/work/CMPT-433-A2/as2/hal/src/led.c

hal/CMakeFiles/hal.dir/src/led.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/hal.dir/src/led.c.i"
	cd /home/tony/cmpt433/work/CMPT-433-A2/as2/build/hal && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tony/cmpt433/work/CMPT-433-A2/as2/hal/src/led.c > CMakeFiles/hal.dir/src/led.c.i

hal/CMakeFiles/hal.dir/src/led.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/hal.dir/src/led.c.s"
	cd /home/tony/cmpt433/work/CMPT-433-A2/as2/build/hal && /usr/bin/arm-linux-gnueabihf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tony/cmpt433/work/CMPT-433-A2/as2/hal/src/led.c -o CMakeFiles/hal.dir/src/led.c.s

# Object files for target hal
hal_OBJECTS = \
"CMakeFiles/hal.dir/src/i2c.c.o" \
"CMakeFiles/hal.dir/src/led.c.o"

# External object files for target hal
hal_EXTERNAL_OBJECTS =

hal/libhal.a: hal/CMakeFiles/hal.dir/src/i2c.c.o
hal/libhal.a: hal/CMakeFiles/hal.dir/src/led.c.o
hal/libhal.a: hal/CMakeFiles/hal.dir/build.make
hal/libhal.a: hal/CMakeFiles/hal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/tony/cmpt433/work/CMPT-433-A2/as2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library libhal.a"
	cd /home/tony/cmpt433/work/CMPT-433-A2/as2/build/hal && $(CMAKE_COMMAND) -P CMakeFiles/hal.dir/cmake_clean_target.cmake
	cd /home/tony/cmpt433/work/CMPT-433-A2/as2/build/hal && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
hal/CMakeFiles/hal.dir/build: hal/libhal.a
.PHONY : hal/CMakeFiles/hal.dir/build

hal/CMakeFiles/hal.dir/clean:
	cd /home/tony/cmpt433/work/CMPT-433-A2/as2/build/hal && $(CMAKE_COMMAND) -P CMakeFiles/hal.dir/cmake_clean.cmake
.PHONY : hal/CMakeFiles/hal.dir/clean

hal/CMakeFiles/hal.dir/depend:
	cd /home/tony/cmpt433/work/CMPT-433-A2/as2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tony/cmpt433/work/CMPT-433-A2/as2 /home/tony/cmpt433/work/CMPT-433-A2/as2/hal /home/tony/cmpt433/work/CMPT-433-A2/as2/build /home/tony/cmpt433/work/CMPT-433-A2/as2/build/hal /home/tony/cmpt433/work/CMPT-433-A2/as2/build/hal/CMakeFiles/hal.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : hal/CMakeFiles/hal.dir/depend

