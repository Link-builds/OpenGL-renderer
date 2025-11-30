cmake_minimum_required( VERSION 3.5.0 )
project( MINE )
cmake_policy( SET CMP0072 NEW )

find_package( OpenGL REQUIRED )

set( src )
add_subdirectory( "src" )

include_directories( "${PROJECT_SOURCE_DIR}/include" )
include_directories( "${PROJECT_SOURCE_DIR}/vendor" )

add_executable( "${PROJECT_NAME}" "${src}" )


# For shaders
set( SOURCE_DIR_SHADER "${CMAKE_SOURCE_DIR}/src/Shaders" )
set( DEST_DIR_SHADER "${CMAKE_BINARY_DIR}/Shaders" )

add_custom_target(
                    copy_shader ALL
                    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_DIR_SHADER} ${DEST_DIR_SHADER}
                    DEPENDS ${SOURCE_DIR_SHADER}
                 )

add_custom_command(
                    TARGET "${PROJECT_NAME}" PRE_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${SOURCE_DIR_SHADER} ${DEST_DIR_SHADER}
                  )


# For assets
set( SOURCE_DIR_RSC "${PROJECT_SOURCE_DIR}/resource" )
set( DEST_DIR_RSC "${CMAKE_BINARY_DIR}/resource" )

add_custom_target(
                    copy_resource ALL
                    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_DIR_RSC} ${DEST_DIR_RSC}
                    DEPENDS ${SOURCE_DIR_RSC}/Textures
                 )

add_custom_command(
                    TARGET "${PROJECT_NAME}" PRE_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${SOURCE_DIR_RSC} ${DEST_DIR_RSC}
                  )


#For external libs

# Imgui
add_library(  
              imgui STATIC
              vendor/imgui/imgui.cpp
              vendor/imgui/imgui_demo.cpp
              vendor/imgui/imgui_draw.cpp
              vendor/imgui/imgui_tables.cpp
              vendor/imgui/imgui_widgets.cpp
              vendor/imgui/imgui_impl_opengl3.cpp
              vendor/imgui/imgui_impl_glfw.cpp
           )

target_include_directories( imgui PUBLIC vendor/imgui )
target_link_libraries( ${PROJECT_NAME} PRIVATE imgui )

# stb_image
add_library( stb_image STATIC vendor/stb_image/stb_image.c )
target_include_directories( stb_image PUBLIC vendor/stb_image )
target_link_libraries( ${PROJECT_NAME} PRIVATE stb_image )

# glad
add_library( glad STATIC vendor/glad/glad.c )
target_include_directories( glad PUBLIC vendor/glad )
target_link_libraries( ${PROJECT_NAME} PRIVATE glad )

# Glfw implementation
# target_link_libraries( "${PROJECT_NAME}" PRIVATE glfw OpenGL::GL )
find_package(glfw3 REQUIRED)
target_link_libraries( "${PROJECT_NAME}" PRIVATE glfw OpenGL::GL )

# Dependencies
add_dependencies( "${PROJECT_NAME}" copy_shader copy_resource )