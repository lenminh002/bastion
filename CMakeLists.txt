cmake_minimum_required(VERSION 3.20)

project(bastion LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(bastion
    src/main.cpp
    src/Game.cpp
    src/Grid.cpp
    src/Enemy.cpp
    src/Tower.cpp
)
add_executable(arraylist_tests
    tests/ArrayListTests.cpp
)
add_executable(queue_tests
    tests/QueueTests.cpp
)
add_executable(stack_tests
    tests/StackTests.cpp
)
add_executable(singly_linked_list_tests
    tests/SinglyLinkedListTests.cpp
)
add_executable(doubly_linked_list_tests
    tests/DoublyLinkedListTests.cpp
)
add_executable(map_validator_tests
    tests/MapValidatorTests.cpp
)

target_include_directories(bastion PRIVATE include)
target_include_directories(arraylist_tests PRIVATE include)
target_include_directories(queue_tests PRIVATE include)
target_include_directories(stack_tests PRIVATE include)
target_include_directories(singly_linked_list_tests PRIVATE include)
target_include_directories(doubly_linked_list_tests PRIVATE include)
target_include_directories(map_validator_tests PRIVATE include)
