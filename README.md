# genetic-bot
Projet C réaliser pour un cours de M1. L'objectif est d'entrainer un reseau de neurone afin conduire une voiture a l'aide d'algorithme génétique.

Vidéo de présentation: [link](https://drive.google.com/file/d/1j4IPwt5t_o6sAyyPHedUWDtauAvAu3l_/view)

## Dependense du projet
    
 GTK version 3.0

## Installation

Compiler le cmake:

    cmake -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles" "."

Puis une fois le makeFile générer taper:
    
    make

### Problem de compilation

Il se peut que se type de message arrive:

    CMake Error at CMakeLists.txt:1 (cmake_minimum_required):
    CMake 3.8 or higher is required.  You are running version 3.5.1

Pour le corriger il faut modifier la fichier CMakeLists.txt et changer la ligne:

    cmake_minimum_required(VERSION 3.8)
    en
    cmake_minimum_required(VERSION 3.5)

## Annexe

Rapport du projet: [génétic_Bot.pdf](génétic_Bot.pdf)