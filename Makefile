.PHONY: clean

OUT = build/main.out

_src = main.cpp universe.cpp utils/readTiledMapData.cpp Entity.cpp
src = $(addprefix src/,$(_src))

_objects = main.o universe.o readTiledMapData.o Entity.o
objects = $(addprefix build/obj/,$(_objects))

lib = -ljsoncpp -lsfml-graphics -lsfml-window -lsfml-system


all: $(OUT)

$(OUT): $(objects)
	g++ -o $(OUT) $(objects) $(lib)

$(objects): $(src)
	g++ -c $(src); \
	mkdir -p ./build/obj; \
	mv *.o ./build/obj;

clean:
	rm -rf build