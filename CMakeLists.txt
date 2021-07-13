cmake_minimum_required(VERSION 3.13)

project(Tower_Defense_Prototype)

option(MSVC_STATIC_STD_LIBS "(MSVC only) Static link MSVC runtime libraries for better portability. Only set this to true if SFML was built with SFML_USE_STATIC_STD_LIBS=TRUE" FALSE)
option(MINGW_STATIC_STD_LIBS "(MinGW only) Static link MinGW runtime libraries for better portability" TRUE)
option(WINDOWS_HIDE_CONSOLE "Hide the console on Windows" FALSE)
option(USE_BUNDLED_SFML "Use the bundled static distribution of SFML, if available for your system" TRUE)

if(USE_BUNDLED_SFML)
	if(MSVC AND MSVC_VERSION GREATER_EQUAL 1920 AND (CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64"))
		set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/SFML-2.5.1-windows-vc16-64-bit-static-runtime/lib/cmake/SFML")
		set(SFML_STATIC_LIBRARIES TRUE)
		set(MSVC_STATIC_STD_LIBS TRUE)
	endif()
endif()

if(MSVC)
	add_link_options("/ENTRY:mainCRTStartup")
	if(WINDOWS_HIDE_CONSOLE)
		add_link_options("/SUBSYSTEM:WINDOWS")
	endif()
	if (MSVC_STATIC_STD_LIBS)
		foreach(flag
				CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
				CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
				CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
				CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
			if(${flag} MATCHES "/MD")
				string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
			endif()
		endforeach()
	endif()
endif()
if(MINGW)
	if(WINDOWS_HIDE_CONSOLE)
		add_link_options("-mwindows")
	endif()
	if(MINGW_STATIC_STD_LIBS)
		add_link_options("-static")
	endif()
endif()

find_package(SFML REQUIRED system window graphics network audio)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.c" "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(Tower_Defense_Prototype ${SRC_FILES} "src/InstanceEnemy.cpp" "src/InstanceEnemy.hpp"  )
target_include_directories(Tower_Defense_Prototype PRIVATE ${SFML_INCLUDE_DIRS})
target_link_libraries(Tower_Defense_Prototype PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

add_custom_command(TARGET Tower_Defense_Prototype POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)
