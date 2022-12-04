compile:
	g++ -c main.cpp universe.cpp
	g++ main.o universe.o -o main -lsfml-graphics -lsfml-window -lsfml-system
