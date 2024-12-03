# Documentation : Utilisation de la CI/CD pour R-Type

## Introduction

Ce document décrit le fonctionnement du pipeline CI/CD pour le projet **R-Type**, ainsi que les étapes nécessaires pour l'utiliser efficacement.  
Ce pipeline garantit que le code est compilé, testé et déployé correctement sur les branches suivantes : `dev`, `server`, `engine`, `game`, `graphic` et `main`.

---

## Fonctionnement de la CI/CD

### 1. Déclenchement des workflows

Le pipeline CI/CD est déclenché automatiquement dans les cas suivants :
- Un **push** est effectué sur les branches `dev`, `server`, `engine`, `game`, `graphic` ou `main`.
- Une **Pull Request** est ouverte vers les branches `dev` ou `main`.

### 2. Étapes des workflows

#### a. Build

- Clone le dépôt à l’aide de l’action `actions/checkout@v3`.
- Installe les dépendances requises :
  - **CMake**
  - **Boost**
  - **CTest**
- Crée un répertoire `build` et compile le projet à l'aide de **CMake** et **Make**.

#### b. Tests

- Exécute les tests définis dans le fichier `CMakeLists.txt` via `ctest`.
- Affiche les résultats des tests pour s'assurer que le code fonctionne comme prévu.

#### c. Déploiement

- Répète l'installation des dépendances.
- Déploie le projet dans un conteneur **Docker**.

---

## Gestion des erreurs

Si une étape du pipeline (Build, Tests ou Deploy) échoue :
- Le **push** ou le **merge** est automatiquement annulé.
- Vous devez corriger les erreurs et réessayer.
- Les **logs** indiquant quel test ou étape a échoué sont accessibles dans l'onglet **Actions** de votre dépôt GitHub.

---

## Étapes pour utiliser le pipeline

1. Ajouter du code ou des modifications.
2. Créer un commit.
3. Pousser les modifications sur votre branche.
4. Créer une **Pull Request** vers `dev` ou `main`.
5. Si toutes les étapes (Build, Tests, Deploy) réussissent, le **push**, la **Pull Request** ou le **merge** sera validé.

---

## Exemple de fichier `CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.10)
project(RTypeServer)

# Configuration de la version C++
set(CMAKE_CXX_STANDARD 17)

# Inclusion de Boost
find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

# Compilation de l'exécutable principal
add_executable(<your_exec> <dir/your_main_file.cpp>)
target_link_libraries(<your_exec> ${Boost_LIBRARIES})

# Tests
enable_testing()
add_executable(<your_test_exec> <dir/file_test.cpp>)
target_link_libraries(<your_test_exec> ${Boost_LIBRARIES})

# Déclaration des tests
add_test(NAME <give_a_name_for_test> COMMAND <your_test_exec>)
