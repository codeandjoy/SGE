compile:
	g++ -c main.cpp universe.cpp ./utils/readTiledMapData.cpp
	g++ main.o universe.o readTiledMapData.o -o main.out -ljsoncpp -lsfml-graphics -lsfml-window -lsfml-system
