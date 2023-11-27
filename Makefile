all:
	g++ ./src/*.cpp -o ./bin/compiler

test:
	./tests/*.test

quicktest:
	./bin/compiler
