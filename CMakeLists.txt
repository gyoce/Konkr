cmake_minimum_required(VERSION 3.20)
project(Konkr VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_BINARY_DIR}>)
set(EXEC_NAME ${PROJECT_NAME})

set(RES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/res)
add_definitions("-DDEF_RES_PATH=${RES_PATH}")
add_definitions("-DSDL_MAIN_HANDLED")

include(FetchContent)

set(disable_options SDL_TEST SDL_TESTS SDL_TEST_LIBRARY SDL_EXAMPLES SDL2IMAGE_SAMPLES SDL2IMAGE_TESTS
    SDL_ATOMIC SDL_AUDIO SDL_DISKAUDIO SDL_DLOPEN SDL_HAPTIC SDL_HIDAPI SDL_JOYSTICK SDL_LOCALE SDL_POWER SDL_SENSOR
    SDL2IMAGE_AVIF SDL2IMAGE_BMP SDL2IMAGE_GIF SDL2IMAGE_JXL SDL2IMAGE_LBM SDL2IMAGE_PCX SDL2IMAGE_PNM SDL2IMAGE_QOI 
    SDL2IMAGE_SVG SDL2IMAGE_TGA SDL2IMAGE_TIF SDL2IMAGE_WEBP SDL2IMAGE_XCF SDL2IMAGE_XPM SDL2IMAGE_XV
)
set(enable_options SDL2IMAGE_JPG SDL2IMAGE_PNG SDL2TTF_VENDORED)

foreach(option ${disable_options})
    set(${option} OFF CACHE BOOL "")
endforeach()

foreach(option ${enable_options})
    set(${option} ON CACHE BOOL "")
endforeach()

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.32.0
)
FetchContent_Declare(
    SDL_Image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
    GIT_TAG release-2.8.5
)
FetchContent_Declare(
    SDL_Ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf
    GIT_TAG release-2.24.0
)
FetchContent_MakeAvailable(SDL2 SDL_Image SDL_Ttf)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.hpp)

include_directories(
    ${SDL2_SOURCE_DIR}/include
    src/
)

add_executable(${EXEC_NAME} src/Main.cpp ${SOURCES} ${HEADERS})
target_link_libraries(${EXEC_NAME} 
    PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf
)