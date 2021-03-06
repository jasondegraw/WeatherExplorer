cmake_minimum_required(VERSION 2.8.11)

project(weatherexploder)

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Turn on automatic invocation of the MOC
set(CMAKE_AUTOMOC ON)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-local-typedefs")

# Find Boost
find_package(Boost 1.55.0 COMPONENTS log thread system filesystem REQUIRED)

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )



# Generate code from ui files
qt5_wrap_ui(UI_HEADERS locationdialog.ui loggingdialog.ui)

# Generate rules for building source files from the resources
qt5_add_resources(QRCS resources.qrc)

set(HDRS weatherdatamodel.h
         weatherdatapoint.h
         weatherdataperiod.h
         weatherexplorer.h
         locationdialog.h
         logging.h
         loggingdialog.h)

set(SRCS main.cpp
         weatherdatamodel.cpp
         weatherdatapoint.cpp
         weatherdataperiod.cpp
         weatherexplorer.cpp
         locationdialog.cpp
         logging.cpp
         loggingdialog.cpp)

# Tell CMake to create the executable
add_executable(WeatherExplorer ${SRCS} ${HDRS} ${UI_HEADERS} ${QRCS})

# Add the Qt5 Widgets for linking
target_link_libraries(WeatherExplorer Qt5::Widgets ${Boost_LIBRARIES} qdecnumber)

source_group(Headers FILES ${HDRS})
source_group(Sources FILES ${SRCS})
