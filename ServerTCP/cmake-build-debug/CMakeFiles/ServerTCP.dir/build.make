# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /snap/clion/250/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/250/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/adri/Documents/G4_Proyecto2_SO/ServerTCP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adri/Documents/G4_Proyecto2_SO/ServerTCP/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ServerTCP.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ServerTCP.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ServerTCP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ServerTCP.dir/flags.make

CMakeFiles/ServerTCP.dir/main.c.o: CMakeFiles/ServerTCP.dir/flags.make
CMakeFiles/ServerTCP.dir/main.c.o: /home/adri/Documents/G4_Proyecto2_SO/ServerTCP/main.c
CMakeFiles/ServerTCP.dir/main.c.o: CMakeFiles/ServerTCP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adri/Documents/G4_Proyecto2_SO/ServerTCP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ServerTCP.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ServerTCP.dir/main.c.o -MF CMakeFiles/ServerTCP.dir/main.c.o.d -o CMakeFiles/ServerTCP.dir/main.c.o -c /home/adri/Documents/G4_Proyecto2_SO/ServerTCP/main.c

CMakeFiles/ServerTCP.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ServerTCP.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/adri/Documents/G4_Proyecto2_SO/ServerTCP/main.c > CMakeFiles/ServerTCP.dir/main.c.i

CMakeFiles/ServerTCP.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ServerTCP.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/adri/Documents/G4_Proyecto2_SO/ServerTCP/main.c -o CMakeFiles/ServerTCP.dir/main.c.s

CMakeFiles/ServerTCP.dir/serverInit.c.o: CMakeFiles/ServerTCP.dir/flags.make
CMakeFiles/ServerTCP.dir/serverInit.c.o: /home/adri/Documents/G4_Proyecto2_SO/ServerTCP/serverInit.c
CMakeFiles/ServerTCP.dir/serverInit.c.o: CMakeFiles/ServerTCP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adri/Documents/G4_Proyecto2_SO/ServerTCP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/ServerTCP.dir/serverInit.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ServerTCP.dir/serverInit.c.o -MF CMakeFiles/ServerTCP.dir/serverInit.c.o.d -o CMakeFiles/ServerTCP.dir/serverInit.c.o -c /home/adri/Documents/G4_Proyecto2_SO/ServerTCP/serverInit.c

CMakeFiles/ServerTCP.dir/serverInit.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ServerTCP.dir/serverInit.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/adri/Documents/G4_Proyecto2_SO/ServerTCP/serverInit.c > CMakeFiles/ServerTCP.dir/serverInit.c.i

CMakeFiles/ServerTCP.dir/serverInit.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ServerTCP.dir/serverInit.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/adri/Documents/G4_Proyecto2_SO/ServerTCP/serverInit.c -o CMakeFiles/ServerTCP.dir/serverInit.c.s

CMakeFiles/ServerTCP.dir/driver_lib.c.o: CMakeFiles/ServerTCP.dir/flags.make
CMakeFiles/ServerTCP.dir/driver_lib.c.o: /home/adri/Documents/G4_Proyecto2_SO/ServerTCP/driver_lib.c
CMakeFiles/ServerTCP.dir/driver_lib.c.o: CMakeFiles/ServerTCP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adri/Documents/G4_Proyecto2_SO/ServerTCP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/ServerTCP.dir/driver_lib.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/ServerTCP.dir/driver_lib.c.o -MF CMakeFiles/ServerTCP.dir/driver_lib.c.o.d -o CMakeFiles/ServerTCP.dir/driver_lib.c.o -c /home/adri/Documents/G4_Proyecto2_SO/ServerTCP/driver_lib.c

CMakeFiles/ServerTCP.dir/driver_lib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ServerTCP.dir/driver_lib.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/adri/Documents/G4_Proyecto2_SO/ServerTCP/driver_lib.c > CMakeFiles/ServerTCP.dir/driver_lib.c.i

CMakeFiles/ServerTCP.dir/driver_lib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ServerTCP.dir/driver_lib.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/adri/Documents/G4_Proyecto2_SO/ServerTCP/driver_lib.c -o CMakeFiles/ServerTCP.dir/driver_lib.c.s

# Object files for target ServerTCP
ServerTCP_OBJECTS = \
"CMakeFiles/ServerTCP.dir/main.c.o" \
"CMakeFiles/ServerTCP.dir/serverInit.c.o" \
"CMakeFiles/ServerTCP.dir/driver_lib.c.o"

# External object files for target ServerTCP
ServerTCP_EXTERNAL_OBJECTS =

ServerTCP: CMakeFiles/ServerTCP.dir/main.c.o
ServerTCP: CMakeFiles/ServerTCP.dir/serverInit.c.o
ServerTCP: CMakeFiles/ServerTCP.dir/driver_lib.c.o
ServerTCP: CMakeFiles/ServerTCP.dir/build.make
ServerTCP: CMakeFiles/ServerTCP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/adri/Documents/G4_Proyecto2_SO/ServerTCP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable ServerTCP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ServerTCP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ServerTCP.dir/build: ServerTCP
.PHONY : CMakeFiles/ServerTCP.dir/build

CMakeFiles/ServerTCP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ServerTCP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ServerTCP.dir/clean

CMakeFiles/ServerTCP.dir/depend:
	cd /home/adri/Documents/G4_Proyecto2_SO/ServerTCP/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adri/Documents/G4_Proyecto2_SO/ServerTCP /home/adri/Documents/G4_Proyecto2_SO/ServerTCP /home/adri/Documents/G4_Proyecto2_SO/ServerTCP/cmake-build-debug /home/adri/Documents/G4_Proyecto2_SO/ServerTCP/cmake-build-debug /home/adri/Documents/G4_Proyecto2_SO/ServerTCP/cmake-build-debug/CMakeFiles/ServerTCP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ServerTCP.dir/depend
