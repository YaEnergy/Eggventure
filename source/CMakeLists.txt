# CMakeList.txt : CMake project for Eggventure, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Eggventure" VERSION 1.0.2)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

# Our Project

if (WIN32 AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
    #this is to get rid of the console window. Yeah I know, I suck.

    # Add source to this project's executable.
    add_executable (Eggventure WIN32 "Eggventure.cpp" "Eggventure.h")

    add_compile_definitions(WIN32RELEASE)
else()
    # Add source to this project's executable.
    add_executable (Eggventure "Eggventure.cpp" "Eggventure.h")
endif()


# Copy assets folder to build folder
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(Eggventure copy_assets)

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)


# Add source files (neccessary for linking)
target_sources(${PROJECT_NAME} PRIVATE
    "game.cpp"
    "assets.cpp"
    "renderer.cpp"
    "egg.cpp"
    "eggCreator.cpp" 
    "elements/FadeScreen.cpp" 
    "elements/Button.cpp" 
    "elements/TextButton.cpp" 
    "elements/StateBox.cpp" 
    "elements/UIUtils.cpp" 
    "EggStatebox.cpp"
    "eggHunt.cpp"
)

# Web Configurations
if (${PLATFORM} MATCHES "Web")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
    set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so that you can directly open it.
    
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "--preload-file ./assets --shell-file _deps/raylib-src/src/minshell.html")
endif ()

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Eggventure PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.