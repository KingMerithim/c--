all: ./src/*.cpp
	g++ ./src/*.cpp -o ./bin/bibliothek
	
clean:	
	rm -f ./bin/*
