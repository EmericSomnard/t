cmake_minimum_required(VERSION 3.10)
project(RTypeServer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add Boost.Asio dependency
find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

# Add server executable
add_executable(rtype_server src/server.cpp)
target_link_libraries(rtype_server ${Boost_LIBRARIES})

# Add test executable
enable_testing()
add_executable(server_test tests/server_test.cpp)
target_link_libraries(server_test ${Boost_LIBRARIES})
add_test(NAME ServerTest COMMAND server_test)
