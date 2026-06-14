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
	cmake --build build --target bastion_tests
	./build/bastion_tests

configure:
	cmake -S . -B build

clean:
	cmake --build build --target clean
