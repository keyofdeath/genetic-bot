cmake_minimum_required(VERSION 3.5)
project(Genetic_Bot)

set(CMAKE_C_STANDARD 99)

# Use the package PkgConfig to detect GTK+ headers/library files
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

# Add other flags to the compiler
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

set(SOURCE_FILES main.c Neural/NeuralNetwork.h Neural/NeuralNetwork.c Neural/NeuronalInput.h Neural/NeuronalInput.c Neural/NeuralLayer.c Neural/NeuralLayer.h Neural/Neuron.c Neural/Neuron.h Neural/NeuralActivation.c Neural/NeuralActivation.h Neural/TestNeural.h Neural/TestNeural.c Genetic/DnaNeuralNetwork.c Genetic/DnaNeuralNetwork.h Genetic/GeneDouble.c Genetic/GeneDouble.h Tool/Tool.c Tool/Tool.h Genetic/Population.c Genetic/Population.h Genetic/Individual.c Genetic/Individual.h Robot/Robot.c Robot/Robot.h Robot/Sensor.h Robot/Sensor.c Vector2D/points.h Vector2D/points.c Constante/Constante.h Board/Obstacle.c Board/Obstacle.h Board/Board.h Board/Board.c Workers/Workers.c Workers/Workers.h)
add_executable(Genetic_Bot ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(Genetic_Bot ${GTK3_LIBRARIES})
# on lie la library math au projet Genetic_Bot et la library pour les threads
target_link_libraries(Genetic_Bot m -lm -lpthread)
