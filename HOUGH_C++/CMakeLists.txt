project(CV_SHORT_PROJECT)

cmake_minimum_required (VERSION 2.8) 
cmake_policy(SET CMP0015 NEW)

# Change to "Debug" to enable debug symbols
set(CMAKE_BUILD_TYPE "Release")

set(STD_FLAGS_DEBUG "-Wall -g -D__STDC_CONSTANT_MACROS -pthread")
set(STD_FLAGS_RELEASE "-Wall -D__STDC_CONSTANT_MACROS -pthread -export-dynamic -march=nocona -mfpmath=sse -ftree-vectorize -fextended-identifiers -O3")

find_package( OpenCV REQUIRED )
include_directories(./include ${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

#Add here your source files
aux_source_directory( src CV_SHORT_PROJECT_SRC )


add_library(CV_SHORT_PROJECT STATIC ${CV_SHORT_PROJECT_SRC})
set_target_properties(CV_SHORT_PROJECT PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_executable(hough src/main.cpp)
target_link_libraries(hough CV_SHORT_PROJECT  ${OpenCV_LIBS})
install(TARGETS hough RUNTIME DESTINATION bin)
