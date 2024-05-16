cmake_minimum_required(VERSION 3.28)
project(hyperion_engine LANGUAGES C CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")


file(
        GLOB_RECURSE SOURCE_FILES
        CONFIGURE_DEPENDS
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.hpp
        ${PROJECT_SOURCE_DIR}/src/*.h
        ${PROJECT_SOURCE_DIR}/src/include/**/*.cpp
        ${PROJECT_SOURCE_DIR}/src/include/**/*.hpp
        ${PROJECT_SOURCE_DIR}/src/include/**/*.h
)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})


target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)


if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
endif ()


if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif ()

if (EMSCRIPTEN)
    # Attach data folder to Emscripten builds.
    target_link_options(${PROJECT_NAME} PRIVATE --preload-file "${CMAKE_CURRENT_SOURCE_DIR}/data@data")
    # Set output to html to generate preview pages, otherwise you'll have to make your own html.
    set_target_properties(
            ${PROJECT_NAME}
            PROPERTIES
            SUFFIX ".html"
    )
endif ()

# copy data folder to build directory
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/data
)

find_package(SDL2 CONFIG REQUIRED)
find_package(libtcod CONFIG REQUIRED)
target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        libtcod::libtcod
)