.PHONY: run build test clean configure

run:
	cmake -S . -B build
	cmake --build build --target bastion
	./build/bastion

build:
	cmake -S . -B build
	cmake --build build

test:
	cmake -S . -B build
	cmake --build build --target arraylist_tests
	./build/arraylist_tests
	cmake --build build --target queue_tests
	./build/queue_tests
	cmake --build build --target stack_tests
	./build/stack_tests
	cmake --build build --target singly_linked_list_tests
	./build/singly_linked_list_tests
	cmake --build build --target doubly_linked_list_tests
	./build/doubly_linked_list_tests

configure:
	cmake -S . -B build

clean:
	cmake --build build --target clean
