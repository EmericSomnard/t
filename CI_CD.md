# Documentation: Using CI/CD for R-Type

## Introduction

This document explains the functionality of the CI/CD pipeline for the **R-Type** project, along with the steps necessary for its effective usage.  
The pipeline ensures that the code is compiled, tested, and deployed correctly on the following branches: `dev`, `server`, `engine`, `game`, `graphic`, and `main`.

---

## CI/CD Functionality

### 1. Workflow Triggers

The CI/CD pipeline is automatically triggered in the following cases:
- A **push** is made to the `dev`, `server`, `engine`, `game`, `graphic`, or `main` branches.
- A **Pull Request** is opened targeting the `dev`, `engine`, or `main` branches.

### 2. Workflow Steps

#### a. Build

- Clones the repository using the `actions/checkout@v3` action.
- Installs the required dependencies:
  - **CMake**
  - **Boost**
  - **CTest**
- Creates a `build` directory and compiles the project using **CMake** and **Make**.

#### b. Tests

- Runs the tests defined in the `CMakeLists.txt` file using `ctest`.
- Displays the test results to ensure the code works as expected.

#### c. Deployment

- Reinstalls the required dependencies.
- Deploys the project in a **Docker** container.

---

## Error Management

If any step in the pipeline (Build, Tests, or Deploy) fails:
- The **push** or **merge** is automatically canceled.
- You must fix the errors and retry.
- **Logs** detailing which test or step failed are accessible in the **Actions** tab of your GitHub repository.

---

## Steps to Use the Pipeline

1. Add code or modifications.
2. Create a commit.
3. Push the changes to your branch.
4. Create a **Pull Request** targeting `dev`, `engine`, or `main`.
5. If all steps (Build, Tests, Deploy) succeed, the **push**, **Pull Request**, or **merge** will be validated.

---

## Example of a `CMakeLists.txt` File

```cmake
cmake_minimum_required(VERSION 3.10)
project(RTypeServer)

# C++ version configuration
set(CMAKE_CXX_STANDARD 17)

# Boost inclusion
find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

# Main executable compilation
add_executable(<your_exec> <dir/your_main_file.cpp>)
target_link_libraries(<your_exec> ${Boost_LIBRARIES})

# Tests
enable_testing()
add_executable(<your_test_exec> <dir/file_test.cpp>)
target_link_libraries(<your_test_exec> ${Boost_LIBRARIES})

# Test declaration
add_test(NAME <give_a_name_for_test> COMMAND <your_test_exec>)
